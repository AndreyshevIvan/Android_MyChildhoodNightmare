#include "Weapon.h"
#include <iostream>

USING_NS_CC;

namespace
{
	const float PISTOL_COLDOWN = 0.5f;
	const float SHOOTGUN_COLDOWN = 0.5f;
	const float AK_COLDOWN = 0.20f;

	const Vec2 SHOOTGUN_BULLET_OFFSET = Vec2(0, 20);
}

void CWeapon::SetBullet(RefPtr<CBullet> bullet)
{
	m_bullet = bullet;
}
void CWeapon::SetColdown(float coldown)
{
	m_coldown = coldown;
}
void CWeapon::SetHost(Node *host)
{
	m_host = host;
}
int CWeapon::GetAmmoCount()
{
	return m_ammo;
}
void CWeapon::update(float delta)
{
	if (m_currColdown < m_coldown)
	{
		m_currColdown += delta;
	}
}
bool CWeapon::IsReady()
{
	bool isColdownEnd = (m_currColdown >= m_coldown);
	bool isAmmoEnough = (m_ammo > 0);

	return isColdownEnd && isAmmoEnough;
}
Bullets CWeapon::CreateBullets(Direction direction)
{
	Bullets bullets;
	auto bullet = m_bullet->CloneAndStart(m_host->getPosition(), direction);
	bullets.push_back(bullet);

	return bullets;
}
Bullets CWeapon::Fire(Direction direction)
{
	Bullets bullets;
	if (!IsReady())
	{
		return bullets;
	}

	bullets = CreateBullets(direction);
	m_currColdown = 0;
	m_ammo--;

	return bullets;
}

RefPtr<CPistol> CPistol::Create(Node *host)
{
	RefPtr<CPistol> weapon = make_node<CPistol>();
	RefPtr<CBullet> pistolBullet = CBullet::CreatePistolBullet();

	weapon->SetBullet(pistolBullet);
	weapon->SetColdown(PISTOL_COLDOWN);
	weapon->SetHost(host);
	weapon->addChild(pistolBullet);
	weapon->scheduleUpdate();

	return weapon;
}

RefPtr<CShootgun> CShootgun::Create(Node *host)
{
	RefPtr<CShootgun> weapon = make_node<CShootgun>();
	RefPtr<CBullet> shootgunBullet = CBullet::CreateShootgunBullet();

	weapon->SetBullet(shootgunBullet);
	weapon->SetColdown(SHOOTGUN_COLDOWN);
	weapon->SetHost(host);
	weapon->addChild(shootgunBullet);
	weapon->scheduleUpdate();

	return weapon;
}
Bullets CShootgun::CreateBullets(Direction direction)
{
	Bullets bullets;
	Vec2 topPos = m_host->getPosition() + SHOOTGUN_BULLET_OFFSET;
	Vec2 bottomPos = m_host->getPosition() - SHOOTGUN_BULLET_OFFSET;

	auto bulletTop = m_bullet->CloneAndStart(topPos, direction);
	auto bulletMiddle = m_bullet->CloneAndStart(m_host->getPosition(), direction);
	auto bulletBottom = m_bullet->CloneAndStart(bottomPos, direction);

	bullets.push_back(bulletTop);
	bullets.push_back(bulletMiddle);
	bullets.push_back(bulletBottom);
	m_currColdown = 0;

	return bullets;
}

RefPtr<CAkWeapon> CAkWeapon::Create(Node *host)
{
	RefPtr<CAkWeapon> weapon = make_node<CAkWeapon>();
	RefPtr<CBullet> akBullet = CBullet::CreateAKBullet();

	weapon->SetBullet(akBullet);
	weapon->SetColdown(AK_COLDOWN);
	weapon->SetHost(host);
	weapon->addChild(akBullet);
	weapon->scheduleUpdate();

	return weapon;
}