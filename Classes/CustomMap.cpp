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
	auto removePredicate = [&](auto &element) {
		return predicate(element);
	};
	auto newEnd = remove_if(begin(container), end(container), removePredicate);

	container.erase(newEnd, container.end());
}

bool CCustomMap::init(const std::string &tmxFile)
{
	scheduleUpdate();
	return initWithTMXFile(tmxFile) && LoadObstacles() && LoadUnits();
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
	TMXObjectGroup* group = TMXTiledMap::getObjectGroup(UNITS_LAYER_NAME);
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

template <class T>
void CCustomMap::TransferFromVect(std::vector<T> &destVect, std::vector<T> &sourceVect, Node* parent)
{
	for (auto element : sourceVect)
	{
		destVect.push_back(element);
		if (parent)
		{
			parent->addChild(element);
		}
	}
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

void CCustomMap::AddPlayerBullets(Bullets playerBullets)
{
	TransferFromVect(m_playerBullets, playerBullets, this);
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