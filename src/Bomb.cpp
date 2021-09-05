/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Bomb.cpp
*/

#include <Explosion.hpp>
#include <Bomb.hpp>


Bomb::Bomb(SAppContext &ctx, Audio *sounds, Character *player) : _player(player)
{
    _sounds = sounds;
    context = &ctx;
    this->smgr = context->device->getSceneManager();
    this->driver = context->device->getVideoDriver();
    irr::scene::IAnimatedMesh *mesh;

    if ((mesh = smgr->getMesh("media/bomb.3ds")) == nullptr) {
        AssetLoadErrorMac("Can't load 'media/bomb.3ds'");
    }
    if ((this->body = smgr->addAnimatedMeshSceneNode(mesh)) == nullptr) {
        SceneErrorMac("Could not add AnimatedMeshSceneNode");
    }

    this->body->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->body->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));
    this->body->setScale(irr::core::vector3df(.4));

    this->selector = this->smgr->createOctreeTriangleSelector(this->body->getMesh(), this->body, 128);
    this->body->setTriangleSelector(this->selector);

    _position = _player->getBody()->getPosition();
    _position.X = _player->calcMiddle(_position.X);
    _position.Z = _player->calcMiddle(_position.Z);
    _position.Y = 10;

    this->body->setVisible(true);
    this->body->setPosition(_position);
}

Character *Bomb::getPLayer() const
{
    return _player;
}

void Bomb::initExplosion(std::vector<float> surround)
{
    this->_exploded = true;
    _surround = surround;
    irr::core::vector3df up = irr::core::vector3df(0.0f, 0.0f, surround[0]); ///surround[0]
    irr::core::vector3df right = irr::core::vector3df(surround[1], 0.0f, 0.0f); ///surround[1]
    irr::core::vector3df down = irr::core::vector3df(0.0f, 0.0f, surround[2]); ///surround[2]
    irr::core::vector3df left = irr::core::vector3df(surround[3], 0.0f, 0.0f); ///surround[3]
    this->_explosions.push_back(new Explosion(this->_position, up, this->context->device));
    this->_explosions.push_back(new Explosion(this->_position, right, this->context->device));
    this->_explosions.push_back(new Explosion(this->_position, down, this->context->device));
    this->_explosions.push_back(new Explosion(this->_position, left, this->context->device));

    this->body->setVisible(false);
    this->timer = Timer(700);
    timer.startTimer();
}

void Bomb::stopExplosion()
{
    for (auto it : this->_explosions) {
        it->getParticleSceneNode()->setVisible(false);
        delete it;
    }
    this->_explosions.clear();
}

void Bomb::drop()
{
    timer.startTimer();
}

void Bomb::setPosition(float x, float z) {}

bool Bomb::HandleCollision(Character &player)
{
    if (player.getBody()->getTransformedBoundingBox().intersectsWithBox(this->body->getTransformedBoundingBox())) {
        this->body->setVisible(false);
        return true;
    }
    return false;
}

bool Bomb::beShureCollision(const irr::core::vector3df& pos)
{
    //_explosions
    auto colX = _player->calcMiddle(pos.X);
    auto colZ = _player->calcMiddle(pos.Z);
    auto bombX = _player->calcMiddle(body->getPosition().X);
    auto bombZ = _player->calcMiddle(body->getPosition().Z);

    float up = _surround[0];
    float right = _surround[1];
    float down = _surround[2];
    float left = _surround[3];

    int tanya = 0;
    while (up > 0.1) {

        if (bombX == colX && (bombZ + tanya == colZ))
            return true;
        else {
            up -= 0.1;
            tanya += 50;
        }
    }
    tanya = 0;

    while (left < -0.1) {
        if (bombZ == colZ && (bombX - tanya == colX))
            return true;
        else {
            left += 0.1;
            tanya += 50;
        }
    }
    tanya = 0;

    while (down < -0.1) {
        if (bombX == colX && (bombZ - tanya == colZ))
            return true;
        else {
            down += 0.1;
            tanya += 50;
        }
    }
    tanya = 50;
    while (right > 0.1) {
        if (bombZ == colZ)
        {
            if (bombX + tanya == colX)
            return true;
        }
            right -= 0.1;
            tanya += 50;
    }

//    if ((bombX == colX && (bombZ == colZ
//                           || bombZ == colZ - 50 || bombZ == colZ - 100
//                           || bombZ == colZ+ 50 || bombZ == colZ + 100) ||
//         (bombZ == colZ && (bombX == colX
//                            || bombX == colX - 50 || bombX == colX - 100
//                            || bombX == colX + 50 || bombX == colX + 100))))
//        return true;
    return false;
}

MyList<Explosion *> Bomb::getExplosions()
{
    return _explosions;
}

irr::scene::IAnimatedMeshSceneNode *Bomb::getBody()
{
    return body;
}

Timer Bomb::getTimer()
{
    return timer;
}

bool Bomb::getExploded()
{
    return _exploded;
}


