#ifndef STATS_AND_ACHIEVEMENTS_H
#define STATS_AND_ACHIEVEMENTS_H

#define _CRT_SECURE_NO_WARNINGS

#include <steam_api.h>

#include <memory>

enum EAchievements
{
	ACH_TEST_0 = 0,
	ACH_TEST_1 = 1,
	ACH_TEST_2 = 2,
};

struct Achievement_t
{
	EAchievements m_eAchievementID;
	const char *m_pchAchievementID;
	char m_rgchName[128];
	char m_rgchDescription[256];
	bool m_bAchieved;
	int m_iIconImage;
};

enum EStat
{
	STAT_TEST_0 = 0,
	STAT_TEST_1 = 1,
	STAT_TEST_2 = 2,
	STAT_TEST_3 = 3,
};

enum EStatTypes
{
	STAT_INT = 0,
	STAT_FLOAT = 1,
	STAT_AVGRATE = 2,
};

struct Stat_t
{
	int m_ID;
	EStatTypes m_eStatType;
	const char *m_pchStatName;
	int m_iValue;
	float m_flValue;
	float m_flAvgNumerator;
	float m_flAvgDenominator;
};

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