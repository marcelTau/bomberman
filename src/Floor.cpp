//
// Created by oelman on 5/28/21.
//

#include <ctime>
#include <utility>
#include "../include/Floor.hpp"

void Floor::set_monster_nb()
{
    if (_level >= 1 && _level <= 10)
        _nb_monsters = 1;
    if (_level >= 10 && _level <= 19)
        _nb_monsters = 2;
}

void Floor::set_obstacle_number_for_the_level()
{
    _nb_of_item_at_start = ((_height * _width) / 10);
    _nb_of_item_per_level = _nb_of_item_at_start / 10;
    _nb_tiles = (_nb_of_item_at_start * (1.5/3)) + (_nb_of_item_per_level * _level);
    _nb_boxes = (_nb_of_item_at_start * (1/3)) + (_nb_of_item_per_level * _level);
    set_monster_nb();
}

void Floor::build_available_square_list()
{
    Coordinate cor;
    _available_squares.clear();
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            if (_template[y][x] == ' ' && x != 1 && x != _width - 2 && y != 1 && y != _height - 2) {
                cor.x = x;
                cor.y = y;
                _available_squares.push_back(cor);
            }
        }
    }
    _nb_free_squares = _available_squares.size();
}

void Floor::show_map()
{
    for (std::vector<std::string>::const_iterator i = _template.begin(); i != _template.end(); ++i)
        std::cout << *i << std::endl;
}

void Floor::set_teleport()
{
    _template[_height / 2][1] = '+'; //X
    _template[(_height) / 2][_width - 2] =  '+';
    _template[1][(_width) / 2] = '+';
    _template[_height - 2][_width / 2] = '+';
    build_available_square_list();
}


MyList<std::pair<Floor::Type, Coordinate>> Floor::getTemplate()
{
    return _map;
}

void Floor::generate_template()
{
    std::string wall;
    std::string interior;
    std::string empty;
    empty.append(_width, ' ');
    wall.append(_width, '#');
    _template.push_back(wall);
    for (int i = 0; i < _height - 2; i++) {
        _template.push_back(empty);
    }
    _template.push_back(wall);
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            if ((y % 2 == 0) && (x % 2 == 0))
                _template[y][x] = '#';
            if (x == 0 || x == _width - 1)
                _template[y][x] = '#';
        }
    }
    set_teleport();
    build_available_square_list();
    put_obstacles('+', _nb_boxes);
    put_obstacles('+', _nb_monsters); //M
    put_obstacles('+', _nb_tiles); //*
    create_map();
}

void Floor::create_map() {
    int i = 0;
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            Coordinate cord;
            Floor::Type type = Floor::Type::EMPTY;
            char c = _template[y][x];
            if (c == '#') {
                type = Floor::Type::WALL;
            }
            if (c == '+') {
                type = Floor::Type::BOX;
            }
            cord.x = x;
            cord.y = y;
            _map.push_back(std::make_pair(type, cord));
            i++;
        }
    }
}

void Floor::create_template_from_map() {
    _template.clear();
    for (int y = 0; y < _height; y++)
    {
        std::string tmp;
        for (int x = 0; x < _width; x++)
        {
            tmp += " ";
        }
        _template.push_back(tmp);
    }
    for (auto block : _map)
    {
        char c = '\0';
        switch (block.first)
        {
            case Floor::Type::EMPTY:
                c = ' ';
                break;
            case Floor::Type::WALL:
                c = '#';
                break;
            case Floor::Type::BOX:
                c = '+';
                break;
            default:
                break;
        }
        _template[block.second.y][block.second.x] = c;
    }
}

void Floor::check_and_fit_in_sizes() {
    if (_height % 2 == 0)
        _height++;
    if (_width % 2 == 0)
        _width++;
    if (_player_nb > 4)
        _player_nb = 4;
    if (_width <= 13 || _width > 100)
        _width = 13;
    if (_height <= 11 || _height > 100)
        _height = 11;
    _height += 2;
    _width += 2;
}

std::set<unsigned int> get_random_number_set(int min, int max, int amount)
{
    std::set<unsigned int> results;
    random_device rd;
    mt19937_64 generator(rd());
    uniform_int_distribution<unsigned int> dist{(unsigned)min, (unsigned)max};
    while(results.size() != amount)
    {
        results.insert(dist(generator));
    }

    return results;
}


void Floor::put_obstacles(char ch, int nb_items)
{
    std::set<unsigned int> random_set = get_random_number_set(0, _nb_free_squares - 1, nb_items);
    Coordinate cord;

    for (auto it = random_set.begin(); it !=
                                  random_set.end(); ++it)
    {
        cord = _available_squares[*it];
       _template[cord.y][cord.x] = ch;

    }
    build_available_square_list();

}

Floor::Floor(int level, int player_nb ,int width, int height)
{
    _level = level;
    _player_nb = player_nb;
    _width = width;
    _height = height;
    check_and_fit_in_sizes();
    set_obstacle_number_for_the_level();
    generate_template();
}

