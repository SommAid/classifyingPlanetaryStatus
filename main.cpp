// classifyPlanetarySystems.cpp : This file contains the 'main' function. Program execution begins and ends there.
// VER 1.4.1
// Version changes since publish where 1.0.0 is launch *.*.x where x represents changes before launch

/*
    4. Finish a more real solution
    5. Ordered and anti-Ordered fails when an error occurs at the beginning but not the front

    DONE:
    1. Add difficulty were all the errors are at the beginning of the solar system
    2. Add difficulty were all the errors are at the end of the solar system
    3. Create brutal difficult were mixed difficulty is called but the errors are increased

*/

// the problem generator and answer
#include "myProblem.h"
#include <string>
#include <map>
#include <chrono>

static void print(std::vector<int>& solarSystem, std::vector<int>& posErrors);
static void print(std::vector<int>& solarSystem);

bool checkAntiOrdered(std::vector<int>& solarSystem, int numErrors)
{
    //std::cout << "CHECK ANTIORDERED\n";
    int len = solarSystem.size(), firstNotError = solarSystem[1], firstNotErrorPos = 1, counterErrors = 0, prevNotError, curr;
    for(int j = 2; j < (numErrors+2) && j < len; j++)
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
    //std::cout << "firstNotError::" << prevNotError << " firstNotErrorPos::" << firstNotErrorPos << "\n";

    int isTrueStart = firstNotError, isTrueStartPos = firstNotErrorPos, maxNotErrors = 0, countNotErrors = 0;
    for(int j  = 1; j <= firstNotErrorPos; j++)
    {
        curr = solarSystem[j];
        for(int ins = j+1; ins <= firstNotErrorPos*2+1 && ins < len; ins++)
        {
            if(curr > solarSystem[ins])
            {
                countNotErrors++;
            }
        }
        if(countNotErrors > maxNotErrors)
        {
            maxNotErrors = countNotErrors;
            isTrueStartPos = j;
            isTrueStart = curr;
        }
        countNotErrors = 0;
    }
    counterErrors = isTrueStartPos - 1;
    prevNotError = isTrueStart;

    //std::cout << "isTrueStart::" << isTrueStart << " isTrueStartPos::" << isTrueStartPos << "\n";

    for(int j = isTrueStartPos + 1; j < len; j++)
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
    //std::cout << "counterErorrers::" << counterErrors << " numErrors::" << numErrors << "\n";
    return counterErrors == numErrors;
}

