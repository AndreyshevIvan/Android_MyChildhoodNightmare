#pragma once
#include "cocos_custom.h"
#include "IPuppeteer.h"
#include "Puppet.h"
#include "PlayerController.h"

class CHeroPuppeteer : protected IPuppeteer
{
public:
	void SetPuppet(CPuppet *hero);
	void SetController(CPlayerController *controller);

	cocos2d::Vec2 GetPuppetPos() override;
	std::shared_ptr<CPlayerController> GetController();

protected:
	void OnEnter() override;
	void Update(float delta) override;
	void OnExit() override;

	RunState GetMoveState() override;
	bool GetJumpState() override;

private:
	CPuppetPtr m_hero;
	std::shared_ptr<CPlayerController> m_controller;

};

typedef std::unique_ptr<CHeroPuppeteer> CHeroPuppeteerPtr;
