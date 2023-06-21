// classifyPlanetarySystems.cpp : This file contains the 'main' function. Program execution begins and ends there.
// VER 1.4.1
// Version changes since publish where 1.0.0 is launch *.*.x where x represents changes before launch

/*
    4. Finish a more real solution

    DONE:
    1. Add difficulty were all the errors are at the beginning of the solar system
    2. Add difficulty were all the errors are at the end of the solar system
    3. Create brutal difficult were mixed difficulty is called but the errors are increased

*/

// the problem generator and answer
#include "myProblem.h"
#include <map>
#include <string>

static void print(std::vector<int>& solarSystem, std::vector<int>& posErrors);
static void print(std::vector<int>& solarSystem);

bool checkAntiOrdered(std::vector<int>& solarSystem, int numErrors)
{
    std::cout << "CHECK ANTIORDERED\n";
    int len = solarSystem.size(), firstNotError = solarSystem[1], firstNotErrorPos = 1, counterErrors = 0, prevNotError, curr;
    for(int j = 2; j < (numErrors + 1) && j < len; j++)
    {
        curr = solarSystem[j];
        if(curr > firstNotError)
        {
            firstNotError = curr;
            firstNotErrorPos = j;
        }
    }
    counterErrors = firstNotErrorPos - 1;
    prevNotError = firstNotError;
    for(int j = firstNotErrorPos + 1; j < len; j++)
    {
        curr = solarSystem[j];
        if(curr > prevNotError)
        {
            counterErrors++;
        }
        else
        {
            prevNotError = curr;
        }
    }
    //std::cout << "counterErrors::" << counterErrors << " numErrors::" << numErrors << "\n";
    return counterErrors == numErrors;
}

bool checkOrdered(std::vector<int>& solarSystem, std::vector<int>& foundErrors, int numErrors)
{
    std::cout << "CHECK ORDERED\n";
    int len = solarSystem.size(), firstNotError = solarSystem[1], firstNotErrorPos = 1, counterErrors = 0, prevNotError, curr;
    for(int j = 2; j < numErrors + 1 && j < len; j++)
    {
        curr = solarSystem[j];
        if(curr < firstNotError)
        {
            firstNotError = curr;
            firstNotErrorPos = j;
        }
    }

    // Testing code delete later
    {
        for(int j = 1; j < firstNotErrorPos; j++)
        {
            foundErrors.push_back(j);
        }
    }

    counterErrors = firstNotErrorPos - 1;
    prevNotError = firstNotError;
    for(int j = firstNotErrorPos + 1; j < len; j++)
    {
        curr = solarSystem[j];
        if(curr < prevNotError)
        {
            foundErrors.push_back(j);
            counterErrors++;
        }
        else
        {
            prevNotError = curr;
        }
    }
    //std::cout << "counterErrors::" << counterErrors << " numErrors::" << numErrors << "\n";
    return counterErrors == numErrors;
}

bool checkSimilar(std::vector<int>& solarSystem, int numErrors)
{
    std::map<int, int> groupSimilarPlanets;
    int len = solarSystem.size(), counterErrors = 0, target = len - numErrors  - 1, prevNotError, curr;
    for(int j = 1; j < len; j++)
    {
        curr = solarSystem[j];
        if(groupSimilarPlanets.find(curr) != groupSimilarPlanets.end())
        {
            groupSimilarPlanets[curr]++;
        }
        else
            groupSimilarPlanets.insert({curr, 1});
    }
    for(const std::pair<int, int>& i : groupSimilarPlanets)
    {
        //std::cout << "TOTALVALUES::" << i.second << " TARGET::" << target << "\n";
        if(i.second == target)
            return true;
    }
    //print(solarSystem);
    return false;
}

// My solution to the problem, will not work for brutal difficulty need to create a way to double-check estimations
static std::string classifyPlanetarySystem(std::vector<int>& solarSystem, std::vector<int>& posErrors, int numErrors)
{
    srand(3);
    // let's get a rough estimate of what type of solar system we are looking at
    int len = solarSystem.size(), estimation = len - 1 -  ((len / 10) + numErrors), diffInY, diffInX, x2, delta;
    //int target = len - 1 - numErrors;
    // determine[0] is x <= -1 determine[1] is -1 < x < 1 determine[2] x >= 1
    int determine[3]{ 0, 0, 0 };
    for (int planet = 1; planet < len; planet++)
    {
        x2 = uniqueRand(1, len-1, planet);
        diffInY = solarSystem[planet] - solarSystem[x2];
        diffInX = planet - x2;
        delta = diffInY / diffInX;
        if (delta <= -1)
            determine[0]++;
        else if (delta >= 1)
            determine[2]++;
        else
        {
            determine[1]++;
        }
    }
    // std::cout << "Size::" << len << " numErrors::" << numErrors << "\n";
    // std::cout << "Target::" << target <<  " Estimation::" << estimation << "\n";
    // std::cout << "determine[0]::" << determine[0] << "\ndetermine[1]::" << determine[1] << "\ndetermine[2]::" << determine[2] << "\n";

    if (determine[0] >= estimation && checkAntiOrdered(solarSystem, numErrors))
    {
        // we probably have antiordered
        return "antiordered";
    }
    else if (determine[1] >= estimation && checkSimilar(solarSystem, numErrors))
    {
        // we probably have similar
        return "similar";
    }
    else if (determine[2] >= estimation && checkOrdered(solarSystem, posErrors, numErrors))
    {
        // we probably have ordered
        return "ordered";
    }
    else
    {
        return "mixed";
    }
};

// This is a main function of all time
int main()
{
    srand(time(0));
    bool errorOccured = false;
    std::vector<int> foundErrors;
    for(int j = 0; j < 1000 && !errorOccured; j++) {
        solarSystemCreator creator = solarSystemCreator{};
        createSystemMed(creator);
        std::string a = classifyPlanetarySystem(creator.planets, foundErrors, creator.numErrors);
        if (creator.ans != a) {
            std::cout << "___ERROR OCCURED___\n";
            std::cout << "Expected::" << creator.ans << "\n";
            std::cout << "Actual::" << a << "\n";
            std::cout << "PASSED::" << j << "\n";
            print(creator.planets, creator.posErrors);
            std::cout << "FOUND__\n";
            print(foundErrors);
            errorOccured = true;
        }
    }
    if(!errorOccured)
        std::cout << "TEST PASSED\n";
    else
        std::cout << "TEST FAILED\n";

    return 0;
}

// print functions
static void print(std::vector<int>&solarSystem)
{
    int pos = 0;
    for (int i : solarSystem)
    {
        std::cout << pos++ << " : " << i << "\n";
    }
}

static void print(std::vector<int>& solarSystem, std::vector<int>& posErrors)
{
    int pos = 0;
    int curr;
    for (int iter = 0; iter < solarSystem.size(); iter++)
    {
        curr = iter-1;
        if (findNum(posErrors, curr))
        {
            std::cout << pos++ << " : " << solarSystem[iter] << "<---Error\n";
        }
        else
            std::cout << pos++ << " : " << solarSystem[iter] << "\n";
    }
    std::cout << "Location of errors\n";
    for(const int& iter : posErrors)
    {
        std::cout << iter+1 << "\n";
    }
}

