#pragma once

#include "cocos_custom.h"
#include "IPlayerWeapon.h"

namespace
{
	const int MAX_AMMO = 2;
}

class CWeapon
	: public cocos2d::Node
	, public IPlayerWeapon
{
public:
	void update(float delta) override;
	Bullets Fire(Direction direction) final;

	int GetAmmoCount() override;

protected:
	cocos2d::Node *m_host;
	cocos2d::RefPtr<CBullet> m_bullet;
	float m_currColdown = 0;

	virtual Bullets CreateBullets(Direction direction);

	void SetBullet(cocos2d::RefPtr<CBullet> bullet);
	void SetColdown(float coldown);
	void SetHost(cocos2d::Node *host);

private:
	float m_coldown = 0;
	int m_ammo = MAX_AMMO;
	int m_maxAmmo = MAX_AMMO;

	bool IsReady();
};

class CPistol : public CWeapon
{
public:
	static cocos2d::RefPtr<CPistol> Create(cocos2d::Node *host);
};

class CShootgun : public CWeapon
{
public:
	static cocos2d::RefPtr<CShootgun> Create(cocos2d::Node *host);
	Bullets CreateBullets(Direction direction) override;
};

class CAkWeapon : public CWeapon
{
public:
	static cocos2d::RefPtr<CAkWeapon> Create(cocos2d::Node *host);
};