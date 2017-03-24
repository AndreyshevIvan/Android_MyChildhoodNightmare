#pragma once
#include "cocos_custom.h"
#include "IPuppeteer.h"
#include "Puppet.h"
#include "PlayerController.h"

class CHeroPuppeteer : protected IPuppeteer
{
public:
	void SetPuppet(CPuppet *hero);

	cocos2d::Vec2 GetPuppetPos() override;

protected:
	void OnEnter() override;
	void Update(float delta) override;
	void OnExit() override;

	PuppetState GetMoveState() override;
	PuppetState GetJumpState() override;

private:
	CPuppetPtr m_hero;
	std::unique_ptr<CPlayerController> m_controller;

};

typedef std::unique_ptr<CHeroPuppeteer> CHeroPuppeteerPtr;
