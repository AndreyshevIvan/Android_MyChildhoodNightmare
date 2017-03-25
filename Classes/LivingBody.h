#pragma once

#include "cocos_custom.h"

class CLivingBody
{
public:
	void InitLivingBody(int maxHealth);

	void SetDemage(int demage);
	void SetHealthBar(cocos2d::RefPtr<cocos2d::Label> healthBar);
	void HealBody(int addingHealth);

	bool IsLive();

private:
	void CLivingBody::UpdateHealthBar();

	int m_maxHealth = 1;
	int m_health = 1;
	cocos2d::RefPtr<cocos2d::Label> m_healthBar;
};