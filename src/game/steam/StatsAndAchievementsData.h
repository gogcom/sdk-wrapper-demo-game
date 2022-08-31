#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }
#define _STAT_ID( id,type,name ) { id, type, name, 0, 0, 0, 0 }

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