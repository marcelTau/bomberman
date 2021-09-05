/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** PlayerEventHandling.hpp
*/

#ifndef BOMBERMAN_PLAYEREVENTHANDLING_HPP
#define BOMBERMAN_PLAYEREVENTHANDLING_HPP

#include "irrlicht.h"

class GameEventReceiver : public irr::IEventReceiver
{
public:
    GameEventReceiver();

    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    bool OnEvent(const irr::SEvent &event) final;
    bool IsKeyDown(irr::EKEY_CODE keyCode) const;
    void setIsKeyDown(irr::EKEY_CODE keyCode, bool value);
};

#endif //BOMBERMAN_PLAYEREVENTHANDLING_HPP
