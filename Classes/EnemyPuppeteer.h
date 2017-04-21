#pragma once

#include "cocos_custom.h"
#include "IPuppeteer.h"
#include "Puppet.h"

class CEnemyPuppeteer : protected IPuppeteer
{
public:
	void SetPuppet(CPuppet *enemy);
	//void SetController(CPlayerController *controller);

	cocos2d::Vec2 GetPuppetPos() override;
	//std::shared_ptr<CPlayerController> GetController();

protected:
	void OnEnter() override;
	void Update(float delta) override;
	void OnExit() override;

	RunState GetRunState() override;
	bool GetJumpState() override;
	bool GetFireState() override;
	bool GetSwitchWeaponState() override;

private:
	CPuppetPtr m_enemy;
	//std::shared_ptr<CPlayerController> m_controller;

};