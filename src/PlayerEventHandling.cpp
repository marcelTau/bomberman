/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** PlayerEventHandling.cpp
*/

#include "PlayerEventHandling.hpp"

bool GameEventReceiver::OnEvent(const irr::SEvent& event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    return false;
}

bool GameEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

void GameEventReceiver::setIsKeyDown(irr::EKEY_CODE keyCode, bool value)
{
    KeyIsDown[keyCode] = value;
}

GameEventReceiver::GameEventReceiver()
{
    for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
        KeyIsDown[i] = false;
}