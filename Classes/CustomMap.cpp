#include "CustomMap.h"
#include <iostream>

USING_NS_CC;
using namespace std;

namespace
{
	const char OBSTACLES_LAYER_NAME[] = "obstacles";
	const char LEVELS_DOORS_LAYER[] = "doors";

	const std::map<GameUnit, std::string> UNITS_LAYERS = {
		{ GameUnit::PLAYER, "player" },
		{ GameUnit::SHADOW, "shadows" },
		{ GameUnit::CLOWN, "clowns" },
		{ GameUnit::GHOST, "ghosts" },
		{ GameUnit::SPIDER, "spiders" }
	};
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
	m_name = tmxFile;
	scheduleUpdate();
	bool isLoad = (
		initWithTMXFile(tmxFile) &&
		LoadObstacles() &&
		LoadDoors());

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
bool CCustomMap::LoadDoors()
{
	TMXObjectGroup* group = TMXTiledMap::getObjectGroup(LEVELS_DOORS_LAYER);
	if (!group)
	{
		return true;
	}

	try
	{
		for (Value object : group->getObjects())
		{
			auto door = AsDoor(object.asValueMap());
			m_doors.push_back(door);
		}
	}
	catch (const std::exception &)
	{
		return false;
	}
	return true;
}
Coordinates CCustomMap::LoadAllCoordinates(TMXObjectGroup* group) const
{
	if (!group)
	{
		return {};
	}

	Coordinates coordinates;

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
	if (!group)
	{
		return Vec2::ZERO;
	}

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

	auto updateBullets = [&](CBulletsPack &bullets) {
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

bool CCustomMap::GetCollideDoorKey(const cocos2d::Rect &body, std::string &doorKey)
{
	bool isIntersectsWithDoor = false;

	for (auto levelDoor : m_doors)
	{
		if (levelDoor.first.intersectsRect(body))
		{
			isIntersectsWithDoor = true;
			doorKey = levelDoor.second;
			return true;
		}
	}

	return false;
}
std::string CCustomMap::GetMapName() const
{
	return m_name;
}
Vec2 CCustomMap::GetHeroSpawnPosition() const
{
	TMXObjectGroup* playerLayer = TMXTiledMap::getObjectGroup(UNITS_LAYERS.at(GameUnit::PLAYER));
	Vec2 heroSpawn = Vec2::ZERO;

	if (playerLayer)
	{
		heroSpawn = LoadSingleCoordinate(playerLayer);
	}

	return convertToWorldSpace(heroSpawn);
}
Coordinates CCustomMap::GetUnitsSpawnPositions(GameUnit unitType) const
{
	TMXObjectGroup* unitLayer = TMXTiledMap::getObjectGroup(UNITS_LAYERS.at(unitType));
	if (!unitLayer)
	{
		return {};
	}

	Coordinates coordinates = {};

	try
	{
		coordinates = LoadAllCoordinates(unitLayer);
	}
	catch (const std::exception &) {}
	return coordinates;
}

void CCustomMap::AddPlayerBullets(CBulletsPack playerBullets)
{
	auto add_to_child = [&](Node* child) {
		addChild(child);
	};

	transfer_elements(m_playerBullets, playerBullets, add_to_child);
}
void CCustomMap::AddEnemy(CPuppetPtr enemy)
{
	if (!enemy)
	{
		return;
	}

	m_enemies.push_back(enemy);
	addChild(enemy);
}

void CCustomMap::AddPlayer(CPuppetPtr player)
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
LevelDoor CCustomMap::AsDoor(const cocos2d::ValueMap &properties) const
{
	Rect rect = AsRect(properties);
	string key = properties.at("name").asString();

	return LevelDoor(rect, key);
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