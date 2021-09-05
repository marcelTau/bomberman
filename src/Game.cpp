/*
** EPITECH PROJECT, 2019
** FILE_NAME
** File description:
** FILE DESCRIPTION
*/

#include "../include/Game.hpp"

#include <utility>
#include <iostream>
#include "AIBot.hpp"

Game::Game()
{
    _map = nullptr;
    _powerUpHandler = nullptr;
    _floor = nullptr;
    _context = createContext();
    _context.state = GameState::Menu;
    _driver = _context.device->getVideoDriver();
    _gameReceiver = new GameEventReceiver();
    _context.device->setEventReceiver(_gameReceiver);
    _winner = 0;

    for (int i = 0; i < TEXTPATHSLENGTH; i += 1) {
        std::pair<Buttons, irr::video::ITexture *> tmp;
        tmp.first = static_cast<Buttons>(i + 100);
        tmp.second = _driver->getTexture(textPaths[i]);
        _imageList.push_back(tmp);
    }
}

void Game::createMap()
{
    try {
        _map = new VisualMap(_context, _mapTemplate, _size);
    } catch (AssetLoadError &e) {
        std::cerr << e.getMessage() << std::endl;
        exit(84);
    } catch (SceneError &e) {
        std::cerr << e.getMessage() << std::endl;
        exit(84);
    }
    MyList<Cube *> map = _map->getBlocks();
}

SAppContext Game::createContext()
{
    irr::video::E_DRIVER_TYPE driver_type = irr::video::EDT_OPENGL;
    irr::IrrlichtDevice *device = irr::createDevice(driver_type,
                                                    irr::core::dimension2d<irr::u32>(1920, 1080),
                                                    16, false, false, false, nullptr);
    device->setWindowCaption(L"Best Bomberman");
    device->setResizable(true);

    SAppContext context;
    context.device = device;
    context.counter = 0;
    context.muteMusic = false;
    context.muteSound = false;
    context.isPaused = false;
    context.saveState = 0;
    context.needSave = false;
    context.needLoad = false;
    context.needGame = true;
    context.playerNbr = 0;
    context.mapSize = 0;
    return context;
}


void Game::play()
{
    _sounds->backMusic();
    while (_context.device->run()) {
        if (_context.state != GameState::Game) {
            this->updateMenu();
            continue;
        }

        if (_context.needGame) {
            if (_context.mapSize != 0 && _context.playerNbr != 0)
                createGame();
            else {
                _context.state = GameState::New;
                continue;
            }
        }

        for (auto & player : _players)
        {
            if (player->update(*_gameReceiver) && isDropPossible(player))
            {
                Bomb *b = new Bomb(_context, _sounds, player);
                b->drop();
                _bombs.push_back(b);
            }
        }
        HandleExplosion();
        getExplosions();
        if (_gameReceiver->IsKeyDown(irr::KEY_ESCAPE) ||
        _gameReceiver->IsKeyDown(irr::KEY_KEY_P)) {
            _context.isPaused = true;
            _context.state = GameState::PauseMenu;
            _gameReceiver->setIsKeyDown(irr::KEY_ESCAPE, false);
            _gameReceiver->setIsKeyDown(irr::KEY_KEY_P, false);
        }
        _driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        _powerUpHandler->loop(_players);
        _map->display();
        _driver->endScene();
        checkLevel();
    }
}

bool Game::isDropPossible(Character *player)
{
    auto it = _bombs.begin();

    int i = 0;
    if (!player->getUnlimitedBombs())
    {
        for (; it != _bombs.end(); it++) {
            if ((*it)->getPLayer() == player)
                ++i;
        }
        if (i >= player->getBombsMax())
            return false;
    }

    auto position = player->getBody()->getPosition();
    position.X = player->calcMiddle(position.X);
    position.Z = player->calcMiddle(position.Z);
    position.Y = 10;

    for (it = _bombs.begin(); it != _bombs.end(); it++)
    {
        if ((*it)->getBody()->getPosition() == position)
            return false;
    }
    return true;
}


