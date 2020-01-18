/*
** EPITECH PROJECT, 2019
** poll.hpp
** File description:
** poll.hpp
*/

#pragma once
#include <sstream>

//using STR_ARRAY = std::array<std::string, 3>;
using TRIO_TUPLE = std::tuple<double, double, double>;

template<typename T>
T stringToNumber(const std::string &str)
{
    std::istringstream strStream(str);
    T nb;

    return strStream >> nb ? nb : -42;
};
