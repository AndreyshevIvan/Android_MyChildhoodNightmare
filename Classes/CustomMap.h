#pragma once
#include "cocos_custom.h"
#include "IMapPhysics.h"

class CCustomMap
	: public cocos2d::TMXTiledMap
	, public IMapPhysics
{
public:
	bool init(const std::string& tmxFile);

	cocos2d::Vec2 GetHeroWorldPosition()const;
	std::vector<cocos2d::Vec2> GetEnemyWorldPositions()const;

	bool CanStandOn(const cocos2d::Rect &body) override;

private:
	bool LoadObstacles();
	bool LoadUnits();
	cocos2d::Rect AsRect(const cocos2d::ValueMap &properties)const;

	std::vector<cocos2d::Rect> m_obstacles;
	std::vector<cocos2d::Vec2> m_enemyPositions;
	cocos2d::Vec2 m_heroPosition;
};