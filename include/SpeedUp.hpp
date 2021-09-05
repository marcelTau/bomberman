/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** SpeedUp_t.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_SPEEDUP_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_SPEEDUP_HPP

#include "PowerUp.hpp"

class SpeedUp : public PowerUp
{
public:
    explicit SpeedUp(SAppContext &sac, Audio *s);
    std::tuple<Timer, PowerUpType, Character *> getTimerTypeAndPlayer(Character& player) final;
    void BluRrr(){
        _sounds->powerUp3();
    }
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_SPEEDUP_HPP
