#pragma once
#include "cocos_custom.h"
#include "IMapPhysics.h"
#include "Puppet.h"

enum GameUnit
{
	PLAYER,
	SHADOW,
	CLOWN,
	GHOST,
	SPIDER,
};

typedef std::map<GameUnit, std::vector<cocos2d::Vec2>> UnitsCoords;

class CCustomMap
	: public cocos2d::TMXTiledMap
	, public IMapPhysics
{
public:
	bool init(const std::string& tmxFile);
	void Pause(bool isPause) override;

	void update(float delta) override;
	void UpdateBullets();

	std::string GetMapName() const;
	cocos2d::Vec2 GetHeroWorldPosition() const;
	std::vector<cocos2d::Vec2> GetUnitsWorldPositions(GameUnit unitType) const;

	void AddPlayerBullets(Bullets bullet) override;
	void AddEnemy(CPuppet* enemy) override;
	void AddPlayer(CPuppet* player) override;

	bool CanStandOn(const cocos2d::Rect &body) override;

private:

	bool LoadObstacles();
	bool LoadUnits();
	std::vector<cocos2d::Vec2> LoadAllCoordinates(cocos2d::TMXObjectGroup* group);
	cocos2d::Vec2 LoadSingleCoordinate(cocos2d::TMXObjectGroup* group) const;

	cocos2d::Rect AsRect(const cocos2d::ValueMap &properties) const;

	std::string m_mapName;
	std::vector<cocos2d::Rect> m_obstacles;
	Bullets m_playerBullets;
	std::vector<CPuppetPtr> m_enemies;

	cocos2d::Vec2 m_heroSpawnCoord;
	UnitsCoords m_unitsCoords;
	std::vector<cocos2d::Vec2> m_shadowCoords;
	std::vector<cocos2d::Vec2> m_clownCoords;
	std::vector<cocos2d::Vec2> m_spiderCoords;
	std::vector<cocos2d::Vec2> m_ghostCoords;

	std::vector<cocos2d::Vec2> m_healthCoords;
	std::vector<cocos2d::Vec2> m_akAmmoCoords;
	std::vector<cocos2d::Vec2> m_shootgunAmmoCoords;
	std::vector<cocos2d::Vec2> m_giftCoords;
	std::vector<cocos2d::Vec2> m_boxCoords;
};
