#pragma once

#include "cocos_custom.h"
#include "Puppet.h"

class CEnemy : public CPuppet
{
public:
	void Spawn(const cocos2d::Vec2 &position) override;

protected:
	bool PersonalInit() override;
	virtual bool InitTactics() { return true; };

	void PersonalUpdate(float delta) override;
	virtual void UpdateWorldInfo(float delta) {};
	virtual void ChooseTactic() {};
	virtual void DoTactic(float delta) {};

private:
	std::function<void()> *m_tactic;
	std::function<void()> m_idle;
	std::function<void()> m_pursuite;

};