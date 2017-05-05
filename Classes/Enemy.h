#pragma once

#include "cocos_custom.h"
#include "Puppet.h"

namespace
{
	enum class EnemyActivity
	{
		IDLE,
		PURSUITE,
	};
}

class CEnemy : public CPuppet
{
public:
	virtual void InitTactics() {};
	void Spawn(const cocos2d::Vec2 &position) override;

protected:
	void PersonalUpdate(float delta) override;

	std::function<void()> *m_tactic;
	std::function<void()> m_idle;
	std::function<void()> m_pursuite;

	EnemyActivity m_activity;
	cocos2d::Rect m_targetArea;
	cocos2d::Point m_handMiddleLeft;
	cocos2d::Point m_handMiddleRight;
	cocos2d::Point m_handBottomLeft;
	cocos2d::Point m_handBottomRight;

};