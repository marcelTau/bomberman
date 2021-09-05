/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** FireUp.cpp
*/

#include "FireUp.hpp"

FireUp::FireUp(SAppContext &sac, Audio *s) : PowerUp(sac, "./media/asset/powerup/powerUpP.obj",
                                           "./media/asset/pillier/Texture_pillier_Selfillum_Purple"
                                           ".png", s)
{
    this->body->setMaterialTexture(
        1,driver->getTexture("./media/asset/pillier/Texture_pillier_alpha_Purple.png"));
    this->body->setMaterialTexture(
        2,driver->getTexture("./media/asset/pillier/Texture_pillier_Purple.png"));
    this->body->setScale(irr::core::vector3df(3, 3, 3));
    this->body->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    this->body->setRotation(irr::core::vector3df(50, 0, 0));

}

std::tuple<Timer, PowerUpType, Character *> FireUp::getTimerTypeAndPlayer(Character& player)
{
    return std::make_tuple(Timer(5000), PowerUpType::FireUp_t, &player);
}
