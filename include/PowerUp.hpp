/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** PowerUp.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_POWERUP_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_POWERUP_HPP

#include "ICollidable.hpp"
#include "Error.hpp"
#include "Audio.hpp"

class PowerUp : public ICollidable
{
    protected:
    Audio *_sounds;

public:
    ~PowerUp() override;
    explicit PowerUp(SAppContext &ctx, const irr::core::string<irr::fschar_t>& meshPath, const
    irr::core::string<irr::fschar_t> &texturePath, Audio *s);
    void setPosition(float x, float z) final;
    virtual std::tuple<Timer, PowerUpType, Character *> getTimerTypeAndPlayer(Character& player)
    = 0;
    bool HandleCollision(Character &player) override;
    void virtual BluRrr() = 0;
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_POWERUP_HPP
