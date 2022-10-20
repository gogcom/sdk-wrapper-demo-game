#ifndef LOBBY_H
#define LOBBY_H

#define _CRT_SECURE_NO_WARNINGS

#include <game/SWDemo.h>

#include <steam_api.h>
#include <steam_api_common.h>

#include <memory>
#include <vector>
#include <string>

class CLobby
{
public:
	
    CLobby(const GamePtr& game, bool create = false, const std::string& connectionString = nullptr);
    ~CLobby();

    bool Init();
    bool Release();

    std::string GetConnectionString() const;
    bool ConnectToLobbyByConnectionString(const std::string& connectionString);

	void SetLobbyID(const CSteamID &lobbyID);
    const CSteamID& GetLobbyID() const;
    void AddLobbyMember(const CSteamID& steamID);
    void RemoveLobbyMember(const CSteamID& steamID);
    const std::vector<CSteamID>& GetLobbyMembers() const;

    void CreateLobbyRoom();

    CCallResult<CLobby, LobbyCreated_t> m_callResultLobbyCreated;
	CCallResult<CLobby, LobbyEnter_t> m_callResultLobbyEntered;

private:
	GamePtr game;

    CSteamID lobbyID;
	std::vector<CSteamID> lobbyMembers;

    void OnLobbyCreated(LobbyCreated_t *pResult, bool bIOFailure);
    void OnLobbyEntered(LobbyEnter_t *pResult, bool bIOFailure);

	STEAM_CALLBACK( CLobby, OnLobbyChatUpdate, LobbyChatUpdate_t, m_CallbackChatDataUpdate );
    STEAM_CALLBACK( CLobby, OnLobbyEnter, LobbyEnter_t, m_CallbackLobbyEnter );
};

using LobbyPtr = std::shared_ptr<CLobby>;

#endif