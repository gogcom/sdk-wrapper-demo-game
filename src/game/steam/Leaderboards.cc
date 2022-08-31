#include "Leaderboards.h"

#include <math.h>

CLeaderboards::CLeaderboards() :
 m_CurrentLeaderboard( NULL ),
 m_nLeaderboardEntries( 0 )
{
}

void CLeaderboards::FindLeaderboard( const char *pchLeaderboardName )
{
	m_CurrentLeaderboard = NULL;

	SteamAPICall_t hSteamAPICall = SteamUserStats()->FindLeaderboard(pchLeaderboardName);
	m_callResultFindLeaderboard.Set(hSteamAPICall, this,
		&CLeaderboards::OnFindLeaderboard);
}

bool CLeaderboards::UploadScore( int score )
{
	if (!m_CurrentLeaderboard)
		return false;

	SteamAPICall_t hSteamAPICall =
	SteamUserStats()->UploadLeaderboardScore( m_CurrentLeaderboard, k_ELeaderboardUploadScoreMethodForceUpdate, score, nullptr, 0 );

	m_callResultUploadScore.Set(hSteamAPICall, this, &CLeaderboards::OnUploadScore);

	return true;
}

bool CLeaderboards::DownloadScores()
{
	if (!m_CurrentLeaderboard)
		return false;

	// load the specified leaderboard data around the current user
	SteamAPICall_t hSteamAPICall = SteamUserStats()->DownloadLeaderboardEntries(
		m_CurrentLeaderboard, k_ELeaderboardDataRequestGlobal, 0, 10);
	m_callResultDownloadScore.Set(hSteamAPICall, this,
		&CLeaderboards::OnDownloadScore);

	return true;
}

void CLeaderboards::OnFindLeaderboard( LeaderboardFindResult_t *pCallback,	bool bIOFailure )
{
	// see if we encountered an error during the call
	if ( !pCallback->m_bLeaderboardFound || bIOFailure )
	{
		printf( "Leaderboard could not be found\n" );
		return;
	}

	m_CurrentLeaderboard = pCallback->m_hSteamLeaderboard;
}

void CLeaderboards::OnUploadScore(LeaderboardScoreUploaded_t *pCallback, bool bIOFailure)
{
	if ( !pCallback->m_bSuccess || bIOFailure )
	{
		printf( "Score could not be uploaded to Steam\n" );
	}
}

void CLeaderboards::OnDownloadScore(LeaderboardScoresDownloaded_t *pCallback, bool bIOFailure)
{
	if (!bIOFailure)
	{
		m_nLeaderboardEntries = std::min(pCallback->m_cEntryCount, 10);

		for (int index = 0; index < m_nLeaderboardEntries; index++)
		{
			SteamUserStats()->GetDownloadedLeaderboardEntry(
				pCallback->m_hSteamLeaderboardEntries,index,&m_leaderboardEntries[index],NULL,0);
		}
	}
}

SteamLeaderboard_t CLeaderboards::GetCurrentLeaderboard()
{
	return m_CurrentLeaderboard;
}

int CLeaderboards::GetLeaderboardEntriesCount() const
{
	return m_nLeaderboardEntries;
}

LeaderboardEntry_t *CLeaderboards::GetLeaderboardEntry(int index)
{
	return &m_leaderboardEntries[index];
}