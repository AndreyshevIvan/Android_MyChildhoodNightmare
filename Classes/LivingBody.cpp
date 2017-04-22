#include "LivingBody.h"

USING_NS_CC;

namespace
{

}

void CLivingBody::InitLivingBody(int maxHealth)
{
	m_maxHealth = maxHealth;
	m_health = m_maxHealth;
}

void CLivingBody::SetDemage(int demage)
{
	m_health -= demage;
	UpdateHealthBar();
}

void CLivingBody::SetHealthBar(cocos2d::RefPtr<cocos2d::Label> healthBar)
{
	m_healthBar = healthBar;
	UpdateHealthBar();
}

void CLivingBody::UpdateHealthBar()
{
	if (m_healthBar)
	{
		std::string health = (m_health > 0) ? std::to_string(m_health) : "0";
		m_healthBar->setString(health);
	}
}

void CLivingBody::HealBody(int addingHealth)
{
	if (m_health + addingHealth >= m_maxHealth)
	{
		m_health = m_maxHealth;
	}
	else
	{
		m_health += addingHealth;
	}
	UpdateHealthBar();
}

bool CLivingBody::IsLive()
{
	return (m_health >= m_maxHealth);
}