/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** PowerUp.cpp
*/

#include "IAnimatedMesh.h"
#include <PowerUp.hpp>

PowerUp::PowerUp(SAppContext &ctx, const irr::core::string<irr::fschar_t> &meshPath,
                 const irr::core::string<irr::fschar_t> &texturePath, Audio *s)
{
    _sounds = s;
    context = &ctx;
    this->smgr = context->device->getSceneManager();
    this->driver = context->device->getVideoDriver();

    irr::scene::IAnimatedMesh *mesh;

    if ((mesh = smgr->getMesh(meshPath)) == NULL)
        AssetLoadErrorMac("loading mesh");
    if ((this->body = smgr->addAnimatedMeshSceneNode(mesh)) == NULL)
        SceneErrorMac("adding scene node");
    this->body->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    auto *texture = driver->getTexture(texturePath);

    this->body->setMaterialTexture(0, texture);
    this->body->addAnimator(smgr->createRotationAnimator(irr::core::vector3df(0, 1, 0)));


    /* lift the player up a bit */
    auto pos = this->body->getPosition();
    pos.Y += 45;
    this->body->setPosition(pos);

    this->selector = this->smgr->createOctreeTriangleSelector(this->body->getMesh(), this->body,
                                                              128);
    this->body->setTriangleSelector(this->selector);
}

void PowerUp::setPosition(float x, float z)
{
    this->body->setPosition(irr::core::vector3d<irr::f32>(x, 45, z));
}

bool PowerUp::HandleCollision(Character &player)
{
    int playX = player.calcMiddle(player.getBody()->getPosition().X);
    int playz = player.calcMiddle(player.getBody()->getPosition().Z);
    int colX = player.calcMiddle(body->getPosition().X);
    int colz = player.calcMiddle(body->getPosition().Z);

    if (playX == colX && playz == colz)
    {
        this->body->setVisible(false);
        this->BluRrr();
        return true;
    }
    return false;
}

PowerUp::~PowerUp()
{
}
