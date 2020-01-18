/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main.c
*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <tuple>
#include <iterator>
#include <iomanip>
#include <cmath>
#include "poll.hpp"

static void displayHelp(void)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./209poll pSize sSize p"
              << std::endl << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tpSize\tsize of the population" << std::endl;
    std::cout << "\tsSize\tsize of the sample (supposed to be representative)"
              << std::endl;
    std::cout << "\tp\tpercentage of voting intentions for a specific candidate"
              << std::endl;
}

static void displayPoll(const TRIO_TUPLE &study, double variance,
    std::pair<double, double> lowConf,
    std::pair<double, double> highConf)
{
    std::cout << "Population size:\t "<< std::get<0>(study) << std::endl;
    std::cout << "Sample size:\t\t "<< std::get<1>(study) << std::endl;
    std::cout << std::fixed << std::setprecision(2)
              << "Voting intentions:\t "<< std::get<2>(study)
              << "%" << std::endl;
    std::cout << std::fixed << std::setprecision(6)
              << "Variance:\t\t " << variance << std::endl;
    std::cout << std::fixed << std::setprecision(2)
              << "95% confidence interval: [" << lowConf.first
              << "%; " << lowConf.second << "%]" << std::endl;
    std::cout << std::fixed << std::setprecision(2)
              << "99% confidence interval: [" << highConf.first
              << "%; " << highConf.second << "%]" << std::endl;
}

static void poll(const TRIO_TUPLE &study)
{
    double population(std::get<0>(study));
    double sample(std::get<1>(study));
    double vote(std::get<2>(study) / 100);
    double variance{((vote * (1 - vote)) / sample)
    * ((population - sample) / (population - 1))};
    std::pair<double, double> interval{(2 * 1.96 * sqrt(variance)) / 2 * 100
    , (2 * 2.58 * sqrt(variance)) / 2 * 100};
    std::pair<double, double> lowConf{vote * 100 - interval.first,
    vote * 100 + interval.first};
    std::pair<double, double> highConf{vote * 100 - interval.second,
    vote * 100 + interval.second};
    
    if (lowConf.first < 0)
        lowConf.first = 0;
    if (highConf.first < 0)
        highConf.first = 0;
    if (lowConf.second > 100)
        lowConf.second = 100;
    if (highConf.second > 100)
        highConf.second = 100;
    variance = ((vote * (1 - vote)) / sample)
    * ((population - sample) / (population - 1));
    displayPoll(study, variance, lowConf, highConf);
}

int main(int ac, char **av)
{
    TRIO_TUPLE study;

    if (ac == 2 and strcmp(av[1], "-h") == 0) {
        displayHelp();
        return 0;
    }
    if (ac != 4)
        return 84;
    else {
        study = std::make_tuple(std::atof(av[1]),
        std::atof(av[2]), std::atof(av[3]));
        if (stringToNumber<int>(av[1]) == -42
        or stringToNumber<int>(av[2]) == -42
        or stringToNumber<double>(av[3]) == -42)
            return 84;
        if (std::get<0>(study) <= 0)
            return 84;
        if (std::get<1>(study) >= std::get<0>(study) or std::get<1>(study) <= 0)
            return 84;
        if (std::get<2>(study) < 0 or std::get<2>(study) > 100)
            return 84;
        if (std::get<0>(study) - 1 < 0)
            return 84;
    }
    poll(study);
    return 0;
}
