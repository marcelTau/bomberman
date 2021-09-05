/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** Character.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_CHARACTER_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_CHARACTER_HPP

#include "AppContext.hpp"
#include "Coordinate.hpp"
#include "VisualMap.hpp"
#include <irrlicht.h>

class GameEventReceiver;

class Character : public IXML
{
public:
    Character(SAppContext &ctx, VisualMap &vmap, const int &idx);
    ~Character();
    bool isAlive() const;
    void kill();
    void revive();
    void setFire(bool enable);
    void setUnlimitedBombs(bool enabled);
    void setExtraSpeed(irr::f32 newExtraSpeed);
    irr::scene::IAnimatedMeshSceneNode *getBody();
    bool getUnlimitedBombs() const;
    bool getFireUp() const;
    int getBombsMax();
    int calcMiddle(int coordinate);
    bool checkCollision(const irr::core::aabbox3d<irr::f32>& object) const;

    virtual bool update(GameEventReceiver &receiver) = 0;
    std::string serialize() override;
    void deserialize(std::string xmlCode) final;

private:
    void initCharacter(irr::core::vector3df _pos);

protected:
    /* general */
    SAppContext *context;
    irr::scene::ISceneManager *smgr;
    irr::video::IVideoDriver *driver;
    irr::scene::IAnimatedMeshSceneNode *body;

    /* movement */
    irr::u32 then;
    int playerIndex;
	irr::f32 MOVEMENT_SPEED;
    irr::f32 frameDeltaTime;
    irr::scene::EMD2_ANIMATION_TYPE currentMovementState;

    /* collision */
    irr::scene::ITriangleSelector *selector;

    /* map needed to add collision to it */
    VisualMap *map;

    /* powerUp handling */
    irr::f32 extraSpeedFactor; /* used for the SpeedUp_t powerUp */
    bool alive = true;
    bool fireUp = false;
    bool unlimitedBombs = false;
    int bombsMax = 2;

protected:
    void changeMovementState();
    void moveUp(irr::core::vector3df &pos);
    void moveDown(irr::core::vector3df &pos);
    void moveLeft(irr::core::vector3df &pos);
    void moveRight(irr::core::vector3df &pos);
    void addCollision(irr::scene::IAnimatedMeshSceneNode *_body);

    /* function that need to be overwritten by child classes */
    virtual bool dropBomb(GameEventReceiver &receiver) = 0;
    virtual void move(GameEventReceiver &receiver) = 0;
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_CHARACTER_HPP