bool checkOrdered(std::vector<int>& solarSystem, int numErrors)
{
    //std::cout << "CHECK ORDERED\n";
    int len = solarSystem.size(), firstNotError = solarSystem[1], firstNotErrorPos = 1, counterErrors = 0, prevNotError, curr;
    for(int j = 2; j < numErrors + 2 && j < len; j++)
    {
        curr = solarSystem[j];
        if(curr < firstNotError)
        {
            firstNotError = curr;
            firstNotErrorPos = j;
        }
    }
    counterErrors = firstNotErrorPos - 1;
    prevNotError = firstNotError;
    //std::cout << "firstNotError::" << prevNotError << " firstNotErrorPos::" << firstNotErrorPos << "\n";

    int isTrueStart = firstNotError, isTrueStartPos = firstNotErrorPos, maxNotErrors = 0, countNotErrors = 0;
    for(int j  = 1; j <= firstNotErrorPos; j++)
    {
        curr = solarSystem[j];
        for(int ins = j+1; ins <= firstNotErrorPos*2+1 && ins < len; ins++)
        {
            if(curr < solarSystem[ins])
            {
                countNotErrors++;
            }
        }
        if(countNotErrors > maxNotErrors )
        {
            maxNotErrors = countNotErrors;
            isTrueStartPos = j;
            isTrueStart = curr;
        }
        countNotErrors = 0;
    }
    counterErrors = isTrueStartPos - 1;
    prevNotError = isTrueStart;

    //std::cout << "isTrueStart::" << isTrueStart << " isTrueStartPos::" << isTrueStartPos << "\n";


    for(int j = isTrueStartPos + 1; j < len; j++)
    {
        curr = solarSystem[j];
        if(curr < prevNotError)
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

bool checkSimilar(std::vector<int>& solarSystem, int numErrors)
{
    // std::cout << "CHECK SIMILAR\n";
    std::map<int, int> groupSimilarPlanets;
    int len = solarSystem.size(), counterErrors = 0, target = len - numErrors  - 1, prevNotError, curr, foundNonErrors = 0;
    for(int j = 1; j < len; j++)
    {
        curr = solarSystem[j];
        if(groupSimilarPlanets.find(curr) != groupSimilarPlanets.end())
        {
            ++groupSimilarPlanets[curr];
            if (groupSimilarPlanets[curr] > foundNonErrors)
                foundNonErrors = groupSimilarPlanets[curr];
        }
        else
            groupSimilarPlanets.insert({curr, 1});
    }
    //std::cout << "Found::" << foundNonErrors << " Target::" << target << "\n";
    if (foundNonErrors == target)
        return true;
    return false;
}

// My solution to the problem, will not work for brutal difficulty need to create a way to double-check estimations
static std::string classifyPlanetarySystem(std::vector<int>& solarSystem, int numErrors)
{
    srand(3);
    // let's get a rough estimate of what type of solar system we are looking at
    int len = solarSystem.size(), buffer = (len / 10), estimation = len - 1 -  (buffer + numErrors), diffInY, diffInX, x2, delta;
    
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
    else if (determine[2] >= estimation && checkOrdered(solarSystem, numErrors))
    {
        // we probably have ordered
        return "ordered";
    }
    else if (checkSimilar(solarSystem, numErrors))
    {
        // we probably have similar
        return "similar";
    }
    else
    {
        return "mixed";
    }
}

// This is a main function of all time
int main()
{
    //solarSystemCreator creator = solarSystemCreator{};
    //creator.numErrorsBrutal = 0;
    //createSystemBrutal(creator);
    //std::string a = classifyPlanetarySystem(creator.planets, creator.numErrorsBrutal);


    //solarSystemCreator creator;
    //createSystemEndErrors(creator);
    // std::string a = classifyPlanetarySystem(creator.planets, creator.numErrors);

    srand(time(0));
    std::vector<int> foundErrors;
    bool errorOccured = false;
    auto start = std::chrono::high_resolution_clock::now();
    for(int j = 0; j < 10000 && !errorOccured; j++) {
        solarSystemCreator creator;
        createSystemBrutal(creator);
        std::string a = classifyPlanetarySystem(creator.planets, creator.numErrorsBrutal);
        if (creator.ans != a) {
            std::cout << "___ERROR_OCCURED___\n";
            std::cout << "Expected::" << creator.ans << "\n";
            std::cout << "Actual::" << a << "\n";
            std::cout << "PASSED::" << j << "\n";
            std::cout << "NUM_OF_ERRORS::" << creator.numErrorsBrutal << "\n";
            print(creator.planets, creator.posErrors);
            errorOccured = true;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    if(!errorOccured)
        std::cout << "TEST PASSED in : " << duration.count() << "\n";
    else
        std::cout << "TEST FAILED in : " << duration.count() << "\n";
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
    std::cout << "Solar System__\n";
    for (int iter = 0; iter < solarSystem.size(); iter++)
    {
        curr = iter-1;
        if (std::find(posErrors.cbegin(), posErrors.cend(), curr) != posErrors.cend())
        {
            std::cout << pos++ << " : " << solarSystem[iter] << "<---Error\n";
        }
        else
            std::cout << pos++ << " : " << solarSystem[iter] << "\n";
    }
    std::cout << "Location of errors__\n";
    for(const int& iter : posErrors)
    {
        std::cout << iter+1 << "\n";
    }
}