std::string Floor::getStringFromType(Floor::Type t)
{
    const std::map<Type, std::string> TypeStrings {
        {Type::EMPTY, "EMPTY"},
        {Type::BOX, "BOX"},
        {Type::WALL, "WALL"},
    };
    auto it = TypeStrings.find(t);
    return it == TypeStrings.end() ? "Out of range" : it->second;
}

Floor::Type Floor::getTypeFromString(std::string str)
{
    const std::map<std::string, Type> TypeStrings {
        {"EMPTY",        Type::EMPTY},
        {"BOX",          Type::BOX},
        {"WALL",         Type::WALL},
    };
    auto it = TypeStrings.find(str.substr(0, str.size() - 1));
    return it->second;
}

void Floor::deserialize(std::string xmlCode)
{
    std::string levels = SerializeHelper::FindKeyValue(xmlCode, "level");
    std::string player_nbs = SerializeHelper::FindKeyValue(xmlCode, "player_nb");
    std::string widths = SerializeHelper::FindKeyValue(xmlCode, "width");
    std::string heights = SerializeHelper::FindKeyValue(xmlCode, "height");
    std::string nb_monsterss = SerializeHelper::FindKeyValue(xmlCode, "nb_monsters");
    std::string nb_free_squaress = SerializeHelper::FindKeyValue(xmlCode, "nb_free_squares");
    std::string nb_boxess = SerializeHelper::FindKeyValue(xmlCode, "nb_boxes");
    std::string types = SerializeHelper::FindKeyValue(xmlCode, "type");
    std::string nb_tiless = SerializeHelper::FindKeyValue(xmlCode, "nb_tiles");
    std::string nb_of_item_at_starts = SerializeHelper::FindKeyValue(xmlCode, "nb_of_item_at_start");
    std::string nb_of_item_per_levels = SerializeHelper::FindKeyValue(xmlCode, "nb_of_item_per_level");

    _level = stoi(levels);
    _player_nb = stoi(player_nbs);
    _width = stoi(widths);
    _height = stoi(heights);
    _nb_monsters = stoi(nb_monsterss);
    _nb_free_squares = stoi(nb_free_squaress);
    _nb_boxes = stoi(nb_boxess);
    _type = Floor::getTypeFromString(types);
    _nb_tiles = stoi(nb_tiless);
    _nb_of_item_at_start = stoi(nb_of_item_at_starts);
    _nb_of_item_per_level = stoi(nb_of_item_per_levels);
}

std::string Floor::serialize()
{
    SerializeHelper sh;
    sh.beginKey("Floor");

    sh.addKeyValue("level", std::to_string(_level));
    sh.addKeyValue("player_nb", std::to_string(_player_nb));
    sh.addKeyValue("width", std::to_string(_width));
    sh.addKeyValue("height", std::to_string(_height));
    sh.addKeyValue("nb_monsters", std::to_string(_nb_monsters));
    sh.addKeyValue("nb_free_squares", std::to_string(_nb_free_squares));
    sh.addKeyValue("nb_boxes", std::to_string(_nb_boxes));
    sh.addKeyValue("type", Floor::getStringFromType(_type));
    sh.addKeyValue("nb_tiles", std::to_string(_nb_tiles));
    sh.addKeyValue("nb_of_item_at_start", std::to_string(_nb_of_item_at_start));
    sh.addKeyValue("nb_of_item_per_level", std::to_string(_nb_of_item_per_level));

    sh.endKey("Floor");
    return sh.getXML();
}

Floor::Floor(std::string floorXML, const std::string& mapXML)
{
    deserialize(std::move(floorXML));
    _map = deserializeMap(mapXML);
    create_template_from_map();
}

MyList<std::pair<Floor::Type, Coordinate>> Floor::deserializeMap(const std::string& mapXML)
{
    MyList<std::pair<Type, Coordinate>> list;
    SerializeHelper sh(mapXML);
    std::string node = sh.GetNextKey();
    while (!node.empty())
    {
        std::string isVisable = SerializeHelper::FindKeyValue(node, "isVisible");

        std::string ypos = SerializeHelper::FindKeyValue(node, "Y");
        std::string xpos = SerializeHelper::FindKeyValue(node, "X");
        std::string zpos = SerializeHelper::FindKeyValue(node, "Z");
        float x = stof(xpos);
        float y = stof(ypos);
        float z = stof(zpos);
        Coordinate cor
        {
            (int)(x + 300) / 50,
            (int)(z - 300) / -50
        };
        if (x != -5000)
        {
            if (stoi(isVisable) == true)
            {
                std::string types = SerializeHelper::FindKeyValue(node, "type");
                auto type = Floor::getTypeFromString(types);
                auto o = std::make_pair(type, cor);
                list.push_back(o);
            }
            else
                list.push_back(std::make_pair(Floor::Type::EMPTY, cor));
        }
        node = sh.GetNextKey();
    }
    return list;
}

int Floor::getLevel() const
{
    return _level;
}

void Floor::nextLevel()
{
    _level++;
    set_obstacle_number_for_the_level();
    _template.clear();
    generate_template();
}
