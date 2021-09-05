/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** IXML.hpp
*/

#ifndef BOMBERMAN_IXML_HPP
#define BOMBERMAN_IXML_HPP

#include "string"
#include "sstream"
#include "SerializeHelper.hpp"

class IXML
{
public:
    virtual std::string serialize() = 0;
    virtual void deserialize(std::string xmlCode) = 0;
};

#endif //BOMBERMAN_IXML_HPP
