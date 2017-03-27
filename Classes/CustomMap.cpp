#include "CustomMap.h"
#include <iostream>

USING_NS_CC;

namespace
{
	const char OBSTACLES_LAYER_NAME[] = "obstacles";

	const char UNITS_LAYER_NAME[] = "units_positions";
	const char PLAYER_SPAWN[] = "player_spawn";
	const char ENEMY_SPAWN[] = "enemy_shadow_spawn";
}

template <class TContainer, class TPredicate>
void erase_if(TContainer &container, TPredicate && predicate)
{
	container.erase(
		remove_if(begin(container), end(container), [&](auto &pBullet) {return predicate(pBullet);}),
		container.end()
	);
}

bool CCustomMap::init(const std::string &tmxFile)
{
	scheduleUpdate();
	return initWithTMXFile(tmxFile) && LoadObstacles() && LoadUnits();
}
bool CCustomMap::LoadObstacles()
{
	TMXObjectGroup *group = TMXTiledMap::getObjectGroup(OBSTACLES_LAYER_NAME);
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
	TMXObjectGroup *group = TMXTiledMap::getObjectGroup(UNITS_LAYER_NAME);
	try
	{
		for (Value object : group->getObjects())
		{
			ValueMap map = object.asValueMap();
			Rect rect = AsRect(map);
			if (ENEMY_SPAWN == map.at("type").asString())
			{
				m_enemyPositions.push_back(rect.origin);
			}
			if (PLAYER_SPAWN == map.at("type").asString())
			{
				m_heroPosition = rect.origin;
			}
		}
	}
	catch (const std::exception &)
	{
		return false;
	}
	return true;
}

void CCustomMap::update(float delta)
{
	UpdateBullets();
}
void CCustomMap::UpdateBullets()
{
	auto updateBullets = [&](std::vector<RefPtr<CBullet>> &bullets) {
		erase_if(bullets, [&](CBullet* pBullet) {
			bool dead = (!CanStandOn(pBullet->getBoundingBox()) || !pBullet->IsDistanceValid());
			if (dead)
			{
				pBullet->onExit();
			}
			return dead;
		});
	};

	updateBullets(m_playerBullets);
}

bool CCustomMap::CanStandOn(const cocos2d::Rect &body)
{
	bool isOnObstacle = std::any_of(m_obstacles.begin(), m_obstacles.end(), [=](const Rect &rect) {
		return rect.intersectsRect(body);
	});

	return !isOnObstacle;
}

Vec2 CCustomMap::GetHeroWorldPosition() const
{
	return convertToWorldSpace(m_heroPosition);
}
std::vector<Vec2> CCustomMap::GetEnemyWorldPositions() const
{
	std::vector<Vec2> positions(m_enemyPositions);
	for (Vec2 & pos : positions)
	{
		pos = convertToWorldSpace(pos);
	}
	return positions;
}

void CCustomMap::AddPlayerBullets(std::vector<RefPtr<CBullet>> playerBullets)
{
	for (auto bullet : playerBullets)
	{
		if (bullet)
		{
			m_playerBullets.push_back(bullet);
			addChild(bullet);
		}
	}
}
void CCustomMap::AddEnemy(CPuppet *enemy)
{
	if (enemy)
	{
		m_enemies.push_back(enemy);
	}
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