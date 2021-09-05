/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** SceneError.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_SCENEERROR_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_SCENEERROR_HPP

#include "string"
#include "exception"
#include <utility>

class SceneError : public std::exception
{
private:
    std::string _errorMessage;
public:
    SceneError(std::string errorMessage);
    std::string getMessage();
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_SCENEERROR_HPP
