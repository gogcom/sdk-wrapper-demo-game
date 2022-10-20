#include "Lobby.h"

#include <SDL_log.h>

CLobby::CLobby(const GamePtr& _game, bool create, const std::string& connectionString)
    : game(_game),
    m_CallbackChatDataUpdate(this, &CLobby::OnLobbyChatUpdate),
	m_CallbackLobbyEnter(this, &CLobby::OnLobbyEnter)
{
	if (create)
		Init();
	else
		ConnectToLobbyByConnectionString(connectionString);
}

CLobby::~CLobby()
{
	SDL_Log("Destroy lobby");
    SteamMatchmaking()->LeaveLobby(lobbyID);
	Release();
	game.reset();
}

bool CLobby::Init()
{
        
    SteamAPICall_t hSteamAPICall = SteamMatchmaking()->CreateLobby(ELobbyType::k_ELobbyTypePublic, 4);
	m_callResultLobbyCreated.Set(hSteamAPICall, this,
		&CLobby::OnLobbyCreated);

	if (hSteamAPICall == 0)
		return false;

    return true;
}

bool CLobby::Release()
{
	
	lobbyID = CSteamID();
	lobbyMembers.clear();
	return true;
}

std::string CLobby::GetConnectionString() const
{
	std::string connectionString = "+connect_";
	connectionString += std::to_string(lobbyID.ConvertToUint64());
	return connectionString;
}


bool CLobby::ConnectToLobbyByConnectionString(const std::string& connectionString)
{
	const std::string connectionStringPrefix = "+connect_";
	if (connectionString.find(connectionStringPrefix) == std::string::npos)
		return false;

	const auto lobbyIDStr = connectionString.substr(connectionStringPrefix.size());
	CSteamID id = std::stoull(lobbyIDStr);

	SDL_Log("Connecting to lobby: %d with connection string: %s", id, connectionString.c_str());

    SteamAPICall_t hSteamAPICall = SteamMatchmaking()->JoinLobby(id);
	m_callResultLobbyEntered.Set(hSteamAPICall, this,
		&CLobby::OnLobbyEntered);

	if (hSteamAPICall == 0)
		return false;

	return true;
}

void CLobby::SetLobbyID(const CSteamID& _lobbyID)
{
    lobbyID = _lobbyID;
}

const CSteamID& CLobby::GetLobbyID() const
{
    return lobbyID;
}

void CLobby::AddLobbyMember(const CSteamID& galaxyID)
{
	SDL_Log("User %s added", std::to_string(galaxyID.ConvertToUint64()).c_str());
	if (std::find(std::begin(lobbyMembers), std::end(lobbyMembers), galaxyID) == std::end(lobbyMembers))
		lobbyMembers.push_back(galaxyID);
}

void CLobby::RemoveLobbyMember(const CSteamID& galaxyID)
{
	SDL_Log("User %s removed", std::to_string(galaxyID.ConvertToUint64()).c_str());
    auto it = std::find(std::begin(lobbyMembers), std::end(lobbyMembers), galaxyID);
    if (it != std::end(lobbyMembers))
        lobbyMembers.erase(it);
}

const std::vector<CSteamID>& CLobby::GetLobbyMembers() const
{
    return lobbyMembers;
}

void CLobby::CreateLobbyRoom()
{
    game->SetGameState(GameState::State::LOBBY_VIEW);
}

void CLobby::OnLobbyCreated(LobbyCreated_t *pResult, bool bIOFailure)
{
	if (pResult->m_eResult != k_EResultOK)
	{
		SDL_Log("Lobby creation failed: %d", pResult->m_eResult);
		return;
	}

	lobbyID = pResult->m_ulSteamIDLobby;
	SDL_Log("Lobby created: %s\nSetting Rich Presence with connect status and connection string: %s", std::to_string(lobbyID.ConvertToUint64()).c_str(), GetConnectionString().c_str());
	SteamFriends()->SetRichPresence("connect", GetConnectionString().c_str());
}

void CLobby::OnLobbyEnter(LobbyEnter_t *pCallback)
{
	SDL_Log("OnLobbyEnter");

    if (pCallback->m_EChatRoomEnterResponse != k_EChatRoomEnterResponseSuccess )
    {
        SDL_Log("Lobby enter failed: %d", pCallback->m_EChatRoomEnterResponse);
        return;
    }

    if (pCallback->m_bLocked)
    {
        SDL_Log("Lobby enter failed: only invited users may join");
        return;
    }

    int cLobbyMembers = SteamMatchmaking()->GetNumLobbyMembers(lobbyID);

	SDL_Log("Lobby %s joined, %d users", std::to_string(lobbyID.ConvertToUint64()).c_str(), cLobbyMembers);

    for (int i = 0; i < cLobbyMembers; ++i)
	{
		AddLobbyMember(SteamMatchmaking()->GetLobbyMemberByIndex(lobbyID, i));
	}

	CreateLobbyRoom();
}

void CLobby::OnLobbyEntered(LobbyEnter_t *pResult, bool bIOFailure)
{
	SDL_Log("OnLobbyEntered");

    if (pResult->m_EChatRoomEnterResponse != k_EChatRoomEnterResponseSuccess )
    {
        SDL_Log("Lobby enter failed: %d", pResult->m_EChatRoomEnterResponse);
        return;
    }

    if (pResult->m_bLocked)
    {
        SDL_Log("Lobby enter failed: only invited users may join");
        return;
    }

	int cLobbyMembers = SteamMatchmaking()->GetNumLobbyMembers(lobbyID);

	SDL_Log("Lobby %s joined, %d users", std::to_string(lobbyID.ConvertToUint64()).c_str(), cLobbyMembers);

    for (int i = 0; i < cLobbyMembers; ++i)
	{
		AddLobbyMember(SteamMatchmaking()->GetLobbyMemberByIndex(lobbyID, i));
	}

	CreateLobbyRoom();
}

void CLobby::OnLobbyChatUpdate(LobbyChatUpdate_t *pCallback)
{
    // callbacks are broadcast to all listeners, so we'll get this for every lobby we're requesting
	if ( lobbyID != pCallback->m_ulSteamIDLobby )
		return;

	if ( pCallback->m_ulSteamIDUserChanged == SteamUser()->GetSteamID().ConvertToUint64() && 
		( pCallback->m_rgfChatMemberStateChange &
			( k_EChatMemberStateChangeLeft|
				k_EChatMemberStateChangeDisconnected|
				k_EChatMemberStateChangeKicked|
				k_EChatMemberStateChangeBanned ) ) )
	{
		// we've left the lobby, so it is now invalid
		lobbyID = CSteamID();
	}

	int cLobbyMembers = SteamMatchmaking()->GetNumLobbyMembers(lobbyID);
	for ( int i = 0; i < cLobbyMembers; i++ )
	{
		CSteamID steamIDLobbyMember = SteamMatchmaking()->GetLobbyMemberByIndex(lobbyID, i) ;

		// ignore yourself.
		if (SteamUser()->GetSteamID() == steamIDLobbyMember)
			continue;

	}
}