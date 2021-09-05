#include "Character.hpp"

static const int positions[4][2] = {
    {0, 0},
    {1, 0},
    {0, 1},
    {1, 1}
};

Character::Character(SAppContext &ctx, VisualMap &vmap, const int &idx)
    : context(&ctx), map(&vmap), playerIndex(idx)
{
    MOVEMENT_SPEED = 100.0f;
    currentMovementState = irr::scene::EMAT_STAND;
    extraSpeedFactor = 1.f;

    this->smgr = context->device->getSceneManager();
    this->driver = context->device->getVideoDriver();
    then = context->device->getTimer()->getTime();

    auto [x, z] = map->getMaxCoordinates();
    auto [multX, multZ] = positions[idx];
    int blockSize = 50;
    x = (x - 2) * blockSize * multX;
    z = (z - 2) * blockSize * multZ;

    irr::core::vector3df pos = { static_cast<float>(-250 + x), 0, static_cast<float>(250 - z)};

    initCharacter(pos);
    this->selector = this->smgr->createOctreeTriangleSelector(this->body->getMesh(), this->body);
    this->body->setTriangleSelector(this->selector);

    map->addCollision(body);
}

Character::~Character()
{
    this->selector->drop();
    //this->body->drop();
}

bool Character::getUnlimitedBombs() const
{
    return unlimitedBombs;
}

int Character::getBombsMax() {
    return this->bombsMax;
}

int Character::calcMiddle(int coordinate)
{
    int n = coordinate / 50;
    int min_x = 50 * n;
    int max_x = 50 * (n + (n >= 0 && coordinate >= 0 ? + 1 : - 1));

    return abs(min_x - coordinate) < abs(max_x - coordinate) ? min_x : max_x;
}

void Character::initCharacter(irr::core::vector3df _pos)
{
    irr::scene::IAnimatedMesh *mesh;

    if ((mesh = smgr->getMesh("media/sydney.md2")) == NULL) {
        AssetLoadErrorMac("Can't load 'media/sydney.md2'");
    }
    if ((this->body = smgr->addAnimatedMeshSceneNode(mesh)) == NULL) {
        SceneErrorMac("Could not add AnimatedMeshSceneNode");
    }

    this->body->setMD2Animation(currentMovementState);
    this->body->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->body->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));

    auto pos = this->body->getPosition();
    pos.X = _pos.X;
    pos.Y += 45;
    pos.Z = _pos.Z;

    this->body->setPosition(pos);
}

irr::scene::IAnimatedMeshSceneNode *Character::getBody()
{
    return this->body;
}


/* use this function to create Collision between multiple Players or monsters */
void Character::addCollision(irr::scene::IAnimatedMeshSceneNode *_body)
{
    auto *anim = smgr->createCollisionResponseAnimator(selector, _body,
            irr::core::vector3df(10, 10, 10),
            irr::core::vector3df(0, 0, 0));
    _body->addAnimator(anim);
    anim->drop();
}

bool Character::checkCollision(const irr::core::aabbox3d<irr::f32>& object) const
{
    return object.intersectsWithBox(this->body->getTransformedBoundingBox());
}

void Character::setExtraSpeed(irr::f32 newExtraSpeed)
{
    this->extraSpeedFactor = newExtraSpeed;
}

bool Character::isAlive() const
{
    return alive;
}

void Character::kill()
{
    alive = false;
    body->setVisible(false);
    bombsMax = 0;
}

bool Character::getFireUp() const
{
    return fireUp;
}

void Character::revive()
{
    alive = true;
}

void Character::setFire(bool enable)
{
    fireUp = enable;
}

void Character::setUnlimitedBombs(bool enabled)
{
    unlimitedBombs = enabled;
}

void Character::changeMovementState()
{
    if (currentMovementState == irr::scene::EMAT_STAND) {
        currentMovementState = irr::scene::EMAT_RUN;
        this->body->setMD2Animation(currentMovementState);
    }
}

void Character::moveUp(irr::core::vector3df &pos)
{
    this->body->setRotation(irr::core::vector3df(0, 270, 0));
    pos.Z += (MOVEMENT_SPEED * frameDeltaTime) * extraSpeedFactor;
    changeMovementState();
}

void Character::moveDown(irr::core::vector3df &pos)
{
    this->body->setRotation(irr::core::vector3df(0, 90, 0));
    pos.Z -= (MOVEMENT_SPEED * frameDeltaTime) * extraSpeedFactor;
    changeMovementState();
}

void Character::moveRight(irr::core::vector3df &pos)
{
    this->body->setRotation(irr::core::vector3df(0, 0, 0));
    pos.X += (MOVEMENT_SPEED * frameDeltaTime) * extraSpeedFactor;
    changeMovementState();
}

void Character::moveLeft(irr::core::vector3df &pos)
{
    this->body->setRotation(irr::core::vector3df(0, 180, 0));
    pos.X -= (MOVEMENT_SPEED * frameDeltaTime) * extraSpeedFactor;
    changeMovementState();
}


void Character::deserialize(std::string xmlCode)
{
    std::string xpos = SerializeHelper::FindKeyValue(xmlCode, "X");
    std::string ypos = SerializeHelper::FindKeyValue(xmlCode, "Y");
    std::string zpos = SerializeHelper::FindKeyValue(xmlCode, "Z");
    std::string playerIndexS = SerializeHelper::FindKeyValue(xmlCode, "playerIndex");
    std::string aliveS = SerializeHelper::FindKeyValue(xmlCode, "alive");
    std::string fireUpS = SerializeHelper::FindKeyValue(xmlCode, "fireUp");
    std::string unlimitedBombsS = SerializeHelper::FindKeyValue(xmlCode, "unlimitedBombs");

    body->setPosition(irr::core::vector3df(stof(xpos), stof(ypos), stof(zpos)));
    playerIndex = stoi(playerIndexS);
    alive = stoi(aliveS);
    fireUp = stoi(fireUpS);
    unlimitedBombs = stoi(unlimitedBombsS);
    if (!alive)
        this->kill();
}

std::string Character::serialize()
{
    SerializeHelper s;
    s.beginKey("Position");
    s.addKeyValue("X", std::to_string(this->getBody()->getPosition().X));
    s.addKeyValue("Y", std::to_string(this->getBody()->getPosition().Y));
    s.addKeyValue("Z", std::to_string(this->getBody()->getPosition().Z));
    s.endKey("Position");

    s.addKeyValue("playerIndex", std::to_string(playerIndex));
    s.addKeyValue("extraSpeedFactor", std::to_string(extraSpeedFactor));
    s.addKeyValue("alive", std::to_string(alive));
    s.addKeyValue("fireUp", std::to_string(fireUp));
    s.addKeyValue("unlimitedBombs", std::to_string(unlimitedBombs));
    return s.getXML();
}
