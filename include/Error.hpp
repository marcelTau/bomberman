/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Error.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_ERROR_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_ERROR_HPP


#include "AssetLoadError.hpp"
#include "SceneError.hpp"

#define SceneErrorMac(arg) \
    throw SceneError(arg "\n\tat: " __FILE__ ":" + std::to_string(__LINE__) + "\n")
#define AssetLoadErrorMac(arg) \
    throw AssetLoadError(arg "\n\tat: " __FILE__ ":" + std::to_string(__LINE__) + "\n")


#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_ERROR_HPP
