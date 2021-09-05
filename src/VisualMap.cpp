#include "VisualMap.hpp"
#include "Coordinate.hpp"
#include "IAnimatedMesh.h"
#include "Menu.hpp"
#include "Error.hpp"

Map VisualMap::getMap()
{
    return *this->map;
}

void VisualMap::display()
{
    this->smgr->drawAll();
}

void VisualMap::initializeMap(Map &map)
{
    for (auto [type, coord] : map)
    {
        if (type == Floor::BOX)
            this->blocks.push_back(new Cube(*this->context, Floor::EMPTY, coord));
        this->blocks.push_back(new Cube(*this->context, type, coord));
    }
}

void VisualMap::addCollision(irr::scene::IAnimatedMeshSceneNode *body)
{
    auto *anim = smgr->createCollisionResponseAnimator(metaSelector, body,
            irr::core::vector3df(10, 10, 10),
            irr::core::vector3df(0.f, 0.f, 0.f));
    body->addAnimator(anim);
    anim->drop();

    for (auto &block : blocks)
        block->addCollision(body);
}

VisualMap::VisualMap(SAppContext &ctx, Map &_map, int size)
    : context(&ctx), map(&_map)
{
    this->smgr = context->device->getSceneManager();
    this->driver = context->device->getVideoDriver();

    if (!this->smgr->loadScene("media/skybox.irr"))
        AssetLoadErrorMac("Can't load 'media/skybox.irr'");

    if (size == 1)
        this->smgr->addCameraSceneNode(NULL, irr::core::vector3df(70, 375, -240),
            irr::core::vector3df(70, 0, -75));
    else if (size == 3)
        this->smgr->addCameraSceneNode(NULL, irr::core::vector3df(100, 450, -400),
                                       irr::core::vector3df(100, 0, -200));
    else
        this->smgr->addCameraSceneNode(NULL, irr::core::vector3df(85, 400, -200),
            irr::core::vector3df(85, 0, -50));

    maxCoordinates = _map.back().second;
    initializeMap(_map);

    irr::core::array<irr::scene::ISceneNode *>	walls;
    smgr->getSceneNodesFromType(irr::scene::ESNT_CUBE, walls);
    metaSelector = smgr->createMetaTriangleSelector();

    for (int i = 0; i < walls.size(); i++) {
        auto selector = smgr->createTriangleSelectorFromBoundingBox(walls[i]);
        metaSelector->addTriangleSelector(selector);
        selector->drop();
    }
}

VisualMap::~VisualMap()
{
    this->metaSelector->drop();

    for (auto &block : blocks)
        delete block;
}

MyList<Cube *> VisualMap::getBlocks() const
{
    return blocks;
}

Coordinate VisualMap::getMaxCoordinates()
{
    return maxCoordinates;
}

void VisualMap::deserialize(std::string xmlCode)
{
}

std::string VisualMap::serialize()
{
    SerializeHelper sh;
    sh.beginKey("VisualMap");
    for (auto block : blocks)
        sh.addXML(block->serialize());
    sh.endKey("VisualMap");
    return sh.getXML();
}


void VisualMap::setMap(Coordinate coord, Floor::Type newType)
{
    for (auto &it : *map) {
        if (it.second.x == coord.x && it.second.y == coord.y) {
            it.first = newType;
            return;
        }
    }
}
