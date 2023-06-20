// classifyPlanetarySystems.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Testing this change

// the problem generator and answer
#include <iostream>
#include <vector>
#include <string>

static std::string classifyPlanetarySystem(std::vector<int>& solarSystem, int errors);
static void print(std::vector<int>& solarSystem, std::vector<int>& posErrors);
static void print(std::vector<int>& solarSystem);

// Struct that contains all the pertanent information for creating a solar system
typedef struct solarSystemCreator{
    std::vector<int> planets = {}, posErrors = {};
    int size, startingSize, numErrors, commonSize;
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
            solarSystem.planets.push_back(int(rand() % solarSystem.commonSize));
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
        if (findNum(solarSystem.posErrors, j))
            solarSystem.planets.push_back(rand() % (prevNotError)+(prevNotError + 1));
        else if (!isFirstInserted)
        {
            isFirstInserted = true;
            solarSystem.planets.push_back(solarSystem.startingSize);
        }
        else
        {
            prevNotError = prevNotError - int(rand() % decreaseAmt);
            solarSystem.planets.push_back(prevNotError);
        }
    }

}

// creates a solar system were the planets are arranged from smalledst to largest
static void ordered(solarSystemCreator& solarSystem)
{
    int prevNotError = solarSystem.startingSize, IncreaseAmt = solarSystem.startingSize / solarSystem.size + 1, isFirstInserted = false;
    for (int j = 0; j < solarSystem.size; j++)
    {
        if (findNum(solarSystem.posErrors, j))
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
    createSolarSystem(solarSystem);
}

// creates a solar system with mediocre difficulty
static void createSystemMed(solarSystemCreator& solarSystem)
{
    solarSystem.size = int(rand() % 500) + 250;
    solarSystem.numErrors = int(rand() % 10);
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
    solarSystem.size = int(rand() % 1000) + 500;
    solarSystem.numErrors = int(rand() % 50);
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
        default:
            createRandErrorPlanetPos(solarSystem);
    }

    // if mixed solar system is created make it use a combination of similar, mixed, antiOrdered, and ordered
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
    createSolarSystem(solarSystem);
}

/*
    TODO:
    1. Add difficulty were all the errors are at the beginning of the solar system
    2. Add diffiuclty were all the errors are at the end of the solar system
    3. Create brutal difficult were mixed difficulty is called but the errors are increased
*/

// This is certainly a main function of all time
int main()
{
    solarSystemCreator creator = solarSystemCreator{};
    srand(time(0));
    createSystemHard(creator);
    print(creator.planets, creator.posErrors);
    std::vector<int> test {10000, 1, 2, 3, 4, 1};
    std::string a = classifyPlanetarySystem(test, 1);
    //std::string a = classifyPlanetarySystem(creator.planets, creator.numErrors);
    std::cout << "Expected::" << creator.ans << "\n";
    std::cout << "Actual::" << a << "\n";

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
        curr = iter - 1;
        if (findNum(posErrors, curr))
        {
            std::cout << pos++ << " : " << solarSystem[iter] << "<---Error\n";
        }
        else
            std::cout << pos++ << " : " << solarSystem[iter] << "\n";
    }
}

// My solution to the problem
static std::string classifyPlanetarySystem(std::vector<int>& solarSystem, int errors)
{
    // lets get a rough estimate of what type of solar system we are looking at
    int len = solarSystem.size(), target = len - 1 - errors, diffInY, diffInX, delta, isOrdered, isAntiordered, isSimilar;

    // determine[0] is x <= -1 determine[1] is -1 < x < 1 determine[2] x >= 1
    int determine[3]{ 0, 0, 0 };
    for (int planet = 1; planet < len - 1; planet++)
    {
        diffInY = solarSystem[planet] - solarSystem[planet + 1];
        diffInX = planet - (planet + 1);
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

    std::cout << "Size::" << len << " numErrors::" << errors << "\n";
    std::cout << "Target::" << target << "\n";
    std::cout << "determine[0]::" << determine[0] << "\ndetermine[1]::" << determine[1] << "\ndetermine[2]::" << determine[2] << "\n";

    if ((determine[0] >= (target - errors - 1)) && (determine[0] <= (target + errors + 1)))
    {
        // we probably have antiordered
        return "antiordered";
    }
    else if ((determine[1] >= (target - errors - 1)) && (determine[1] <= (target + errors + 1)))
    {
        // we probably have similar
        return "similar";
    }
    else if ((determine[2] >= (target - errors - 1)) && (determine[2] <= (target + errors + 1)))
    {
        // we probably have ordered
        return "ordered";
    }
    else
    {
        return "mixed";
    }
}

