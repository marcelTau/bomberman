/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Bomb.cpp
*/

#include <Explosion.hpp>

Explosion::Explosion(irr::core::vector3df const &position, irr::core::vector3df const &direction, irr::IrrlichtDevice *device) {
    irr::scene::ISceneManager *sceneManager = device->getSceneManager();
    irr::video::IVideoDriver *videoDriver = device->getVideoDriver();
    _particleSystemSceneNode = sceneManager->addParticleSystemSceneNode(false);

    irr::scene::IParticleEmitter *particleEmitter = _particleSystemSceneNode->createBoxEmitter(
            irr::core::aabbox3d<irr::f32>(position.X - 10.0f, 20.0f, position.Z - 10.0f, position.X + 10.0f, 40.0f, position.Z + 10.0f),
                    direction,
                    1800, 2300,
                    irr::video::SColor(0, 255, 255, 255), irr::video::SColor(0, 255, 255, 255),
                    ///200, 200 damit es kürzer
                    500, 500,
                    0,
                    irr::core::dimension2df(8.5f, 8.5f),irr::core::dimension2df(15.0f, 15.0f));

    _particleSystemSceneNode->setEmitter(particleEmitter);
    particleEmitter->drop();
    irr::scene::IParticleAffector *particelAffector = _particleSystemSceneNode->createFadeOutParticleAffector(irr::video::SColor(0, 0, 0, 0), 45);
    _particleSystemSceneNode->addAffector(particelAffector);
    particelAffector->drop();
    _particleSystemSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _particleSystemSceneNode->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    _particleSystemSceneNode->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    _particleSystemSceneNode->setMaterialTexture(0, videoDriver->getTexture("media/textures/explosion.bmp"));
}

Explosion::~Explosion() {
    _particleSystemSceneNode->remove();
}

irr::scene::IParticleSystemSceneNode * Explosion::getParticleSceneNode()
{
    return _particleSystemSceneNode;
}
