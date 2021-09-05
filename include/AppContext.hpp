/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** AppContext.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_APPCONTEXT_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_APPCONTEXT_HPP

#include <irrlicht.h>

enum class GameState {
    Menu,
    PauseMenu,
    New,
    Save,
    Load,
    Settings,
    HowToPlay,
    Game,
    GameOver,
};

typedef struct
{
    irr::IrrlichtDevice *device;
    irr::s32 counter;
    irr::gui::IGUIListBox *listbox;
    GameState state;
    bool muteMusic;
    bool muteSound;

    bool isPaused;

    int saveState;
    bool needSave;
    bool needLoad;

    bool needGame;
    int playerNbr;
    int mapSize;
} SAppContext;

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_APPCONTEXT_HPP
