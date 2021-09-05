/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** menu.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_MENU_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_MENU_HPP

#include "EventHandling.hpp"
#include "vector"

class Menu
{
public:
    Menu(SAppContext context, const std::vector<std::pair<Buttons,
         irr::video::ITexture *>> &imageList, irr::video::IVideoDriver *driver);
    ~Menu() = default;
    void addLabel(int i, const irr::core::position2d<irr::s32>& pos);
    void addButton(const irr::core::rect<irr::s32>& pos, int btn_enum, const
    wchar_t *tooltip);
    void addCheckBox(const irr::core::rect<irr::s32>& pos, int box_enum, bool
    value);
    void clearGUI();
    irr::video::IVideoDriver *getDriver();
    irr::gui::IGUIEnvironment *getGuiEnv();

    std::vector<irr::gui::IGUIElement *> getElementList();

private:
    std::vector<std::pair<Buttons, irr::video::ITexture *>> _imageList;
    irr::gui::IGUIEnvironment *_guienv;
    std::vector<irr::gui::IGUIElement *> _elementList;
    irr::video::IVideoDriver *_driver;
};

Menu *build_main_menu(SAppContext context, const std::vector<std::pair<Buttons,
    irr::video::ITexture *>> &_imageList, irr::video::IVideoDriver *driver);
Menu *build_new_menu(SAppContext context, const std::vector<std::pair<Buttons,
    irr::video::ITexture *>> &imageList, irr::video::IVideoDriver *driver);
Menu *build_load_menu(SAppContext context, const std::vector<std::pair<Buttons,
    irr::video::ITexture *>> &imageList, irr::video::IVideoDriver *driver);
Menu *build_settings_menu(SAppContext context, const
    std::vector<std::pair<Buttons, irr::video::ITexture *>> &imageList, irr::video::IVideoDriver *driver);
Menu *build_pause_menu(SAppContext context, const
    std::vector<std::pair<Buttons, irr::video::ITexture *>> &imageList, irr::video::IVideoDriver *driver);
Menu *build_save_menu(SAppContext context, const
    std::vector<std::pair<Buttons, irr::video::ITexture *>> &imageList, irr::video::IVideoDriver *driver);
Menu *build_game_over_menu(SAppContext context, const
std::vector<std::pair<Buttons, irr::video::ITexture *>> &imageList,
irr::video::IVideoDriver *driver, int winner);
Menu *build_how_to_play_menu(SAppContext context, const
std::vector<std::pair<Buttons, irr::video::ITexture *>> &imageList,
                           irr::video::IVideoDriver *driver);

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_MENU_HPP
