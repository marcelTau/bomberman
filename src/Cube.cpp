#include "Cube.hpp"
#include "Floor.hpp"

Cube::Cube(SAppContext &context, Floor::Type  blockType, Coordinate cord)
    : type(blockType), coordinate(cord)
{
    irr::scene::IAnimatedMesh *mesh;
    irr::video::IVideoDriver *driver = context.device->getVideoDriver();

    this->smgr = context.device->getSceneManager();

    if (static_cast<int>(type) > 6)
        type = Floor::Type::WALL;

    auto [meshPath, texturePath] = assetPath[static_cast<int>(type)];
    auto [x, y] = cord;

    if ((mesh = smgr->getMesh(meshPath)) == NULL)
        AssetLoadErrorMac("Can't get mesh for block creation");
    if ((this->body = smgr->addAnimatedMeshSceneNode(mesh)) == NULL)
        SceneErrorMac("Could not add AnimatedMeshSceneNode");

    int cubeSize = 50;
    this->body->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->body->setMaterialTexture(0, driver->getTexture(texturePath));
    this->body->setScale(irr::core::vector3df(cubeSize));

    bool isGroundLevel = type == Floor::Type::EMPTY;
    if (isGroundLevel)
        this->body->setPosition(irr::core::vector3df(-300 + x * cubeSize, -10, 300 - y * cubeSize));
    else
        this->body->setPosition(irr::core::vector3df(-300 + x * cubeSize, 30, 300 - y * cubeSize));

    selector = smgr->createOctreeTriangleSelector(this->body->getMesh(), this->body);
    this->body->setTriangleSelector(selector);
}


Floor::Type Cube::getType() const
{
    return type;
}


void Cube::addCollision(irr::scene::IAnimatedMeshSceneNode *_body)
{
    auto anim = smgr->createCollisionResponseAnimator(selector, _body,
            irr::core::vector3df(10),
            irr::core::vector3df(0));
    _body->addAnimator(anim);
    anim->drop();
}

Cube::~Cube()
{
    selector->drop();
//    body->drop();
}

std::string Cube::serialize()
{
    SerializeHelper sh;
    sh.beginKey("Cube");

    sh.addKeyValue("type", Floor::getStringFromType(type));

    sh.beginKey("position");
    sh.addKeyValue("X", std::to_string(body->getPosition().X));
    sh.addKeyValue("Y", std::to_string(body->getPosition().Y));
    sh.addKeyValue("Z", std::to_string(body->getPosition().Z));
    sh.endKey("position");

    sh.addKeyValue("isVisible", std::to_string(body->isVisible()));
    sh.endKey("Cube");
    return sh.getXML();
}

void Cube::deserialize(std::string xmlCode)
{
    std::string xpos = SerializeHelper::FindKeyValue(xmlCode, "X");
    std::string ypos = SerializeHelper::FindKeyValue(xmlCode, "Y");
    std::string zpos = SerializeHelper::FindKeyValue(xmlCode, "Z");
    std::string t = SerializeHelper::FindKeyValue(xmlCode, "type");
    std::string tisVisibleS = SerializeHelper::FindKeyValue(xmlCode, "isVisible");

    type = Floor::getTypeFromString(t);
    body->setPosition(irr::core::vector3df(stof(xpos), stof(ypos), stof(zpos)));
    body->setVisible(stoi(tisVisibleS));
}

bool Cube::HandleCollision(const irr::core::aabbox3d<irr::f32> &object)
{
    if (type == Floor::BOX)
    {
        if (body->getTransformedBoundingBox().intersectsWithBox(object))
            return true;
    }
    return false;
}

irr::scene::IAnimatedMeshSceneNode *Cube::getbody()
{
    return body;
}

Coordinate Cube::getCoordinates()
{
    return coordinate;
}
