//
// Created by Aidan Sommer on 6/21/23.
//

#ifndef CLASSIFYINGPLANETARYSTATUS_MYPROBLEM_H
#define CLASSIFYINGPLANETARYSTATUS_MYPROBLEM_H

#endif //CLASSIFYINGPLANETARYSTATUS_MYPROBLEM_H

#include <iostream>
#include <vector>

// Struct that contains all the pertinent information for creating a solar system
typedef struct solarSystemCreator{
    std::vector<int> planets {}, posErrors {}, posBrutalErrors {};
    int size, startingSize, commonSize, numErrors, numErrorsBrutal;
    std::string ans;
}solarSystemCreator;

// checks if newNum is in nums if so true else false
static bool findNum(std::vector<int>&nums, int& newNum)
{
    for(const int& i: nums)
        if (i == newNum)
            return true;
    return false;
}

// just wanted an excuse for xor shenanigans
static int uniqueRand(int min, int max, int notAllowed)
{
    int randNum = rand()%max + min;
    while(randNum == notAllowed)
    {
        randNum =  rand()%max + min;
    }
    return randNum;
}

// creates a vector of positions where error planets will be random
static void createRandErrorPlanetPos(solarSystemCreator& solarSystem)
{
    int randNum, errorSize = 0;
    while (errorSize < solarSystem.numErrors)
    {
        randNum = (int)(rand() % solarSystem.size);
        if (!findNum(solarSystem.posErrors, randNum))
        {
            errorSize++;
            solarSystem.posErrors.push_back(randNum);
        }
    }
}
// creates a vector of positions where error planets will be at the beginning
static void createErrorPlanetsBeg(solarSystemCreator& solarSystem)
{
    for(int j = 0; j < solarSystem.numErrors; j++) {
        solarSystem.posErrors.push_back(j);
    }
}
// creates a vector of positions where error planets will be at the end
static void createErrorPlanetsEnd(solarSystemCreator& solarSystem)
{
    for(int j = 0; j < solarSystem.numErrors; j++) {
        solarSystem.posErrors.push_back(solarSystem.size - 1 - j);
    }
}

// creates planets with the same size
static void similar(solarSystemCreator& solarSystem)
{
    for (int j = 0; j < solarSystem.size; j++)
    {
        if (findNum(solarSystem.posErrors, j))
            solarSystem.planets.push_back(uniqueRand(0, solarSystem.planets[0], solarSystem.commonSize));
        else
            solarSystem.planets.push_back(solarSystem.commonSize);
    }
}

// creates a solar system with mixed planets
static void mixed(solarSystemCreator& solarSystem)
{
    for (int i = 0; i < solarSystem.size; i++)
    {
        int planetSize = rand() % 10000000;
        solarSystem.planets.push_back(planetSize);
    }
}

// creates a solar system were the planets are arranged from largest to smallest
static void antiOrdered(solarSystemCreator& solarSystem)
{
    int prevNotError = solarSystem.startingSize, decreaseAmt = solarSystem.startingSize / solarSystem.size + 1, isFirstInserted = false;
    for (int j = 0; j < solarSystem.size - 1; j++)
    {
        if (findNum(solarSystem.posErrors, j) && !isFirstInserted)
            solarSystem.planets.push_back(rand() % solarSystem.startingSize);
        else if (findNum(solarSystem.posErrors, j))
            solarSystem.planets.push_back(rand() % (solarSystem.planets[0] - prevNotError - 1)+(prevNotError + 1));
        else if (!isFirstInserted)
        {
            isFirstInserted = true;
            solarSystem.planets.push_back(solarSystem.startingSize);
        }
        else
        {
            prevNotError = prevNotError - int(rand() % decreaseAmt) - 1;
            solarSystem.planets.push_back(prevNotError);
        }
    }

}

