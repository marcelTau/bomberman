/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Bomb.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_EXPLOSION_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_EXPLOSION_HPP

#include <irrlicht.h>

class Explosion
{
    irr::scene::IParticleSystemSceneNode *_particleSystemSceneNode;
public:
    Explosion(irr::core::vector3df const &position, irr::core::vector3df const &direction, irr::IrrlichtDevice *device);
    ~Explosion();

    irr::scene::IParticleSystemSceneNode * getParticleSceneNode();
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_EXPLOSION_HPP
