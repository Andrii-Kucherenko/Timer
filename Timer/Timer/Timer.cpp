//Timer
#include <iostream>
#include <chrono>
#include <math.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <Windows.h>

using myClock_t = std::chrono::high_resolution_clock;
using mySecond_t = std::chrono::duration<double, std::ratio<1> >;

bool checkingForCorrrectness(std::string& str)
{
    if (str.size() < 8)
    {
        return false;
    }

    for (int i = 0; i < 8; ++i)
    {
        if (i == 2 || i == 5)
        {
            if (str[i] != ':')
            {
                return false;
            }

            continue;
        }

        if (!isdigit(str[i]))
        {
            return false;
        }
    }

    return true;
}

int main()
{
    std::chrono::time_point<myClock_t> timer;
    std::string sTime;
    bool isCorrect;
    int hours;
    int minutes;
    int seconds;

    do
    {
        std::cout << "Enter the time in form hh:mm:ss (where 'h' = hours, 'm' = minutes and 's' = seconds, for example: 12:34:56): ";
        std::getline(std::cin, sTime);
        isCorrect = checkingForCorrrectness(sTime);

        if (!isCorrect)
        {
            std::cout << "\n\t\t\tIncorrect input! Try again.\n\n";
            continue;
        }

        std::string sHours(sTime.substr(0, 2));
        std::string sMinutes(sTime.substr(3, 5));
        std::string sSeconds(sTime.substr(6, 8));

        std::stringstream convertTime;

        convertTime << sHours;
        convertTime >> hours;

        convertTime.str("");
        convertTime.clear();

        convertTime << sMinutes;
        convertTime >> minutes;

        convertTime.str("");
        convertTime.clear();

        convertTime << sSeconds;
        convertTime >> seconds;

        convertTime.str("");
        convertTime.clear();

        if (minutes > 59 || seconds > 59)
        {
            std::cout << "\n\t\t\tIncorrect input! Try again.\n\n";
            isCorrect = false;
            continue;
        }

    } while (!isCorrect);

    int timeInSeconds = hours * 3600 + minutes * 60 + seconds;
    while (timeInSeconds >= 0)
    {
        std::cout << "\n\t\t\tThere is time left: ";
        std::cout << std::setw(2) << std::setfill('0') << timeInSeconds / 3600;
        std::cout << ':';
        std::cout << std::setw(2) << std::setfill('0') << (timeInSeconds % 3600) / 60;
        std::cout << ':';
        std::cout << std::setw(2) << std::setfill('0') << timeInSeconds % 60;
        timer = myClock_t::now();

        while (std::chrono::duration_cast<mySecond_t>(myClock_t::now() - timer).count() < 1)
        {
        }
        system("cls");

        --timeInSeconds;
    }

    Beep(3000, 1000);

    return 0;
}