#include "CustomMap.h"
#include <iostream>

USING_NS_CC;

namespace
{
	const char C_LAYER_NAME[] = "tiles";
	const char C_OBSTACLES_LAYER_NAME[] = "obstacles";
	const char C_UNITS_LAYER_NAME[] = "units";
	const char C_PASSABILITY_PROP[] = "pass";
	const char C_HERO_TYPE_KEY[] = "hero";
	const char C_NPC_TYPE_KEY[] = "npc";

	const PhysicsMaterial obstacleMaterial = PhysicsMaterial(0, 1, 1);

#if 0
	void DumpObjectGroup(TMXObjectGroup *group)
	{
		if (!group)
		{
			CCLOG("-- objects group empty --");
			return;
		}
		CCLOG("-- objects group `%s` --", group->getGroupName().c_str());
		for (const Value &v : group->getObjects())
		{
			CCLOG("%s", v.getDescription().c_str());
		}
		CCLOG("-- objects group end --");
	}
#endif
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

bool CCustomMap::init(const std::string &tmxFile)
{
	return initWithTMXFile(tmxFile) && LoadObstacles();// && LoadUnits();
}

bool CCustomMap::LoadObstacles()
{
	TMXObjectGroup *group = TMXTiledMap::getObjectGroup(C_OBSTACLES_LAYER_NAME);
	try
	{
		for (Value object : group->getObjects())
		{
			CreateObstacleBody(object);
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
	TMXObjectGroup *group = TMXTiledMap::getObjectGroup(C_UNITS_LAYER_NAME);
	try
	{
		for (Value object : group->getObjects())
		{
			ValueMap map = object.asValueMap();
			Rect rect = AsRect(map);
			if (C_NPC_TYPE_KEY == map.at("type").asString())
			{
				m_enemyPositions.push_back(rect.origin);
			}
			if (C_HERO_TYPE_KEY == map.at("type").asString())
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

void CCustomMap::CreateObstacleBody(const Value &object)
{
	Node* obstacle = make_node<Node>();
	Rect rect = AsRect(object.asValueMap());
	PhysicsBody* body = PhysicsBody::createBox(rect.size, obstacleMaterial);
	body->setDynamic(false);
	body->setPositionOffset(Vec2(rect.getMidX(), rect.getMidY()));

	obstacle->addComponent(body);
	
	addChild(obstacle);
}

// метод `.at()` бросит исключение, если заданного ключа нет в словаре.
Rect CCustomMap::AsRect(const ValueMap &properties) const
{
	Rect rect;
	rect.origin.x = properties.at("x").asFloat();
	rect.origin.y = properties.at("y").asFloat();
	rect.size.width = properties.at("width").asFloat();
	rect.size.height = properties.at("height").asFloat();

	return rect;
}