#include "Weapon.h"
#include <iostream>

USING_NS_CC;

RefPtr<CWeapon> CWeapon::Create()
{
	RefPtr<CWeapon> weapon = make_node<CWeapon>();
	return weapon;
}

RefPtr<CWeapon> CWeapon::CreatePistol()
{
	RefPtr<CWeapon> weapon = CWeapon::Create();

	if (weapon)
	{
		RefPtr<CBullet> pistolBullet = CBullet::CreatePistolBullet();
		weapon->SetBullet(pistolBullet);
	}

	return weapon;
}

RefPtr<CWeapon> CWeapon::CreateShootgun()
{
	RefPtr<CWeapon> weapon = CWeapon::Create();

	if (weapon)
	{
		RefPtr<CBullet> shootgunBullet = CBullet::CreatePistolBullet();
		weapon->SetBullet(shootgunBullet);
	}

	return weapon;
}

RefPtr<CWeapon> CWeapon::CreateAk()
{
	RefPtr<CWeapon> weapon = CWeapon::Create();

	if (weapon)
	{
		RefPtr<CBullet> akBullet = CBullet::CreatePistolBullet();
		weapon->SetBullet(akBullet);
	}

	return weapon;
}

void CWeapon::SetBullet(RefPtr<CBullet> bullet)
{
	m_bullet = bullet;
}

void CWeapon::update(float delta)
{

}

RefPtr<CBullet> CWeapon::CreateBullet()
{
	std::cout << "Fire!";
	return m_bullet;
}