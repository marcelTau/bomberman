/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** EventHandling.cpp
*/

#include "../include/EventHandling.hpp"

bool MainMenuEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_GUI_EVENT)
    {
        irr::s32 id = event.GUIEvent.Caller->getID();

        switch (event.GUIEvent.EventType)
        {
            case irr::gui::EGET_SCROLL_BAR_CHANGED:
                break;
            case irr::gui::EGET_BUTTON_CLICKED:
                switch (id)
                {
                    case GUI_BUTTON_QUIT:
                        _context.device->closeDevice();
                        return true;
                    case GUI_BUTTON_NEW:
                        _context.state = GameState::New;
                        return true;
                    case GUI_BUTTON_LOAD:
                        _context.state = GameState::Load;
                        return true;
                    case GUI_BUTTON_SETTINGS:
                        _context.state = GameState::Settings;
                        return true;
                    case GUI_BUTTON_HOWTOPLAY:
                        _context.state = GameState::HowToPlay;
                        return true;
                    default:
                        break;
                }
            default:
                break;
        }
    }
    return false;
}

bool NewMenuEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_GUI_EVENT)
    {
        irr::s32 id = event.GUIEvent.Caller->getID();

        switch (event.GUIEvent.EventType)
        {
            case irr::gui::EGET_SCROLL_BAR_CHANGED:
                break;
            case irr::gui::EGET_BUTTON_CLICKED:
                switch (id)
                {
                    case GUI_BUTTON_BACK:
                        _context.state = GameState::Menu;
                        return true;
                    case GUI_BUTTON_CREATE:
                        _context.needGame = true;
                        _context.playerNbr = _playerNbr;
                        _context.mapSize = _mapSize;
                        _context.state = GameState::Game;
                        return true;
                    default:
                        break;
                }
            case irr::gui::EGET_CHECKBOX_CHANGED:
                switch (id)
                {
                    case GUI_RADIO_PLAYER1:
                        updatePlayer(GUI_RADIO_PLAYER1);
                        _playerNbr = 1;
                        return true;
                    case GUI_RADIO_PLAYER2:
                        updatePlayer(GUI_RADIO_PLAYER2);
                        _playerNbr = 2;
                        return true;
                    case GUI_RADIO_SMALL:
                        updateMap(GUI_RADIO_SMALL);
                        _mapSize = 1;
                        return true;
                    case GUI_RADIO_MEDIUM:
                        updateMap(GUI_RADIO_MEDIUM);
                        _mapSize = 2;
                        return true;
                    case GUI_RADIO_LARGE:
                        updateMap(GUI_RADIO_LARGE);
                        _mapSize = 3;
                        return true;
                    default:
                        break;
                }
            default:
                break;
        }
    }
    return false;
}

void NewMenuEventReceiver::updatePlayer(int id)
{
    for (int i = 0; i < _elemList.size(); i += 1) {
        if (_elemList[i]->getID() == GUI_RADIO_PLAYER1 ||
        _elemList[i]->getID() == GUI_RADIO_PLAYER2)
            ((irr::gui::IGUICheckBox *)_elemList[i])->setChecked(false);
        if (_elemList[i]->getID() == id)
            ((irr::gui::IGUICheckBox *)_elemList[i])->setChecked(true);

    }
}

void NewMenuEventReceiver::updateMap(int id)
{

    for (int i = 0; i < _elemList.size(); i += 1) {
        if (_elemList[i]->getID() == GUI_RADIO_SMALL ||
            _elemList[i]->getID() == GUI_RADIO_MEDIUM ||
            _elemList[i]->getID() == GUI_RADIO_LARGE)
            ((irr::gui::IGUICheckBox *)_elemList[i])->setChecked(false);
        if (_elemList[i]->getID() == id)
            ((irr::gui::IGUICheckBox *)_elemList[i])->setChecked(true);

    }
}

bool LoadMenuEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_GUI_EVENT)
    {
        irr::s32 id = event.GUIEvent.Caller->getID();

        switch (event.GUIEvent.EventType)
        {
            case irr::gui::EGET_SCROLL_BAR_CHANGED:
                break;
            case irr::gui::EGET_BUTTON_CLICKED:
                switch (id)
                {
                    case GUI_BUTTON_SAVE1:
                        _context.needLoad = true;
                        _context.saveState = 1;
                        _context.state = GameState::Game;
                        return true;
                    case GUI_BUTTON_SAVE2:
                        _context.needLoad = true;
                        _context.saveState = 2;
                        _context.state = GameState::Game;
                        return true;
                    case GUI_BUTTON_SAVE3:
                        _context.needLoad = true;
                        _context.saveState = 3;
                        _context.state = GameState::Game;
                        return true;
                    case GUI_BUTTON_SAVE4:
                        _context.needLoad = true;
                        _context.saveState = 4;
                        _context.state = GameState::Game;
                        return true;
                    case GUI_BUTTON_BACK:
                        if (_context.isPaused)
                            _context.state = GameState::PauseMenu;
                        else
                            _context.state = GameState::Menu;
                        return true;
                    default:
                        break;
                }
            default:
                break;
        }
    }
    return false;
}