std::vector<float> Game::getFireSurround( MyList<Cube *> map, irr::core::vector3d<irr::f32> pos
) const
{
    std::vector<float> surround;
    float up = 0.1f;
    float right = 0.1f;
    float down = -0.1f;
    float left = -0.1f;

    std::list<std::string>::iterator it;

    std::pair<int, int> Coord;
    std::vector<std::pair<int, int>> wallsCoord;
    MyList<Cube *> _walls;
        for (int i = 0; i < map.size(); ++i) {
            if (map[i]->getType() == 2)

            _walls.push_back(map[i]);

        }
    for (int i = 0; i < _walls.size(); ++i) {
        irr::core::vector3d<irr::f32> cubePos = _walls[i]->getbody()->getPosition();
        Coord.first = cubePos.X;
        Coord.second = cubePos.Z;
        wallsCoord.push_back(Coord);
    }

    int tanya = 50;
    while (up < 0.5) {

        Coord.first = pos.X;
        Coord.second = pos.Z + tanya;
        //std::vector<std::pair<int, int>>::iterator it;
        if (std::find(wallsCoord.begin(), wallsCoord.end(), Coord) != wallsCoord.end())
        {
            break;
        }
        else
        {
            up = up  + 0.1f;
            tanya += 50;
        }
    }
    tanya = 50;

    while (left > -0.5) {


        Coord.first = pos.X - tanya;
        Coord.second = pos.Z;
        if (std::find(wallsCoord.begin(), wallsCoord.end(), Coord) != wallsCoord.end())
        {

            break;
        }
        else
        {
            left = left  - 0.1f;
            tanya += 50;
        }
    }

    tanya = 50;

    while (right < 0.5) {

        Coord.first = pos.X + tanya;
        Coord.second = pos.Z;
        if (std::find(wallsCoord.begin(), wallsCoord.end(), Coord) != wallsCoord.end())
        {

            break;
        }
        else
        {
            right = right  + 0.1f;
            tanya += 50;
        }
    }

    tanya = 50;

    while (down > -0.5) {

        Coord.first = pos.X;
        Coord.second = pos.Z - tanya;
        if (std::find(wallsCoord.begin(), wallsCoord.end(), Coord) != wallsCoord.end())
        {

            break;
        }
        else
        {
            down = down  - 0.1f;
            tanya += 50;
        }
    }


    surround.push_back(up);
    surround.push_back(right);
    surround.push_back(down);
    surround.push_back(left);

    return surround;

}


std::vector<float> Game::getSurround(irr::core::vector3d<irr::f32> pos, Character *player) const
{

    std::vector<float> surround;
    float up = 0.3f;
    float right = 0.3f;
    float down = -0.3f;
    float left = -0.3f;

    MyList<Cube *> map = _map->getBlocks();
    if (player->getFireUp())
         return getFireSurround(map, pos);

    for (int i = 0; i < map.size(); ++i)

    {
        if (map[i]->getType() == 2) {
            irr::core::vector3d<irr::f32> cubePos = map[i]->getbody()->getPosition();
            ///if the wall is one or two squres higher
            if ((cubePos.Z == pos.Z + 50 || cubePos.Z == pos.Z + 100) \
            && cubePos.X == pos.X) {
                up = 0.1f;
            }
            ///if the wall is to the right
            if ((cubePos.X == pos.X + 50 || cubePos.X == pos.X + 100) \
            && cubePos.Z == pos.Z) {
                right = 0.1f;
            }
            /// if the wall is lower
            if (cubePos.X == pos.X && \
            (cubePos.Z == pos.Z - 50 || cubePos.Z == pos.Z - 100))
            //if ((cubePos.Z == pos.Z - 50 || cubePos.Z == pos.Z - 100) \
            //&& cubePos.X == pos.X)
                down = -0.1f;

            ///if the wall is on the left
            if ((cubePos.X == pos.X - 50 || cubePos.X == pos.X - 100) \
            && cubePos.Z == pos.Z)
                left = -0.1f;
        }

    }

    surround.push_back(up);
    surround.push_back(right);
    surround.push_back(down);
    surround.push_back(left);

    return surround;

}

