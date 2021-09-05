/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Speedup.cpp
*/

#include "SpeedUp.hpp"

std::tuple<Timer, PowerUpType, Character *> SpeedUp::getTimerTypeAndPlayer(Character& player)
{
    return std::make_tuple(Timer(15000), PowerUpType::SpeedUp_t, &player);
}

SpeedUp::SpeedUp(SAppContext &sac, Audio *s) : PowerUp(sac, "media/boot.3ds", "media/sydney.bmp", s)
{
    this->body->setScale(irr::core::vector3df(0.06, 0.06, 0.06));
}

