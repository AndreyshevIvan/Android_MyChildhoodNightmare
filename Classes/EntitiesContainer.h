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

class CEntitiesContainer
{
public:

protected:
	std::vector<cocos2d::Rect> m_obstacles;
	std::vector<LevelDoor> m_doors;
	CBulletsPack m_playerBullets;
	std::vector<CPuppetPtr> m_enemies;

	UnitsCoords m_unitsCoords;
	Coordinates m_shadowCoords;
	Coordinates m_clownCoords;
	Coordinates m_spiderCoords;
	Coordinates m_ghostCoords;
	cocos2d::Vec2 m_heroSpawnCoord;

	Coordinates m_healthCoords;
	Coordinates m_akAmmoCoords;
	Coordinates m_shootgunAmmoCoords;
	Coordinates m_giftCoords;
	Coordinates m_boxCoords;

};
