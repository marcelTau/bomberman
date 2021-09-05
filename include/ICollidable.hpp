/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Collidable.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_ICOLLIDABLE_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_ICOLLIDABLE_HPP

#include "Player.hpp"

class ICollidable
{
protected:
    SAppContext *context;
    irr::scene::ISceneManager *smgr;
    irr::video::IVideoDriver *driver;
    irr::scene::ITriangleSelector *selector;
    irr::scene::IAnimatedMeshSceneNode *body;

public:
    virtual ~ICollidable() = default;
    virtual void setPosition(float x, float y) = 0;
    virtual bool HandleCollision(Character &player) = 0;
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_ICOLLIDABLE_HPP
