/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** PowerUpHandler.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_POWERUPHANDLER_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_POWERUPHANDLER_HPP

#include "SpeedUp.hpp"
#include "FireUp.hpp"
#include "BombUp.hpp"
#include "Player.hpp"
#include "Bomb.hpp"

class PowerUpHandler
{
private:
    SAppContext *appContext;
    MyList<std::tuple<Timer, PowerUpType, Character *>> currentPowerUps;
    MyList<PowerUp *> allPowerUps;
    Audio *_sounds;

    static void handlePlayerItems(PowerUpType type, Character *);

public:
    explicit PowerUpHandler(SAppContext &ctx, Audio *s) : appContext(&ctx), _sounds(s)
    {}
    ~PowerUpHandler();
    void loop(MyList<Character *>& players);
    void addPowerUp(PowerUpType, float x, float z);
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_POWERUPHANDLER_HPP
