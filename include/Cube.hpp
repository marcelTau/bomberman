#include "AppContext.hpp"
#include "Floor.hpp"
#include "Error.hpp"
#include "IXML.hpp"
//                     meshPath       texturePath
static const std::pair<irr::io::path, irr::io::path>  assetPath[7] = {
    std::make_pair("media/WoodenBox.3ds", "media/maroccan3.png"), // Empty
    std::make_pair("media/WoodenBox.3ds", "media/marmor.png"), // Box
    std::make_pair("media/WoodenBox.3ds", "media/marmor4.png"), // Wall
};

class Cube : IXML
{
public:
    Cube(SAppContext &context, Floor::Type blockType, Coordinate cord);
    ~Cube();
    void addCollision(irr::scene::IAnimatedMeshSceneNode *body);
    std::string serialize() final;
    void deserialize(std::string xmlCode) final;
    bool HandleCollision(const irr::core::aabbox3d<irr::f32>& object);
    irr::scene::IAnimatedMeshSceneNode *getbody();
    Floor::Type getType() const;
    Coordinate getCoordinates();
private:
    Floor::Type type;
    Coordinate coordinate;
    irr::scene::ISceneManager *smgr;
    irr::scene::IAnimatedMeshSceneNode *body;
    irr::scene::ITriangleSelector *selector;
    bool _visible = true;
};