// creates a solar system were the planets are arranged from smallest to largest
static void ordered(solarSystemCreator& solarSystem)
{
    int prevNotError = solarSystem.startingSize, IncreaseAmt = solarSystem.startingSize / solarSystem.size + 1, isFirstInserted = false;
    for (int j = 0; j < solarSystem.size; j++)
    {
        if (findNum(solarSystem.posErrors, j) && !isFirstInserted)
            solarSystem.planets.push_back(rand() % (solarSystem.planets[0] - solarSystem.startingSize - 1) + solarSystem.startingSize + 1);
        else if (findNum(solarSystem.posErrors, j))
            solarSystem.planets.push_back(rand() % (prevNotError));
        else if (!isFirstInserted)
        {
            isFirstInserted = true;
            solarSystem.planets.push_back(solarSystem.startingSize);
        }
        else
        {
            prevNotError = 1 + prevNotError + int(rand() % IncreaseAmt);
            solarSystem.planets.push_back(prevNotError);
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
    solarSystem.planets.push_back(sun);
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
    createRandErrorPlanetPos(solarSystem);
    createSolarSystem(solarSystem);
}

// creates a solar system with mediocre difficulty
static void createSystemMed(solarSystemCreator& solarSystem)
{
    solarSystem.size = int(rand() % 500) + 250;
    solarSystem.numErrors = int(rand() % 10);
    createRandErrorPlanetPos(solarSystem);
    createSolarSystem(solarSystem);
}

// creates a solar system with a hard level of difficulty
static void createSystemHard(solarSystemCreator& solarSystem)
{
    solarSystem.size = int(rand() % 1000) + 500;
    solarSystem.numErrors = int(rand() % 50);
    createRandErrorPlanetPos(solarSystem);
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
    solarSystem.numErrorsBrutal = int(rand() % 50) + 5;
    int whereErrors = int(rand()%3);
    switch (whereErrors)
    {
        case 0:
            createRandErrorPlanetPos(solarSystem);
            break;
        case 1:
            createErrorPlanetsBeg(solarSystem);
            break;
        case 2:
            createErrorPlanetsEnd(solarSystem);
            break;
    }

    // if mixed solar system is created make it use a combination of similar, mixed, antiOrdered, and ordered
    int type = 4;//rand() % 5;
    int sun = 100000000;
    solarSystem.planets.push_back(sun);
    switch (type)
    {
        case 0:
        {
            // similar
            solarSystem.numErrorsBrutal = int(rand() % (solarSystem.size - 2) / 2);
            int whereErrors = int(rand() % 3);
            switch (whereErrors)
            {
            case 0:
                createRandErrorPlanetPos(solarSystem);
                break;
            case 1:
                createErrorPlanetsBeg(solarSystem);
                break;
            case 2:
                createErrorPlanetsEnd(solarSystem);
                break;
            }
            solarSystem.ans = "similar";
            solarSystem.commonSize = int(rand() % sun);
            similar(solarSystem);
            return;
        }
        case 1:
        {
            // antiOrdered
            solarSystem.startingSize = int(rand() % (sun - (solarSystem.size + 1)) + (solarSystem.size + 1));
            antiOrdered(solarSystem);
            solarSystem.ans = "antiordered";
            return;
        }
        case 2:
        {
            // ordered
            solarSystem.startingSize = int(rand() % (sun - (solarSystem.size + 1)) + (solarSystem.size + 1));
            ordered(solarSystem);
            solarSystem.ans = "ordered";
            return;
        }
        default:
        {
            // Brutal Mixed
            solarSystem.ans = "mixed";
            std::cout << "BRUTAL MIXED SYSTEM::GL\n";
            int brutalSystem = rand() % 4;
            solarSystem.numErrors = int(rand()%20)+solarSystem.numErrorsBrutal + 1;
            switch (whereErrors)
            {
                case 0:
                    createRandErrorPlanetPos(solarSystem);
                    break;
                case 1:
                    createErrorPlanetsBeg(solarSystem);
                    break;
                case 2:
                    createErrorPlanetsEnd(solarSystem);
                    break;
            }
            switch(brutalSystem)
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
