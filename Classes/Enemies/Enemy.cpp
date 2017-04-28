#include "Enemies/Enemy.h"
#include <iostream>

USING_NS_CC;

bool CEnemy::PersonalInit()
{
	return (InitBody() && InitAnimations() && InitTactics());
}

void CEnemy::Spawn(const Vec2 &position)
{
	setPosition(position);
}

void CEnemy::PersonalUpdate(float delta)
{
	UpdateWorldInfo(delta);
	ChooseTactic();
	DoTactic(delta);
}