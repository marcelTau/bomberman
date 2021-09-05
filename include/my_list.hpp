/*
** EPITECH PROJECT, 2021
** B_YEP_400_BER_4_1_indiestudio_karl_erik_stoerzel
** File description:
** my_list.hpp
*/

#ifndef B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_MY_LIST_HPP
#define B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_MY_LIST_HPP

#include <list>

template<typename T1>
class MyList : public std::list<T1>
{
public:
    T1 operator [](unsigned int i);
};

template<typename T1>
T1 MyList<T1>::operator[](unsigned int index)
{
    auto it = this->begin();
    for (int i = 0; i < index && i < this->size(); i++)
    {
////        if (i == this->size())
////            this->push_back(T1());
        it++;
    }
    return *it;
}

#endif //B_YEP_400_BER_4_1_INDIESTUDIO_KARL_ERIK_STOERZEL_MY_LIST_HPP