void Game::getExplosions() {
    auto it = _bombs.begin();

    while (it != _bombs.end()) {
        if (!(*it)->getExploded() && (*it)->getTimer().isFinished()) {
            (*it)->initExplosion(getSurround((*it)->getBody()->getAbsolutePosition(), (*it)->getPLayer
            ()));
            _sounds->explode();
        } else if ((*it)->getExploded() && (*it)->getTimer().isFinished()) {
            (*it)->stopExplosion();
            delete _bombs[it - _bombs.begin()];
            it = _bombs.erase(it);
            continue;
        }
        it++;
    }
}

Game::~Game()
{
    //_context.device->drop();
    if (!_context.needGame) {
        delete _map;
        delete _gameReceiver;
        delete _driver;
        delete _powerUpHandler;
        delete _floor;
    }
    delete _sounds;
}

void Game::safe(int n)
{
    std::ofstream os;
    os.open("./games/save" + std::to_string(n) + ".xml");
    SerializeHelper sh;
    sh.beginKey("save" + std::to_string(n));
    sh.addKeyValue("size", std::to_string(_size));
    sh.addXML(_floor->serialize());
    for (auto & _player : _players)
        sh.addXML(_player->serialize());
    sh.addXML(_map->serialize());
    sh.endKey("save" + std::to_string(n));
    os << R"(<?xml version="1.0" encoding="ISO-8859-1"?>)" << std::endl << sh.getXML();
    os.close();
}

void Game::showMenu(GameState state, Menu *menu)
{
    while (_context.device->run() && _context.state == state)
    {
        _driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        menu->getGuiEnv()->drawAll();
        _driver->endScene();
    }
}

void Game::updateMenu()
{
    switch (_context.state) {
        case GameState::Menu: {
            if (!_context.needGame) {
                unload();
                _context.needGame = true;
            }
            Menu *menu = build_main_menu(_context, _imageList, _driver);
            auto *reciever = new MainMenuEventReceiver(_context);
            _context.device->setEventReceiver(reciever);
            showMenu(GameState::Menu, menu);
            delete reciever;
            menu->clearGUI();
            delete menu;
            break;
        }
        case GameState::New: {
            Menu *menu = build_new_menu(_context, _imageList, _driver);
            auto *reciever = new NewMenuEventReceiver(_context, menu->getElementList());
            _context.device->setEventReceiver(reciever);
            showMenu(GameState::New, menu);
            delete reciever;
            menu->clearGUI();
            delete menu;
            break;
        }
        case GameState::Save: {
            Menu *menu = build_save_menu(_context, _imageList, _driver);
            auto *reciever = new SaveMenuEventReceiver(_context);
            _context.device->setEventReceiver(reciever);
            showMenu(GameState::Save, menu);
            delete reciever;
            menu->clearGUI();
            delete menu;
            if (!checkSaveOrLoad())
                _context.state = GameState::Load;
            break;
        }
        case GameState::Load: {
            Menu *menu = build_load_menu(_context, _imageList, _driver);
            auto *reciever = new LoadMenuEventReceiver(_context);
            _context.device->setEventReceiver(reciever);
            showMenu(GameState::Load, menu);
            delete reciever;
            menu->clearGUI();
            delete menu;
            if (!checkSaveOrLoad())
                _context.state = GameState::Load;
            break;
        }
        case GameState::Settings: {
            Menu *menu = build_settings_menu(_context, _imageList, _driver);
            auto *reciever = new SettingsMenuEventReceiver(_context, _sounds,
                                                           menu->getElementList());
            _context.device->setEventReceiver(reciever);
            showMenu(GameState::Settings, menu);
            delete reciever;
            menu->clearGUI();
            delete menu;
            break;
        }
        case GameState::HowToPlay: {
            Menu *menu = build_how_to_play_menu(_context, _imageList, _driver);
            auto *reciever = new HowToPlayMenuEventReceiver(_context);
            _context.device->setEventReceiver(reciever);
            showMenu(GameState::HowToPlay, menu);
            delete reciever;
            menu->clearGUI();
            delete menu;
        }
        case GameState::PauseMenu: {
            Menu *menu = build_pause_menu(_context, _imageList, _driver);
            auto *reciever = new PauseMenuEventReceiver(_context);
            _context.device->setEventReceiver(reciever);
            showMenu(GameState::PauseMenu, menu);
            delete reciever;
            menu->clearGUI();
            delete menu;
            break;
        }
        case GameState::GameOver: {
            Menu *menu = build_game_over_menu(_context, _imageList, _driver,
                                              _winner);
            auto *reciever = new GameOverMenuEventReceiver(_context);
            _context.device->setEventReceiver(reciever);
            showMenu(GameState::GameOver, menu);
            delete reciever;
            menu->clearGUI();
            delete menu;
            break;
        }
        default:
            break;
    }
    _context.device->setEventReceiver(_gameReceiver);
}

