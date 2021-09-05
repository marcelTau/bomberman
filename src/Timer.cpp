/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** Timer.cpp
*/

#include "Timer.hpp"

void Timer::startTimer()
{
    start = std::chrono::system_clock::now();
}
float Timer::getElapsedTime()
{
    end = std::chrono::system_clock::now();
    return float(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}
bool Timer::isFinished()
{
    return getElapsedTime() >= time;
}