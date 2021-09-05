#ifndef VISUAL_MAP_HPP_
#define VISUAL_MAP_HPP_

#include "AppContext.hpp"
#include "Coordinate.hpp"
#include "IParticleAnimatedMeshSceneNodeEmitter.h"
#include "ISceneManager.h"
#include "IVideoDriver.h"
#include "my_list.hpp"
#include "Floor.hpp"
#include <iostream>
#include <vector>
#include "Cube.hpp"
#include "IXML.hpp"
using Map = MyList<std::pair<Floor::Type, Coordinate>>;

class VisualMap : IXML
{
public:
    VisualMap(SAppContext &ctx, Map &_map, int size);
    ~VisualMap();
    void display();
    void addCollision(irr::scene::IAnimatedMeshSceneNode *body);
    MyList<Cube *> getBlocks() const;
    void deserialize(std::string xmlCode) final;
    std::string serialize() final;
    Coordinate getMaxCoordinates();
    Map getMap();
    void setMap(Coordinate coord, Floor::Type type);

private:
    void initializeMap(Map &map);

private:
    /* general */
    SAppContext *context;
    irr::scene::ISceneManager *smgr;
    irr::video::IVideoDriver *driver;
    Coordinate maxCoordinates;

    MyList<Cube *> blocks;

    irr::scene::IMetaTriangleSelector *metaSelector;
    Map *map;
};

#endif //VISUAL_MAP_HPP_
