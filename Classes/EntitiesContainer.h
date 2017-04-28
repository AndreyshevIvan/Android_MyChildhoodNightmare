#pragma once
#include "cocos_custom.h"
#include "Puppet.h"

enum class GameUnit
{
	PLAYER,
	SHADOW,
	CLOWN,
	GHOST,
	SPIDER,
};

typedef std::pair<cocos2d::Rect, std::string> LevelDoor;
typedef std::vector<cocos2d::Vec2> Coordinates;
typedef std::map<GameUnit, Coordinates> UnitsCoords;

template <class TContainer>
void clear_entities(TContainer &container)
{
	std::for_each(begin(container), end(container), [&](auto &element) {
		element->onExit();
	});
	container.clear();
}

class CEntitiesContainer
{
public:

protected:
	void CleanEntities()
	{
		m_obstacles.clear();
		m_doors.clear();
		clear_entities(m_enemies);
		clear_entities(m_playerBullets);
	}

	std::vector<cocos2d::Rect> m_obstacles;
	std::vector<LevelDoor> m_doors;
	CBulletsPack m_playerBullets;
	std::vector<CPuppetPtr> m_enemies;

};
