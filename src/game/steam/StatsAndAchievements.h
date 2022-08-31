#ifndef STATS_AND_ACHIEVEMENTS_H
#define STATS_AND_ACHIEVEMENTS_H

#define _CRT_SECURE_NO_WARNINGS

#include "StatsAndAchievementsData.h"

#include <steam_api.h>

#include <memory>

class CStatsAndAchievements
{
public:

	CStatsAndAchievements(Achievement_t *Achievements, int NumAchievements, Stat_t *Stats, int NumStats);

	bool RequestStats();
	bool SetAchievement(const char* ID);
	bool ClearAchievement(const char* ID);
	void SetStat(EStat ID, int Value);
	void SetStat(EStat ID, float Value);
	void SetAvgRateStat(EStat ID, float Numerator, float Denominator);
	bool StoreStats();
	int GetNumAchievements();
	Achievement_t *GetAchievementsData();
	int GetNumStats();
	Stat_t *GetStatsData();

	STEAM_CALLBACK( CStatsAndAchievements, OnUserStatsReceived, UserStatsReceived_t, m_CallbackUserStatsReceived );
	STEAM_CALLBACK( CStatsAndAchievements, OnUserStatsStored, UserStatsStored_t, m_CallbackUserStatsStored );
	STEAM_CALLBACK( CStatsAndAchievements, OnAchievementStored, UserAchievementStored_t, m_CallbackAchievementStored );	

private:

	int64 m_iAppID; // Our current AppID
	Achievement_t *m_pAchievements; // Achievements data
	int m_iNumAchievements; // The number of Achievements
	Stat_t *m_pStats; // Stats data
	int m_iNumStats; // The number of Stats
	bool m_bInitialized; // Have we called Request stats and received the callback?
};

using StatsAndAchievementsPtr = std::shared_ptr<CStatsAndAchievements>;

#endif // STATS_AND_ACHIEVEMENTS_H