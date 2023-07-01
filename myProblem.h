//
// Created by Aidan Sommer on 6/21/23.
//

#ifndef CLASSIFYINGPLANETARYSTATUS_MYPROBLEM_H
#define CLASSIFYINGPLANETARYSTATUS_MYPROBLEM_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

// Struct that contains all the pertinent information for creating a solar system
typedef struct solarSystemCreator {
    std::vector<int> planets{}, posErrors{}, posBrutalErrors{};
    int size, startingSize, commonSize, numErrors, numErrorsBrutal;
    std::string ans;
}solarSystemCreator;

// just wanted an excuse for xor shenanigans
static int uniqueRand(int min, int max, int notAllowed)
{
    int randNum = rand() % max + min;
    while (randNum == notAllowed)
    {
        randNum = rand() % max + min;
    }
    return randNum;
}

// creates a vector of positions where error planets will be random
static void createErrorPlanetsRand(solarSystemCreator& solarSystem)
{
    int randNum, errorSize = 0;
    while (errorSize < solarSystem.numErrors)
    {
        randNum = (int)(rand() % solarSystem.size);
        if (std::find(solarSystem.posErrors.cbegin(), solarSystem.posErrors.cend(), randNum) == solarSystem.posErrors.cend())
        {
            errorSize++;
            solarSystem.posErrors.emplace_back(randNum);
        }
    }
}
// creates a vector of positions where error planets will be at the beginning
static void createErrorPlanetsBeg(solarSystemCreator& solarSystem)
{
    for (int j = 0; j < solarSystem.numErrors; j++) {
        solarSystem.posErrors.emplace_back(j);
    }
}
// creates a vector of positions where error planets will be at the end
static void createErrorPlanetsEnd(solarSystemCreator& solarSystem)
{    
    for (int j = 0; j < solarSystem.numErrors; j++) {
        solarSystem.posErrors.emplace_back(solarSystem.size - 2 - j);
    }
}
static void randErrorType(solarSystemCreator& solarSystem)
{
    int whereErrors = int(rand() % 3);
    switch (whereErrors)
    {
    case 0:
        createErrorPlanetsRand(solarSystem);
        break;
    case 1:
        createErrorPlanetsBeg(solarSystem);
        break;
    case 2:
        createErrorPlanetsEnd(solarSystem);
        break;
    }
}

// creates planets with the same size
static void similar(solarSystemCreator& solarSystem)
{
    for (int j = 0; j < solarSystem.size; j++)
    {
        if (std::find(solarSystem.posErrors.cbegin(), solarSystem.posErrors.cend(), j) != solarSystem.posErrors.cend())
            solarSystem.planets.emplace_back(uniqueRand(0, solarSystem.planets[0], solarSystem.commonSize));
        else
            solarSystem.planets.emplace_back(solarSystem.commonSize);
    }
}

// creates a solar system with mixed planets
static void mixed(solarSystemCreator& solarSystem)
{
    solarSystem.planets.insert(solarSystem.planets.cend(), solarSystem.size, rand() % 10000000);
}

// creates a solar system were the planets are arranged from largest to smallest
static void antiOrdered(solarSystemCreator& solarSystem)
{
    int prevNotError = solarSystem.startingSize, decreaseAmt = solarSystem.startingSize / solarSystem.size + 1, isFirstInserted = false;
    for (int j = 0; j < solarSystem.size - 1; j++)
    {
        if ((std::find(solarSystem.posErrors.cbegin(), solarSystem.posErrors.cend(), j) != solarSystem.posErrors.cend()) && !isFirstInserted)
            solarSystem.planets.emplace_back(rand() % (solarSystem.startingSize - decreaseAmt * solarSystem.numErrors));
        else if (std::find(solarSystem.posErrors.cbegin(), solarSystem.posErrors.cend(), j) != solarSystem.posErrors.cend())
            solarSystem.planets.emplace_back(rand() % (solarSystem.planets[0] - prevNotError - 1) + (prevNotError + 1));
        else if (!isFirstInserted)
        {
            isFirstInserted = true;
            solarSystem.planets.emplace_back(solarSystem.startingSize);
        }
        else
        {
            prevNotError = prevNotError - int(rand() % decreaseAmt) - 1;
            solarSystem.planets.emplace_back(prevNotError);
        }
    }

}

// creates a solar system were the planets are arranged from smallest to largest
static void ordered(solarSystemCreator& solarSystem)
{
    int prevNotError = solarSystem.startingSize, increaseAmt = solarSystem.startingSize / solarSystem.size + 1, isFirstInserted = false;
    for (int j = 0; j < solarSystem.size; j++)
    {
        if ((std::find(solarSystem.posErrors.cbegin(), solarSystem.posErrors.cend(), j) != solarSystem.posErrors.cend()) && !isFirstInserted)
        {
            solarSystem.planets.emplace_back(rand() % (solarSystem.planets[0] - (solarSystem.startingSize) - 1) + (solarSystem.startingSize + increaseAmt * solarSystem.numErrors) + 1);
        }
        else if (std::find(solarSystem.posErrors.cbegin(), solarSystem.posErrors.cend(), j) != solarSystem.posErrors.cend())
            solarSystem.planets.emplace_back(rand() % (prevNotError));
        else if (!isFirstInserted)
        {
            isFirstInserted = true;
            solarSystem.planets.emplace_back(solarSystem.startingSize);
        }
        else
        {
            prevNotError = 1 + prevNotError + int(rand() % increaseAmt);
            solarSystem.planets.emplace_back(prevNotError);
        }
    }
}

