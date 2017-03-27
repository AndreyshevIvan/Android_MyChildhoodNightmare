#pragma once

#include "cocos_custom.h"
#include "Puppet.h"

class CEnemy : public CPuppet
{
public:
	virtual void InitTactics() {};
	void Spawn(const cocos2d::Vec2 &position) override;
	void InitEnemy();

protected:
	void PersonalUpdate(float delta) override;

private:
	std::function<void()> *m_tactic;
	std::function<void()> m_idle;
	std::function<void()> m_pursuite;

};