void Game::createGame()
{
    _size = _context.mapSize;
    _playerNumber = _context.playerNbr;
    _floor = new Floor(9, _playerNumber, _size * 5, _size * 5);
    _mapTemplate = _floor->getTemplate();
    createMap();
    _powerUpHandler = new PowerUpHandler(_context, _sounds);
    int i;
    for (i = 0; i < _playerNumber; i++)
        _players.push_back(new Player(_context, *_map, i));
    for (int j = i; j < (4 - _playerNumber) + i; j++)
        _players.push_back(new AIBot(_context, *_map, j));
    _bombs.clear();
    _context.needGame = false;
}

bool Game::load(int n)
{
    std::ifstream file("./games/save" + std::to_string(n) + ".xml");
    std::stringstream ss;
    std::string line;
    std::string before;
    if (file.is_open())
    {
        file >> line;
        file >> line;
        file >> line;
        file >> line;
        while (line != before)
        {
            before  = line;
            ss << line << std::endl;
            file >> line;
        }
        file.close();
    } else {
        std::cerr << "Could not open File from save state " << n << std::endl;
        return false;
    }
    if (!_context.needGame)
        unload();
    std::string code = ss.str();
    SerializeHelper sh(code, true);

    std::string size = SerializeHelper::FindKeyValue(code, "size");
    _size = stoi(size);

    std::string sub_node;
    std::string xmlFloor = SerializeHelper::FindKeyValue(code, "Floor");
    std::string xmlVisualMap = SerializeHelper::FindKeyValue(code, "VisualMap");
    _floor = new Floor(xmlFloor, xmlVisualMap);
    _mapTemplate = _floor->getTemplate();
    _map = new VisualMap(_context, _mapTemplate, _size);

    _powerUpHandler = new PowerUpHandler(_context, _sounds);

    std::string node = sh.GetNextKey();
    while (!node.empty())
    {
        std::string object = SerializeHelper::GetKeyName(node);
        if (object == "Player")
        {
            auto *p = new Player(_context, *_map);
            p->deserialize(node);
            _players.push_back(p);
        }
        else if (object == "AIBot")
        {
            auto aiB = new AIBot(_context, *_map);
            aiB->deserialize(node);
            _players.push_back(aiB);
        }
        else if (object == "Floor" || object == "VisualMap") {
            // here happens nothing
         }
        node = sh.GetNextKey();
    }
    _context.needGame = false;
    return true;
}

