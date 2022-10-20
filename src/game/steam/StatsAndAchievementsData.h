#ifndef STATS_AND_ACHIEVEMENTS_DATA_H
#define STATS_AND_ACHIEVEMENTS_DATA_H

#include "StatsAndAchievements.h"

#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }
#define _STAT_ID( id,type,name ) { id, type, name, 0, 0, 0, 0 }

Achievement_t g_rgAchievements[] = 
{
	_ACH_ID( ACH_TEST_0, "Achievement Test 0" ),
	_ACH_ID( ACH_TEST_1, "Achievement Test 1" ),
	_ACH_ID( ACH_TEST_2, "Achievement Test 2" ),

};

Stat_t g_Stats[] =
{
	_STAT_ID( STAT_TEST_0, STAT_INT, "STAT_TEST_0"),
	_STAT_ID( STAT_TEST_1, STAT_FLOAT, "STAT_TEST_1"),
	_STAT_ID( STAT_TEST_2, STAT_FLOAT, "STAT_TEST_2"),
	_STAT_ID( STAT_TEST_3, STAT_AVGRATE, "STAT_TEST_3"),
};

#endif