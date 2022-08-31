#include "StatsAndAchievements.h"

CStatsAndAchievements::CStatsAndAchievements(Achievement_t *Achievements, int NumAchievements, Stat_t *Stats, int NumStats)
	: 
	m_iAppID( 0 ),
	m_bInitialized( false ),
	m_CallbackUserStatsReceived( this, &CStatsAndAchievements::OnUserStatsReceived ),
	m_CallbackUserStatsStored( this, &CStatsAndAchievements::OnUserStatsStored ),
	m_CallbackAchievementStored( this, &CStatsAndAchievements::OnAchievementStored )
{
	m_iAppID = SteamUtils()->GetAppID();
	m_pAchievements = Achievements;
	m_iNumAchievements = NumAchievements;
	m_pStats = Stats;
	m_iNumStats = NumStats;
	RequestStats();
}

bool CStatsAndAchievements::RequestStats()
{
	// Is Steam loaded? If not we can't get stats.
	if ( NULL == SteamUserStats() || NULL == SteamUser() )
	{
		return false;
	}
	// Is the user logged on?  If not we can't get stats.
	if ( !SteamUser()->BLoggedOn() )
	{
		return false;
	}
	// Request user stats.
	return SteamUserStats()->RequestCurrentStats();
}

bool CStatsAndAchievements::SetAchievement(const char* ID)
{
	// Have we received a call back from Steam yet?
	if (m_bInitialized)
	{
		SteamUserStats()->SetAchievement(ID);
		return SteamUserStats()->StoreStats();
	}
	// If not then we can't set achievements yet
	return false;
}

bool CStatsAndAchievements::ClearAchievement(const char* ID)
{
	// Have we received a call back from Steam yet?
	if (m_bInitialized)
	{
		SteamUserStats()->ClearAchievement(ID);
		return SteamUserStats()->StoreStats();
	}
	// If not then we can't set achievements yet
	return false;
}

void CStatsAndAchievements::SetStat(EStat ID, int Value)
{
	m_pStats[ID].m_iValue = Value;
	StoreStats();
}

void CStatsAndAchievements::SetStat(EStat ID, float Value)
{
	m_pStats[ID].m_flValue = Value;
	StoreStats();
}

void CStatsAndAchievements::SetAvgRateStat(EStat ID, float Numerator, float Denominator)
{
	m_pStats[ID].m_flAvgNumerator = Numerator;
	m_pStats[ID].m_flAvgDenominator = Denominator;
	StoreStats();
}

bool CStatsAndAchievements::StoreStats()
{
	if ( m_bInitialized )
	{
		// load stats
		for ( int iStat = 0; iStat < m_iNumStats; ++iStat )
		{
			Stat_t &stat = m_pStats[iStat];
			switch (stat.m_eStatType)
			{
			case STAT_INT:
				SteamUserStats()->SetStat( stat.m_pchStatName, stat.m_iValue );
				break;

			case STAT_FLOAT:
				SteamUserStats()->SetStat( stat.m_pchStatName, stat.m_flValue );
				break;

			case STAT_AVGRATE:
				SteamUserStats()->UpdateAvgRateStat(stat.m_pchStatName, stat.m_flAvgNumerator, stat.m_flAvgDenominator );
				// The averaged result is calculated for us
				SteamUserStats()->GetStat(stat.m_pchStatName, &stat.m_flValue );
				break;

			default:
				break;
			}
		}

		return SteamUserStats()->StoreStats();
	}

	return false;
}

int CStatsAndAchievements::GetNumAchievements()
{
	return m_iNumAchievements;
}

Achievement_t* CStatsAndAchievements::GetAchievementsData()
{
	return m_pAchievements;
}

int CStatsAndAchievements::GetNumStats()
{
	return m_iNumStats;
}

Stat_t* CStatsAndAchievements::GetStatsData()
{
	return m_pStats;
}

//-----------------------------------------------------------------------------
// Purpose: We have stats data from Steam. It is authoritative, so update
//			our data with those results now.
//-----------------------------------------------------------------------------
void CStatsAndAchievements::OnUserStatsReceived( UserStatsReceived_t *pCallback )
{
	// we may get callbacks for other games' stats arriving, ignore them
	if ( m_iAppID == pCallback->m_nGameID )
	{
		if ( k_EResultOK == pCallback->m_eResult )
		{
			printf("Received stats and achievements from Steam\n");
			m_bInitialized = true;

			// load achievements
			for ( int iAch = 0; iAch < m_iNumAchievements; ++iAch )
			{
				Achievement_t &ach = m_pAchievements[iAch];

				SteamUserStats()->GetAchievement(ach.m_pchAchievementID, &ach.m_bAchieved);
				_snprintf( ach.m_rgchName, sizeof(ach.m_rgchName), "%s",
					SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID,
					"name"));
				_snprintf( ach.m_rgchDescription, sizeof(ach.m_rgchDescription), "%s",
					SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID,
					"desc"));
			}
			for ( int iStat = 0; iStat < m_iNumStats; ++iStat )
			{
				Stat_t &stat = m_pStats[iStat];
				switch (stat.m_eStatType)
				{
				case STAT_INT:
					SteamUserStats()->GetStat(stat.m_pchStatName, &stat.m_iValue);
					break;

				case STAT_FLOAT:
				case STAT_AVGRATE:
					SteamUserStats()->GetStat(stat.m_pchStatName, &stat.m_flValue);
					break;

				default:
					break;
				}
			}
		}
		else
		{
			char buffer[128];
			_snprintf( buffer, 128, "RequestStats - failed, %d\n", pCallback->m_eResult );
			printf( buffer );
		}
	}
}



void CStatsAndAchievements::OnUserStatsStored( UserStatsStored_t *pCallback )
{
	// we may get callbacks for other games' stats arriving, ignore them
	if ( m_iAppID == pCallback->m_nGameID )
	{
		if ( k_EResultOK == pCallback->m_eResult )
		{
			printf( "Stored stats for Steam\n" );
		}
		else if ( k_EResultInvalidParam == pCallback->m_eResult )
		{
			// One or more stats we set broke a constraint. They've been reverted,
			// and we should re-iterate the values now to keep in sync.
			printf( "StoreStats - some failed to validate\n" );
			// Fake up a callback here so that we re-load the values.
			UserStatsReceived_t callback;
			callback.m_eResult = k_EResultOK;
			callback.m_nGameID = m_iAppID;
			OnUserStatsReceived( &callback );
		}
		else
		{
			char buffer[128];
			_snprintf( buffer, 128, "StatsStored - failed, %d\n", pCallback->m_eResult );
			printf( buffer );
		}
	}
	RequestStats();
}

void CStatsAndAchievements::OnAchievementStored( UserAchievementStored_t *pCallback )
{
	// we may get callbacks for other games' stats arriving, ignore them
     if ( m_iAppID == pCallback->m_nGameID )
     {
          printf( "Stored Achievement for Steam\n" );
     }
	 RequestStats();
}