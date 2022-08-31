#ifndef LEADERBOARDS_H
#define LEADERBOARDS_H

#define _CRT_SECURE_NO_WARNINGS

#include <steam_api.h>
#include <steam_api_common.h>

#include <memory>

class CLeaderboards
{
public:

	CLeaderboards();
	~CLeaderboards(){};

	void FindLeaderboard( const char *pchLeaderboardName );
	bool UploadScore( int score );
	bool DownloadScores();

	void OnFindLeaderboard( LeaderboardFindResult_t *pResult, bool bIOFailure);
	void OnUploadScore( LeaderboardScoreUploaded_t *pResult, bool bIOFailure);
	void OnDownloadScore( LeaderboardScoresDownloaded_t *pResult, bool bIOFailure);

	int GetLeaderboardEntriesCount() const;
	LeaderboardEntry_t *GetLeaderboardEntry( int index );
	SteamLeaderboard_t GetCurrentLeaderboard();

	CCallResult<CLeaderboards, LeaderboardScoresDownloaded_t> m_callResultDownloadScore;
	CCallResult<CLeaderboards, LeaderboardFindResult_t> m_callResultFindLeaderboard;
	CCallResult<CLeaderboards, LeaderboardScoreUploaded_t> m_callResultUploadScore;
	
	int m_nLeaderboardEntries; // How many entries do we have?
	LeaderboardEntry_t m_leaderboardEntries[10]; // The entries

private:
	SteamLeaderboard_t m_CurrentLeaderboard; // Handle to leaderboard

};

using LeaderboardsPtr = std::shared_ptr<CLeaderboards>;

#endif