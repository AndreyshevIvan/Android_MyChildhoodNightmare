#pragma once
#include "cocos_custom.h"
#include "IMapPhysics.h"
#include "Puppet.h"

class CCustomMap
	: public cocos2d::TMXTiledMap
	, public IMapPhysics
{
public:
	bool init(const std::string& tmxFile);
	void Pause(bool isPause) override;

	void update(float delta) override;
	void UpdateBullets();

	cocos2d::Vec2 GetHeroWorldPosition() const;
	std::vector<cocos2d::Vec2> GetEnemyWorldPositions() const;
	
	void AddPlayerBullets(Bullets bullet) override;
	void AddEnemy(CPuppet* enemy) override;
	void AddPlayer(CPuppet* player) override;


	bool CanStandOn(const cocos2d::Rect &body) override;
		
private:
	bool LoadObstacles();
	bool LoadUnits();
	template <class T> void TransferFromVect(std::vector<T> &destVect, std::vector<T> &sourceVect, cocos2d::Node* parent);
	cocos2d::Rect AsRect(const cocos2d::ValueMap &properties)const;

	std::vector<cocos2d::Rect> m_obstacles;
	std::vector<cocos2d::Vec2> m_enemyPositions;

	Bullets m_playerBullets;
	std::vector<cocos2d::RefPtr<CPuppet>> m_enemies;

	cocos2d::Vec2 m_heroPosition;
};