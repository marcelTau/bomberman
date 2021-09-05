#include "AIBot.hpp"
#include "Character.hpp"
#include "Floor.hpp"
#include "vector3d.h"
#include "Timer.hpp"

AIBot::AIBot(SAppContext &ctx, VisualMap &map, const int &playerIdx)
    : Character(ctx, map, playerIdx)
{
    moveIdx = 4;
    goingBack = 0;
    shouldDropBomb = false;
    bombsMax = 1;
    lastSteps.push(this->body->getPosition());
    next =  {0, 0};
    current = {0, 0};
    lastCurrent = {0, 0};
    timer.startTimer();
}

AIBot::~AIBot()
{
}

bool AIBot::dropBomb(GameEventReceiver &receiver)
{
    shouldDropBomb = true;
    goingBack = 10;
    return true;
}

bool AIBot::update(GameEventReceiver &receiver)
{
    move(receiver);

    return shouldDropBomb;
}

std::string AIBot::serialize()
{
    SerializeHelper s;
    s.beginKey("AIBot");

    s.addXML(Character::serialize());

    s.endKey("AIBot");
    return s.getXML();
}

bool AIBot::customMove(irr::core::vector3df target)
{
    const irr::u32 now = context->device->getTimer()->getTime();
    auto currentPos = this->body->getPosition();
    auto dir = target - currentPos;

    if (goingBack != 0 && target.getDistanceFrom(currentPos) < 10) {
        goingBack--;
    }

    frameDeltaTime = (irr::f32)(now - then) / 1000.f;
    then = now;

    dir.Y = 0;

    if (dir.getLength() > MOVEMENT_SPEED * frameDeltaTime) {
        target = currentPos + dir * (MOVEMENT_SPEED * frameDeltaTime) / dir.getLength();
    }

    target.Y = currentPos.Y;
    this->body->setPosition(target);
    return false;
}

void AIBot::checkNextMove(irr::core::vector3df &target, GameEventReceiver &receiver)
{
    auto currentMap = map->getMap();

    for (auto [type, coord] : currentMap) {
        if (coord.x == next.x && coord.y == next.y) {
            if (type == Floor::Type::WALL) {
                checkTurn();
            }
            if (type == Floor::Type::BOX) {
                dropBomb(receiver);
                checkTurn();
            } else {
                shouldDropBomb = false;
            }
            if (type == Floor::Type::EMPTY) {
                customMove(target);
            }
        }
    }
}

void AIBot::move(GameEventReceiver &receiver)
{
    auto target = this->body->getPosition();
    int blockSize = 25;

    current.x = round(abs((target.X + 300) / 50));
    current.y = round(abs((target.Z - 300) / 50));
    switch (moveIdx % 4) {
        case 0: //UP
            this->body->setRotation(irr::core::vector3df(0, 270, 0));
            target.Z += blockSize;
            break;
        case 1: //right
            this->body->setRotation(irr::core::vector3df(0, 0, 0));
            target.X += blockSize;
            break;
        case 2: //down
            this->body->setRotation(irr::core::vector3df(0, 90, 0));
            target.Z -= blockSize;
            break;
        case 3: //left
            this->body->setRotation(irr::core::vector3df(0, 180, 0));
            target.X -= blockSize;
            break;
    }
    changeMovementState();
    next.x = round(abs((target.X + 300) / 50));
    next.y = round(abs((target.Z - 300) / 50));
    checkNextMove(target, receiver);
    if (timer.isFinished())
        checkRandomTurn(target, receiver);
}