bool SettingsMenuEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_GUI_EVENT)
    {
        irr::s32 id = event.GUIEvent.Caller->getID();

        switch (event.GUIEvent.EventType)
        {
            case irr::gui::EGET_SCROLL_BAR_CHANGED:
                break;
            case irr::gui::EGET_BUTTON_CLICKED:
                switch (id)
                {
                    case GUI_BUTTON_BACK:
                        if (_context.isPaused)
                            _context.state = GameState::PauseMenu;
                        else
                            _context.state = GameState::Menu;
                        return true;
                    default:
                        break;
                }
            case irr::gui::EGET_CHECKBOX_CHANGED:
                switch (id) {
                    case GUI_RADIO_MUSIC1:
                        updateMusic(GUI_RADIO_MUSIC1);
                        return true;
                    case GUI_RADIO_MUSIC2:
                        updateMusic(GUI_RADIO_MUSIC2);
                        return true;
                    case GUI_CHECK_MUSIC:
                        _context.muteMusic = !_context.muteMusic;
                        _sounds->MuteMusic(_context.muteMusic);
                        return true;
                    case GUI_CHECK_SOUND:
                        _context.muteSound = !_context.muteSound;
                        _sounds->MuteSound(_context.muteSound);
                        return true;
                    default:
                        break;
                }
            default:
                break;
        }
    }
    return false;
}

void SettingsMenuEventReceiver::updateMusic(int id)
{
    for (int i = 0; i < _elemList.size(); i += 1) {
        if (_elemList[i]->getID() == GUI_RADIO_MUSIC1 ||
        _elemList[i]->getID() == GUI_RADIO_MUSIC2)
            ((irr::gui::IGUICheckBox *)_elemList[i])->setChecked(false);
        if (_elemList[i]->getID() == id)
            ((irr::gui::IGUICheckBox *)_elemList[i])->setChecked(true);
    }
    if (id == GUI_RADIO_MUSIC1) {
        _sounds->stopBackMusic2();
        _sounds->backMusic();
    } else {
        _sounds->stopBackMusic();
        _sounds->backMusic2();
    }
}

bool PauseMenuEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_GUI_EVENT)
    {
        irr::s32 id = event.GUIEvent.Caller->getID();

        switch (event.GUIEvent.EventType)
        {
            case irr::gui::EGET_SCROLL_BAR_CHANGED:
                break;
            case irr::gui::EGET_BUTTON_CLICKED:
                switch (id)
                {
                    case GUI_BUTTON_CONTINUE:
                        _context.isPaused = false;
                        _context.state = GameState::Game;
                        return true;
                    case GUI_BUTTON_SAVE:
                        _context.state = GameState::Save;
                        return true;
                    case GUI_BUTTON_LOAD:
                        _context.state = GameState::Load;
                        return true;
                    case GUI_BUTTON_SETTINGS:
                        _context.state = GameState::Settings;
                        return true;
                    case GUI_BUTTON_MAINMENU:
                        _context.isPaused = false;
                        _context.state = GameState::Menu;
                        return true;
                    case GUI_BUTTON_QUIT:
                        _context.device->closeDevice();
                        return true;
                    default:
                        break;
                }
            default:
                break;
        }
    }
    return false;
}

bool SaveMenuEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_GUI_EVENT)
    {
        irr::s32 id = event.GUIEvent.Caller->getID();

        switch (event.GUIEvent.EventType)
        {
            case irr::gui::EGET_SCROLL_BAR_CHANGED:
                break;
            case irr::gui::EGET_BUTTON_CLICKED:
                switch (id)
                {
                    case GUI_BUTTON_SAVE1:
                        _context.needSave = true;
                        _context.saveState = 1;
                        return true;
                    case GUI_BUTTON_SAVE2:
                        _context.needSave = true;
                        _context.saveState = 2;
                        return true;
                    case GUI_BUTTON_SAVE3:
                        _context.needSave = true;
                        _context.saveState = 3;
                        return true;
                    case GUI_BUTTON_SAVE4:
                        _context.needSave = true;
                        _context.saveState = 4;
                        return true;
                    case GUI_BUTTON_BACK:
                        _context.state = GameState::PauseMenu;
                        return true;
                    default:
                        break;
                }
            default:
                break;
        }
    }
    return false;
}

bool GameOverMenuEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_GUI_EVENT)
    {
        irr::s32 id = event.GUIEvent.Caller->getID();

        switch (event.GUIEvent.EventType)
        {
            case irr::gui::EGET_SCROLL_BAR_CHANGED:
                break;
            case irr::gui::EGET_BUTTON_CLICKED:
                switch (id)
                {
                    case GUI_BUTTON_MAINMENU:
                        _context.isPaused = false;
                        _context.state = GameState::Menu;
                        return true;
                    case GUI_BUTTON_QUIT:
                        _context.device->closeDevice();
                        return true;
                    default:
                        break;
                }
            default:
                break;
        }
    }
    return false;
}

bool HowToPlayMenuEventReceiver::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_GUI_EVENT)
    {
        irr::s32 id = event.GUIEvent.Caller->getID();

        switch (event.GUIEvent.EventType)
        {
            case irr::gui::EGET_SCROLL_BAR_CHANGED:
                break;
            case irr::gui::EGET_BUTTON_CLICKED:
                switch (id)
                {
                    case GUI_BUTTON_BACK:
                        _context.state = GameState::Menu;
                        return true;
                    default:
                        break;
                }
            default:
                break;
        }
    }
    return false;
}
