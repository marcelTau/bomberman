/*
** EPITECH PROJECT, 2021
** bomberman
** File description:
** SerializeHelper.hpp
*/

#ifndef BOMBERMAN_SERIALIZEHELPER_HPP
#define BOMBERMAN_SERIALIZEHELPER_HPP

#include "sstream"
#include "iostream"

class SerializeHelper
{
private:
    std::stringstream xmlCode;
    int tabs = 0;
public:
    SerializeHelper() = default;
    explicit SerializeHelper(const std::string& code, bool subXML) : xmlCode(
        subXML ?
        code.substr(code.find('\n') + 1, code.find_last_of('<') - code.find('\n') - 1)
        :
        code)
    {
    }
    explicit SerializeHelper(const std::string& code) : xmlCode(code) {}
    static std::string FindKeyValue(const std::string& xmlCode, const std::string& key);
    static std::string GetKeyName(const std::string& xmlCode);
    std::string GetNextKey();
    void addKeyValue(const std::string& key, const std::string& value);
    void beginKey(const std::string& key);
    void endKey(const std::string& key);
    void insertValue(const std::string& value);
    void addXML(const std::string& xml);

    std::string getXML();
};

#endif //BOMBERMAN_SERIALIZEHELPER_HPP