void Game::randomPowerUpSpawn(float x, float z)
{
    srand(time(NULL));
    int i = rand() % 6;
    if (i == 0)
    {
        _powerUpHandler->addPowerUp(SpeedUp_t, x, z);
    }
    if (i == 1)
    {
        _powerUpHandler->addPowerUp(FireUp_t, x, z);
    }
    if (i == 2)
    {
        _powerUpHandler->addPowerUp(BombUp_t, x, z);
    }
}


bool Game::HandleExplosion()
{

    for (auto &bomb : _bombs)
    {
        auto expos = bomb->getExplosions();
        for (auto &expo : expos)
        {
            for (auto &player : _players)
            {
                if (player->checkCollision(
                    expo->getParticleSceneNode()->getTransformedBoundingBox()))
                {
                    if (bomb->beShureCollision(player->getBody()->getPosition())) {
                        if (player->isAlive()) {
                            _sounds->allah();
                            player->kill();
                        }
                    }
                }
            }
            auto blocks = _map->getBlocks();
            for (auto &box : blocks)
            {
                if (box->getbody()->isVisible())
                {
                    if (box->HandleCollision(
                        expo->getParticleSceneNode()->getTransformedBoundingBox()))
                    {
                        if (bomb->beShureCollision(box->getbody()->getPosition()) &&
                            bomb->getExploded())
                        {
                            randomPowerUpSpawn(box->getbody()->getPosition().X,
                                               box->getbody()->getPosition().Z);
                            _map->setMap(box->getCoordinates(),Floor::Type::EMPTY);
                            box->getbody()->setPosition(irr::core::vector3df(-5000));
//                            box->getbody()->setVisible(false);
                        }
                    }
                }
            }
        }
    }
    return true;
}

void Game::checkLevel()
{
    int i = 0;
    for (auto &player : _players)
    {
        if (player->isAlive())
            i++;
    }
    if (i < 2 ||
        (!_players[0]->isAlive() && _playerNumber == 1) ||
        (!_players[0]->isAlive() && !_players[1]->isAlive() &&
        _playerNumber == 2)) {
        _context.state = GameState::GameOver;
        if (_players[0]->isAlive())
            _winner = 1;
        else if (_players[1]->isAlive() && _playerNumber == 2)
            _winner = 2;
        else
            _winner = 0;
        unload();
    }
}

bool Game::checkSaveOrLoad()
{
    if (_context.needSave) {
        safe(_context.saveState);
        _context.needSave = false;
        return true;
    }
    if (_context.needLoad) {
        if (load(_context.saveState))
            _context.needLoad = false;
        else {
            _context.needLoad = false;
            return false;
        }
    }
    return true;
}

void Game::unload()
{
    _context.device->closeDevice();
    _context.device->run();
    _context.device->drop();
    irr::video::E_DRIVER_TYPE driver_type = irr::video::EDT_OPENGL;
    irr::IrrlichtDevice *device = irr::createDevice(driver_type,
                                                    irr::core::dimension2d<irr::u32>(1920, 1080),
                                                    16, false, false, false, nullptr);
    device->setWindowCaption(L"Best Bomberman");
    device->setResizable(true);
    _context.device = device;
    _driver = _context.device->getVideoDriver();

    _imageList.clear();
    for (int i = 0; i < TEXTPATHSLENGTH; i += 1) {
        std::pair<Buttons, irr::video::ITexture *> tmp;
        tmp.first = static_cast<Buttons>(i + 100);
        tmp.second = _driver->getTexture(textPaths[i]);
        _imageList.push_back(tmp);
    }

    _context.counter = 0;
    _players.clear();
    _bombs.clear();
    delete _map;
    _mapTemplate.clear();
    delete _powerUpHandler;
    _mapTemplate = _floor->getTemplate();
    delete _gameReceiver;
    _gameReceiver = new GameEventReceiver();
    _context.device->setEventReceiver(_gameReceiver);
    //_powerUpHandler = new PowerUpHandler(_context, _sounds);
    _context.needGame = true;
}
