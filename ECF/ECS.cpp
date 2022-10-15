/*
** EPITECH PROJECT, 2022
** Game_test
** File description:
** ECS
*/

#include "ECS.hpp"

void Entity::addGroup(Group mGroup)
{
    groupBitset[mGroup] = true;
    manager.AddToGroup(this, mGroup);
}