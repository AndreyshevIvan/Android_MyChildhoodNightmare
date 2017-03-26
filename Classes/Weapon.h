#pragma once

#include "cocos_custom.h"
#include "IPlayerWeapon.h"

namespace
{
	const int MAX_AMMO = 99;
}

class CWeapon
	: public cocos2d::Node
	, public IPlayerWeapon
{
public:
	void update(float delta) override;
	bool IsReady() override;
	std::vector<cocos2d::RefPtr<CBullet>> Fire(Direction direction) override;

	void SetBullet(cocos2d::RefPtr<CBullet> bullet);
	void SetColdown(float coldown);
	void SetHost(cocos2d::Node *host);

	int GetAmmoCount();

protected:
	cocos2d::Node *m_host;
	cocos2d::RefPtr<CBullet> m_bullet;
	float m_currColdown = 0;

private:
	float m_coldown = 0;
	int m_ammo = 100;
	int m_maxAmmo = MAX_AMMO;

};

class CPistol
	: public CWeapon
{
public:
	static cocos2d::RefPtr<CPistol> Create(cocos2d::Node *host);
};

class CShootgun
	: public CWeapon
{
public:
	static cocos2d::RefPtr<CShootgun> Create(cocos2d::Node *host);
	std::vector<cocos2d::RefPtr<CBullet>> Fire(Direction direction) override;
};

class CAkWeapon
	: public CWeapon
{
public:
	static cocos2d::RefPtr<CAkWeapon> Create(cocos2d::Node *host);
};