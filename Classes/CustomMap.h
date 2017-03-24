#pragma once
#include "cocos_custom.h"

class CCustomMap
	: public cocos2d::TMXTiledMap
{
public:
	bool init(const std::string& tmxFile);

	cocos2d::Vec2 GetHeroWorldPosition()const;
	std::vector<cocos2d::Vec2> GetEnemyWorldPositions()const;

private:
	bool LoadObstacles();
	bool LoadUnits();
	void CreateObstacleBody(const cocos2d::Value &object);
	cocos2d::Rect AsRect(const cocos2d::ValueMap &properties)const;

	std::vector<cocos2d::Vec2> m_enemyPositions;
	cocos2d::Vec2 m_heroPosition;
};