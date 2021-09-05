//
// Created by oelman on 5/28/21.
//

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_FLOOR_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_FLOOR_HPP

#include "../include/my_list.hpp"
#include <map>
#include <ostream>
#include <random>
#include <set>
#include <iostream>
#include <vector>
#include "Coordinate.hpp"
#include "IXML.hpp"

using std::mt19937_64;
using std::random_device;
using std::uniform_int_distribution;

class Floor : public IXML
{
public:
    enum Type
    {
        EMPTY = 0,
        BOX,
        WALL,
    };

public:
    static std::string getStringFromType(Type t);
    static Type getTypeFromString(std::string str);
    Floor(int level, int player_nb, int width, int height);
    Floor(std::string xmlFloor, const std::string& xmlMap);
    MyList<std::pair<Type, Coordinate>> getTemplate();
    void show_map();
    void deserialize(std::string xmlCode) final;
    std::string serialize() final;
    static MyList<std::pair<Type, Coordinate>> deserializeMap(const std::string& mapXML);
    int getLevel() const;
    void nextLevel();

private:
    void generate_template();
    void create_template_from_map();
    void set_obstacle_number_for_the_level();
    void set_teleport();
    void set_monster_nb();
    void put_obstacles(char obstacle_abbrev_letter, int nb_obstacles);
    void create_map();
    void check_and_fit_in_sizes();
    void build_available_square_list();

private:
    MyList<std::pair<Type, Coordinate>> _map;
    int _level = 1;
    int _player_nb = 1;
    int _width = 13;
    int _height = 11;
    int _nb_free_squares;
    Type _type;
    int _nb_boxes = 3; //default
    int _nb_tiles = 3; //default
    int _nb_monsters = 1; //default
    int _nb_of_item_at_start;
    int _nb_of_item_per_level;
    std::vector<Coordinate> _available_squares;
    std::vector<std::string> _template;
};

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_FLOOR_HPP