void AIBot::checkRandomTurn(irr::core::vector3df &target, GameEventReceiver
&receiver)
{
    auto currentMap = map->getMap();

    srand(time(NULL));
    int i = rand() % 12;
    if (getNext() == Floor::EMPTY && getBehind() == Floor::EMPTY) {
        timer = Timer(1000);
        timer.startTimer();
        switch (moveIdx % 4) {
        case 0: //UP
            for (auto[type, coord] : currentMap) {
                if (coord.x == next.x + 1 &&
                    coord.y == next.y + 1) {
                    if (type == Floor::EMPTY && i > 2) {
                        moveIdx++;
                        return;
                    }
                }
                if (coord.x == next.x - 1 &&
                    coord.y == next.y + 1) {
                    if (type == Floor::EMPTY && i > 2) {
                        moveIdx--;
                        return;
                    }
                }
            }
            break;
        case 1: //right
            for (auto[type, coord] : currentMap) {
                if (coord.x == next.x - 1 &&
                    coord.y == next.y + 1) {
                    if (type == Floor::EMPTY && i > 2) {
                        moveIdx++;
                        return;
                    }
                }
                if (coord.x == next.x - 1 &&
                    coord.y == next.y - 1) {
                    if (type == Floor::EMPTY && i > 2) {
                        moveIdx--;
                        return;
                    }
                }
            }
            break;
        case 2: //down
            for (auto[type, coord] : currentMap) {
                if (coord.x == next.x - 1 &&
                    coord.y == next.y - 1) {
                    if (type == Floor::EMPTY && i > 2) {
                        moveIdx++;
                        return;
                    }
                }
                if (coord.x == next.x + 1 &&
                    coord.y == next.y - 1) {
                    if (type == Floor::EMPTY && i > 2) {
                        moveIdx--;
                        return;
                    }
                }
            }
            break;
        case 3: //left
            for (auto[type, coord] : currentMap) {
                if (coord.x == next.x + 1 &&
                    coord.y == next.y - 1) {
                    if (type == Floor::EMPTY && i > 2) {
                        moveIdx++;
                        return;
                    }
                }
                if (coord.x == next.x + 1 &&
                    coord.y == next.y + 1) {
                    if (type == Floor::EMPTY && i > 2) {
                        moveIdx--;
                        return;
                    }
                }
            }
            break;
        }
    }
}

Floor::Type AIBot::getNext()
{
    auto currentMap = map->getMap();

    for (auto [type, coord] : currentMap) {
        switch (moveIdx % 4) {
            case 0: //UP
                if (coord.x == current.x && coord.y == current.y - 1)
                    return type;
            case 1: //right
                if (coord.x == current.x + 1 && coord.y == current.y)
                    return type;
            case 2: //down
                if (coord.x == current.x && coord.y == current.y + 1)
                    return type;
            case 3: //left
                if (coord.x == current.x - 1 && coord.y == current.y)
                    return type;
        }
    }
    return Floor::EMPTY;
}

Floor::Type AIBot::getBehind()
{
    auto currentMap = map->getMap();

    for (auto [type, coord] : currentMap) {
        switch (moveIdx % 4) {
            case 0: //UP
                if (coord.x == current.x && coord.y == current.y + 1)
                    return type;
            case 1: //right
                if (coord.x == current.x - 1 && coord.y == current.y)
                    return type;
            case 2: //down
                if (coord.x == current.x && coord.y == current.y - 1)
                    return type;
            case 3: //left
                if (coord.x == current.x + 1 && coord.y == current.y)
                    return type;
        }
    }
    return Floor::EMPTY;
}

void AIBot::checkTurn()
{
    auto currentMap = map->getMap();

    switch (moveIdx % 4) {
        case 0: //UP
            for (auto[type, coord] : currentMap) {
                if (coord.x == next.x + 1 &&
                    coord.y == next.y + 1) {
                    if (type == Floor::EMPTY) {
                        moveIdx++;
                        return;
                    }
                }
                if (coord.x == next.x - 1 &&
                    coord.y == next.y + 1) {
                    if (type == Floor::EMPTY) {
                        moveIdx--;
                        return;
                    }
                }
            }
            moveIdx += 2;
            break;
        case 1: //right
            for (auto[type, coord] : currentMap) {
                if (coord.x == next.x - 1 &&
                    coord.y == next.y + 1) {
                    if (type == Floor::EMPTY) {
                        moveIdx++;
                        return;
                    }
                }
                if (coord.x == next.x - 1 &&
                    coord.y == next.y - 1) {
                    if (type == Floor::EMPTY) {
                        moveIdx--;
                        return;
                    }
                }
            }
            moveIdx += 2;
            break;
        case 2: //down
            for (auto[type, coord] : currentMap) {
                if (coord.x == next.x - 1 &&
                    coord.y == next.y - 1) {
                    if (type == Floor::EMPTY) {
                        moveIdx++;
                        return;
                    }
                }
                if (coord.x == next.x + 1 &&
                    coord.y == next.y - 1) {
                    if (type == Floor::EMPTY) {
                        moveIdx--;
                        return;
                    }
                }
            }
            moveIdx += 2;
            break;
        case 3: //left
            for (auto[type, coord] : currentMap) {
                if (coord.x == next.x + 1 &&
                    coord.y == next.y - 1) {
                    if (type == Floor::EMPTY) {
                        moveIdx++;
                        return;
                    }
                }
                if (coord.x == next.x + 1 &&
                    coord.y == next.y + 1) {
                    if (type == Floor::EMPTY) {
                        moveIdx--;
                        return;
                    }
                }
            }
            moveIdx += 2;
            break;
    }
}