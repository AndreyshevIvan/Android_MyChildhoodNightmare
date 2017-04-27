#pragma once
#include "cocos_custom.h"
#include "IMapPhysics.h"
#include "EntitiesContainer.h"

class CCustomMap
	: public cocos2d::TMXTiledMap
	, public CEntitiesContainer
	, public IMapPhysics
{
public:
	bool init(const std::string& tmxFile);
	void Pause(bool isPause) override;

	void update(float delta) override;

	std::string GetMapName() const;
	cocos2d::Vec2 GetHeroWorldPosition() const;
	Coordinates GetUnitsWorldPositions(GameUnit unitType) const;

	void AddPlayerBullets(CBulletsPack bullet) override;
	void AddEnemy(CPuppetPtr enemy) override;
	void AddPlayer(CPuppetPtr player) override;

	bool CanStandOn(const cocos2d::Rect &body) override;

private:
	void UpdateBullets();
	void UpdateUnits() {};
	void UpdateItems() {};

	bool LoadObstacles();
	bool LoadUnits();
	Coordinates LoadAllCoordinates(cocos2d::TMXObjectGroup* group);
	cocos2d::Vec2 LoadSingleCoordinate(cocos2d::TMXObjectGroup* group) const;
	cocos2d::Rect AsRect(const cocos2d::ValueMap &properties) const;

	std::string m_name;
};
