/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** PowerUpHandler.cpp
*/

#include "PowerUpHandler.hpp"
#include "Character.hpp"

void PowerUpHandler::loop(MyList<Character *>& players)
{
    MyList<MyList<std::tuple<Timer, PowerUpType, Character *>>::iterator> erasablePair;
    MyList<MyList<PowerUp *>::iterator> erasablePowerUps;
    for (auto it = allPowerUps.begin(); it!= allPowerUps.end(); it++)
    {
        for (auto &player : players)
        {
            if ((*it)->HandleCollision(*player))
            {
                auto pu = (*it)->getTimerTypeAndPlayer(*player);
                std::get<0>(pu).startTimer();
                currentPowerUps.push_back(pu);
                erasablePowerUps.push_back(it);
                break;
            }
        }
    }
    for (auto & it : erasablePowerUps)
    {
        allPowerUps.erase(it);
    }

    for (auto & player : players)
    {
        player->setExtraSpeed(1);
        player->setFire(false);
        player->setUnlimitedBombs(false);
    }

    for (auto it = currentPowerUps.begin(); it != currentPowerUps.end(); it++)
    {
        if (std::get<0>(*it).isFinished())
            erasablePair.push_back(it);
        else
            handlePlayerItems(std::get<1>(*it), std::get<2>(*it));
    }
    for (auto & it : erasablePair)
    {
        currentPowerUps.erase(it);
    }
}

void PowerUpHandler::addPowerUp(PowerUpType type, float x, float z)
{
    PowerUp *item = nullptr;
    switch (type)
    {
        case PowerUpType::SpeedUp_t:
            item = new SpeedUp(*appContext, _sounds);
            break;
        case PowerUpType::FireUp_t:
            item = new FireUp(*appContext, _sounds);
            break;
        case PowerUpType::BombUp_t:
            item = new BombUp(*appContext, _sounds);
            break;
        default:
            break;
    }
    if (item)
        item->setPosition(x, z);
    else
        SceneErrorMac("uncoded powerup");
    allPowerUps.push_back(item);
}

void PowerUpHandler::handlePlayerItems(PowerUpType type, Character *playerRef)
{
    switch (type)
    {
        case PowerUpType::SpeedUp_t:
            playerRef->setExtraSpeed(2);
            break;
        case PowerUpType::FireUp_t:
            playerRef->setFire(true);
            break;
        case PowerUpType::BombUp_t:
            playerRef->setUnlimitedBombs(true);
        default:
            break;
    }
}

PowerUpHandler::~PowerUpHandler()
{
    allPowerUps.clear();
    currentPowerUps.clear();
}
