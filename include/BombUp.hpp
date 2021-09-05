/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** BombUp.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_BOMBUP_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_BOMBUP_HPP

#include "PowerUp.hpp"

class BombUp : public PowerUp
{
public:
    explicit BombUp(SAppContext &sac, Audio *s);
    std::tuple<Timer, PowerUpType, Character*> getTimerTypeAndPlayer(Character& player) final;
    void BluRrr(){
        _sounds->powerUp();
    }
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_BOMBUP_HPP
