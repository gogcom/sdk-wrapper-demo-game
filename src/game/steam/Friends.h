#ifndef FRIENDS_H
#define FRIENDS_H

#define _CRT_SECURE_NO_WARNINGS

#include <steam_api.h>

#include <memory>
#include <vector>

class CFriends
{
public:

    CFriends();

    void RequestGalaxyFriends();
    int GetFriendCount();
    CSteamID GetFriendByIndex(int iFriend);
    const char* GetFriendPersonaName(CSteamID friendID);
    std::vector<CSteamID>& GetFriendsList();

private:

    int friendFlags;
    int friendCount;
    std::vector<CSteamID> friendsList;
};

using FriendsPtr = std::shared_ptr<CFriends>;

#endif // FRIENDS_H