#include "CustomMap.h"
#include <iostream>

USING_NS_CC;
using namespace std;

namespace
{
	const char OBSTACLES_LAYER_NAME[] = "obstacles";

	const char SHADOW_LAYER_NAME[] = "shadow_spawns";
	const char PLAYER_SPAWN[] = "player_spawn";
	const char ENEMY_SPAWN[] = "enemy_shadow_spawn";
}

template <typename T,class TClass>
void transfer_elements(vector<TClass> &dstVect, const vector<TClass> &srcVect, T && transferEvent)
{
	std::for_each(srcVect.begin(), srcVect.end(), [&](TClass element) {
		transferEvent(element);
		dstVect.push_back(element);
	});
}

template <class TContainer, class TPredicate>
void erase_if(TContainer &container, TPredicate && predicate)
{
	auto removePredicate = [&](auto &element) {
		return predicate(element);
	};
	auto newEnd = remove_if(begin(container), end(container), removePredicate);

	container.erase(newEnd, container.end());
}

bool CCustomMap::init(const std::string &tmxFile)
{
	m_mapName = tmxFile;
	scheduleUpdate();
	bool isLoad = (
		initWithTMXFile(tmxFile) &&
		LoadObstacles() &&
		LoadUnits());

	return isLoad;
}
bool CCustomMap::LoadObstacles()
{
	TMXObjectGroup* group = TMXTiledMap::getObjectGroup(OBSTACLES_LAYER_NAME);
	try
	{
		for (Value object : group->getObjects())
		{
			m_obstacles.push_back(AsRect(object.asValueMap()));
		}
	}
	catch (const std::exception &)
	{
		return false;
	}
	return true;
}
bool CCustomMap::LoadUnits()
{
	TMXObjectGroup* playerLayer = TMXTiledMap::getObjectGroup(PLAYER_SPAWN);
	TMXObjectGroup* shadowLayer = TMXTiledMap::getObjectGroup(SHADOW_LAYER_NAME);

	try
	{
		m_heroSpawnCoord = LoadSingleCoordinate(playerLayer);
		m_shadowCoords = LoadAllCoordinates(shadowLayer);
	}
	catch (const std::exception &)
	{
		return false;
	}

	m_unitsCoords.insert(std::make_pair(GameUnit::SHADOW, m_shadowCoords));

	return true;
}
std::vector<cocos2d::Vec2> CCustomMap::LoadAllCoordinates(TMXObjectGroup* group)
{
	std::vector<cocos2d::Vec2> coordinates;

	for (Value object : group->getObjects())
	{
		ValueMap map = object.asValueMap();
		Rect rect = AsRect(map);
		coordinates.push_back(rect.origin);
	}

	return coordinates;
}
cocos2d::Vec2 CCustomMap::LoadSingleCoordinate(TMXObjectGroup* group) const
{
	auto objects = group->getObjects();
	const ValueMap map = objects.begin()->asValueMap();
	const Rect rect = AsRect(map);

	return rect.origin;
}

void CCustomMap::update(float delta)
{
	UpdateBullets();
}
void CCustomMap::UpdateBullets()
{
	auto bulletErasePredicate = [&](CBullet* pBullet) {
		bool isDead = (!CanStandOn(pBullet->getBoundingBox()) || !pBullet->IsDistanceValid());
		if (isDead)
		{
			removeChild(pBullet);
			pBullet->onExit();
		}
		return isDead;
	};

	auto updateBullets = [&](std::vector<RefPtr<CBullet>> &bullets) {
		erase_if(bullets, bulletErasePredicate);
	};

	updateBullets(m_playerBullets);
}

bool CCustomMap::CanStandOn(const Rect &body)
{
	auto isIntersects = [=](const Rect &rect) {
		return rect.intersectsRect(body);
	};

	return !std::any_of(m_obstacles.begin(), m_obstacles.end(), isIntersects);
}

std::string CCustomMap::GetMapName() const
{
	return m_mapName;
}
Vec2 CCustomMap::GetHeroWorldPosition() const
{
	return convertToWorldSpace(m_heroSpawnCoord);
}
std::vector<Vec2> CCustomMap::GetUnitsWorldPositions(GameUnit unitType) const
{
	if (unitType == GameUnit::PLAYER)
	{
		return { GetHeroWorldPosition() };
	}

	std::vector<Vec2> positions = m_unitsCoords.at(unitType);
	for (Vec2 & pos : positions)
	{
		pos = convertToWorldSpace(pos);
	}
	return positions;
}

void CCustomMap::AddPlayerBullets(Bullets playerBullets)
{
	auto add_to_child = [&](Node* child) {
		addChild(child);
	};

	transfer_elements(m_playerBullets, playerBullets, add_to_child);
}
void CCustomMap::AddEnemy(CPuppet* enemy)
{
	if (!enemy)
	{
		return;
	}

	m_enemies.push_back(enemy);
	addChild(enemy);
}

void CCustomMap::AddPlayer(CPuppet* player)
{
	addChild(player);
}

Rect CCustomMap::AsRect(const ValueMap &properties) const
{
	Rect rect;
	rect.origin.x = properties.at("x").asFloat();
	rect.origin.y = properties.at("y").asFloat();
	rect.size.width = properties.at("width").asFloat();
	rect.size.height = properties.at("height").asFloat();

	return rect;
}

void CCustomMap::Pause(bool isPause)
{
	auto childrens = this->getChildren();
	std::for_each(childrens.begin(), childrens.end(), [&](Node* child) {
		if (isPause)
		{
			child->pause();
		}
		else
		{
			child->resume();
		}
	});
}