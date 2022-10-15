/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-axel.derbisz
** File description:
** ECS
*/

#ifndef ECS_HPP_
#define ECS_HPP_

#include <bitset>
#include <array>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

class Entity;
class Component;
class System;

using ComponentID  = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
    static ComponentID lastID = 0u;
    return (lastID++);
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponent = 100;
constexpr std::size_t maxGroups = 100;


using ComponentBitSet = std::bitset<maxComponent>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component *, maxComponent>;

class Component {
    public:
        Entity *_entity;
        virtual void init() {}
        virtual void update() {}
        virtual void draw() {}
        virtual ~Component() {}
};

class Entity {
    private:
        bool _active = true;
        std::vector<std::unique_ptr<Component>> _components;
        ComponentArray _componentsArray;
        ComponentBitSet _componentsBitset;
        GroupBitSet groupBitset;
    public:
        System &manager;
        Entity(System &mManager) : manager(mManager) {}
        void update()
        {
            for (auto &c: _components) c->update();
        }
        void draw()
        {
            for (auto &c : _components) c->draw();
        }
        bool isActive() const { return _active; }
        void destroy() {_active = false;}

        bool hasGroup(Group mGroup)
        {
            return groupBitset[mGroup];
        }

        void addGroup(Group mGroup);
        void delGroup(Group mGroup)
        {
            groupBitset[mGroup] = false;
        }

        template <typename T> bool hasComponent() const
        {
            return _componentsBitset[getComponentTypeID<T>()];
        }

        template <typename T, typename... TArgs>
        T& addComponent(TArgs&&... mArgs)
        {
            T* c(new T(std::forward<TArgs>(mArgs)...));
            c->_entity = this;
            std::unique_ptr<Component> uPtr{ c };
            _components.emplace_back(std::move(uPtr));
            _componentsArray[getComponentTypeID<T>()] = c;
            _componentsBitset[getComponentTypeID<T>()] = true;
            c->init();
            return (*c);
        }
        template <typename T> T& getComponent() const
        {
            auto ptr(_componentsArray[getComponentTypeID<T>()]);
            return *static_cast<T*>(ptr);
        }
};

class System {
    public:
        void update()
        {
            for (auto &e : _entitys) {
                    e->update();
            }
        }
        void draw()
        {
            for (auto &e : _entitys) {
                    e->draw();
            }
        }
        void refresh()
        {
            for (auto i(0u); i < maxGroups; ++i) {
                auto &v(groupedEntities[i]);
                v.erase(
                    std::remove_if(std::begin(v), std::end(v),
                    [i](Entity *mEntity)
                    {
                        return !mEntity->isActive() || !mEntity->hasGroup(i);
                    }),
                        std::end(v));
                }

            _entitys.erase(std::remove_if(std::begin(_entitys), std::end(_entitys),
                [](const std::unique_ptr<Entity> &mEntity) {
                return !mEntity->isActive();
            }),
            std::end(_entitys));
        }

        void AddToGroup(Entity *mEntity, Group mGroup)
        {
            groupedEntities[mGroup].emplace_back(mEntity);
        }

        std::vector<Entity *> &getGroup(Group mGroup)
        {
            return groupedEntities[mGroup];
        }

        Entity& addEntity()
        {
            Entity *e = new Entity(*this);
            std::unique_ptr<Entity> uPtr{ e };
            _entitys.emplace_back(std::move(uPtr));
            return (*e);
        }

        std::vector<std::unique_ptr<Entity>> &getVectorEntitys()
        {
            return _entitys;
        }
    private:
        std::vector<std::unique_ptr<Entity>> _entitys;
        std::array<std::vector<Entity *>, maxGroups> groupedEntities;
};

#endif /* !ECS_HPP_ */
