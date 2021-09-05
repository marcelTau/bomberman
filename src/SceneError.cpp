/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** SceneError.cpp
*/

#include "../include/SceneError.hpp"

SceneError::SceneError(std::string errorMessage) : _errorMessage(std::move(errorMessage)){}

std::string SceneError::getMessage()
{
    return _errorMessage;
}