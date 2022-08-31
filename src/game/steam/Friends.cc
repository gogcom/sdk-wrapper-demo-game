#include "Friends.h"

CFriends::CFriends() :
    friendFlags{k_EFriendFlagImmediate | k_EFriendFlagOnGameServer | k_EFriendFlagRequestingInfo},
    friendCount{0}
{
    RequestGalaxyFriends();
}

void CFriends::RequestGalaxyFriends()
{
    friendCount = SteamFriends()->GetFriendCount(friendFlags);
    if (friendCount)
    {
        printf("Friend count: %d\n", friendCount);
    }
    else
        printf("Couldn't get friends\n");
}

int CFriends::GetFriendCount()
{
    return friendCount;
}

CSteamID CFriends::GetFriendByIndex(int iFriend)
{
    return friendsList[iFriend];
}

const char* CFriends::GetFriendPersonaName(CSteamID friendID)
{
    return SteamFriends()->GetFriendPersonaName(friendID);
}

std::vector<CSteamID>& CFriends::GetFriendsList()
{
    return friendsList;
}