/*
    With the four functions done we need to finish this "control" method
    This method will dish out the different types of solar systems
    Main functionality:
    determine # of errors (errors)
    determine # planets in the solar system (size)
    determine the size of the first planet if required (startingSize)
    determine the size of the sun
*/
static void createSolarSystem(solarSystemCreator& solarSystem)
{
    int type = rand() % 4;
    int sun = 100000000;
    solarSystem.planets.emplace_back(sun);
    switch (type)
    {
    case 0:
    {
        // similar
        solarSystem.ans = "similar";
        solarSystem.commonSize = int(rand() % sun);
        similar(solarSystem);
        return;
    }
    case 1:
    {
        // mixed
        mixed(solarSystem);
        solarSystem.ans = "mixed";
        return;
    }
    case 2:
    {
        // antiOrdered
        solarSystem.startingSize = int(rand() % (sun - (solarSystem.size + 1)) + (solarSystem.size + 1));
        antiOrdered(solarSystem);
        solarSystem.ans = "antiordered";
        return;
    }
    case 3:
    {
        // ordered
        solarSystem.startingSize = int(rand() % (sun - (solarSystem.size + 1)) + (solarSystem.size + 1));
        ordered(solarSystem);
        solarSystem.ans = "ordered";
        return;
    }
    }
}

// creates a really ez solar system
static void createSystemEz(solarSystemCreator& solarSystem)
{
    solarSystem.size = int(rand() % 100) + 100;
    solarSystem.numErrors = int(rand() % 3);
    createErrorPlanetsRand(solarSystem);
    createSolarSystem(solarSystem);
}

// creates a solar system with mediocre difficulty
static void createSystemMed(solarSystemCreator& solarSystem)
{
    solarSystem.size = int(rand() % 500) + 250;
    solarSystem.numErrors = int(rand() % 10);
    createErrorPlanetsRand(solarSystem);
    createSolarSystem(solarSystem);
}

// creates a solar system with a hard level of difficulty
static void createSystemHard(solarSystemCreator& solarSystem)
{
    solarSystem.size = int(rand() % 1000) + 500;
    solarSystem.numErrors = int(rand() % 50);
    createErrorPlanetsRand(solarSystem);
    createSolarSystem(solarSystem);
}

// creates a hard solar system, but all the errors are at the beginning
static void createSystemFrontErrors(solarSystemCreator& solarSystem)
{
    solarSystem.size = int(rand() % 1000) + 500;
    solarSystem.numErrors = int(rand() % 50);
    createErrorPlanetsBeg(solarSystem);
    createSolarSystem(solarSystem);
}

// creates a hard solar system, but all the errors are at the end
static void createSystemEndErrors(solarSystemCreator& solarSystem)
{
    solarSystem.size = int(rand() % 1000) + 500;
    solarSystem.numErrors = int(rand() % 50);
    createErrorPlanetsEnd(solarSystem);
    createSolarSystem(solarSystem);
}

// Use this function multiple times to create a brutally difficult combination of solar systems
static void createSystemBrutal(solarSystemCreator& solarSystem)
{
    solarSystem.size = int(rand() % 500) + 1000;
    // if mixed solar system is created make it use a combination of similar, mixed, antiOrdered, and ordered
    int type = rand() % 5;
    int sun = 100000000;
    solarSystem.planets.emplace_back(sun);
    switch (type)
    {
    case 0:
    {
        // similar
        solarSystem.numErrorsBrutal = int(rand() % (solarSystem.size - 2) / 2);
        solarSystem.numErrors = solarSystem.numErrorsBrutal;
        randErrorType(solarSystem);
        solarSystem.ans = "similar";
        solarSystem.commonSize = int(rand() % sun);
        similar(solarSystem);
        return;
    }
    case 1:
    {
        // antiOrdered
        solarSystem.numErrorsBrutal = int(rand() % 50) + 5;
        solarSystem.numErrors = solarSystem.numErrorsBrutal;
        randErrorType(solarSystem);
        solarSystem.startingSize = int(rand() % (sun - 200001) + 200000);
        antiOrdered(solarSystem);
        solarSystem.ans = "antiordered";
        return;
    }
    case 2:
    {
        // ordered
        solarSystem.numErrorsBrutal = int(rand() % 50) + 5;
        solarSystem.numErrors = solarSystem.numErrorsBrutal;
        randErrorType(solarSystem);
        solarSystem.startingSize = int(rand() % (sun - 400000) + 200000);
        ordered(solarSystem);
        solarSystem.ans = "ordered";
        return;
    }
    default:
    {
        // Brutal Mixed
        solarSystem.ans = "mixed";
        int brutalSystem = rand() % 4;

        solarSystem.numErrorsBrutal = int(rand() % 50) + 5;
        solarSystem.numErrors = int(rand() % 20) + solarSystem.numErrorsBrutal + 1;
        randErrorType(solarSystem);

        switch (brutalSystem)
        {
        case 0:
            mixed(solarSystem);
            return;
        case 1:
            solarSystem.startingSize = int(rand() % (sun - (solarSystem.size + 1)) + (solarSystem.size + 1));
            ordered(solarSystem);
            return;
        case 2:
            solarSystem.commonSize = int(rand() % sun);
            similar(solarSystem);
            return;
        case 3:
            solarSystem.startingSize = int(rand() % (sun - (solarSystem.size + 1)) + (solarSystem.size + 1));
            antiOrdered(solarSystem);
            return;
        }
        return;
    }

    }
    createSolarSystem(solarSystem);
}

#endif //CLASSIFYINGPLANETARYSTATUS_MYPROBLEM_H


