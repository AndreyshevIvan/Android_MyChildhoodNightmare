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
	virtual bool InitTactics() { return true; };
	void Spawn(const cocos2d::Vec2 &position) override;

	bool IsTriggerML();
	bool IsTriggerMR();
	bool IsTriggerBL();
	bool IsTriggerBR();
	bool IsCatchTarget();

protected:
	bool PersonalInit() override;

	void PersonalUpdate(float delta) override;
	virtual void UpdateWorldInfo(float delta) {};
	virtual void ChooseTactic() {};
	virtual void DoTactic(float delta) {};

	std::function<void()> *m_tactic;
	std::function<void()> m_idle;
	std::function<void()> m_pursuite;

	EnemyActivity m_activity;

private:
	void UpdateTriggers();

	cocos2d::Rect m_targetArea;
	cocos2d::Point m_handMiddleLeft;
	cocos2d::Point m_handMiddleRight;
	cocos2d::Point m_handBottomLeft;
	cocos2d::Point m_handBottomRight;
};