#include "../include/AGHRacingTeam.h"

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <map>


void AGHRacingTeam::addMember(std::string name, int height, int yearOfJoining)
{
    //// element wersji rzucającej wyjątkami, niestety testy jednostkowe nie przechodzą jeśli funkcja rzuca wyjątki
//    if (height<100 || height>250) {
//        throw std::invalid_argument("Height has to be an integer in range [100, 250]");
//    }
//    else if (std::any_of(name.begin(), name.end(), [](char c) { return !std::isalnum(c); })
//        || (std::islower(name[0]))
//        || (name.length()>=20)) {
//        throw std::invalid_argument("Invalid name. All characters have to be alphanumeric, first letter uppercase and length less than 20");
//    }
//    else if (yearOfJoining<2000 || yearOfJoining>2023) {
//        throw std::invalid_argument("Year of joining has to be ant integer in range [2000, 2023]");
//    }

    if ((height>=100 && height <=250)
        && (std::all_of(name.begin(), name.end(), [](const char c) { return std::isalnum(c); }))
        && (std::isupper(name[0]))
        && (name.length()<20)
        && (yearOfJoining>=2000 && yearOfJoining<=2023))
    {
        members.emplace_back(name, height, yearOfJoining);
    }
}

std::vector<std::string> AGHRacingTeam::getMembersSortedByHeightAsc()
{
    std::multimap<int, std::string> membersMultimapSortedByHeight;
    for (const auto& teamMember : members) {
        membersMultimapSortedByHeight.insert({teamMember.height, teamMember.name});
    }

    std::vector<std::string> vectorOfMemberNames;
    for (const auto& pair : membersMultimapSortedByHeight) {
        vectorOfMemberNames.push_back(pair.second);
    }

    return vectorOfMemberNames;
}

int AGHRacingTeam::getNumberOfMembersWhoJoinedInLeapYear()
{
    int counterOfMembersWhoJoinedInLeapYear = 0;
    for(const auto& teamMember : members) {
        if (teamMember.yearOfJoining%4==0) {                // w tym przedziale taki warunek wystarczy
            ++counterOfMembersWhoJoinedInLeapYear;
        }
    }
    return counterOfMembersWhoJoinedInLeapYear;
}

int AGHRacingTeam::getMaxNumberOfJoinedInTheSameYear()
{
    // add your code here
    return 0;
}