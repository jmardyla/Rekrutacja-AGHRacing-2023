#include "../include/AGHRacingTeam.h"

#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <map>
#include <unordered_map>
#include <array>

AGHRacingTeam::AGHRacingTeam(const std::vector<Member>& membersToAdd) {
    for(const auto& person : membersToAdd) {
        this->addMember(person.name, person.height, person.yearOfJoining);
    }
}

void AGHRacingTeam::addMember(std::string name, int height, int yearOfJoining)
{
    //// was considering throwing exceptions but the unit tests don't pass
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
    const int minHeight = 100;
    const int maxHeight = 250;

    std::vector<std::string> resultVectorOfSortedNames(members.size());
    std::array<int, maxHeight-minHeight+1> arrayToCountOccurrences{};

    for(const auto& member : members) {
        ++arrayToCountOccurrences[member.height-minHeight];
    }

    for(int idx=1; idx<arrayToCountOccurrences.size(); ++idx) {
        arrayToCountOccurrences[idx] += arrayToCountOccurrences[idx-1];
    }

    for(auto it=members.rbegin(); it!=members.rend(); ++it) {
        resultVectorOfSortedNames[arrayToCountOccurrences[it->height-minHeight]-1] = it->name;
        --arrayToCountOccurrences[it->height-minHeight];
    }

    return resultVectorOfSortedNames;
}

int AGHRacingTeam::getNumberOfMembersWhoJoinedInLeapYear()
{
    int counterOfMembersWhoJoinedInLeapYear = 0;
    for(const auto& teamMember : members) {
        if (teamMember.yearOfJoining%4==0) {                // in our working range this conditions is sufficient
            ++counterOfMembersWhoJoinedInLeapYear;
        }
    }
    return counterOfMembersWhoJoinedInLeapYear;
}

int AGHRacingTeam::getMaxNumberOfJoinedInTheSameYear()
{
    std::unordered_map<int, int> mapOfYearToItsCount;
    for(const auto& teamMember : members) {
        ++mapOfYearToItsCount[teamMember.yearOfJoining];
    }

    auto iteratorToPairWithMaxCount = std::max_element(mapOfYearToItsCount.begin(), mapOfYearToItsCount.end(),
                                                  [](const auto& firstPair, const auto& secondPair) {
                                                      return firstPair.second < secondPair.second;
                                                  });
    return iteratorToPairWithMaxCount->second;
}