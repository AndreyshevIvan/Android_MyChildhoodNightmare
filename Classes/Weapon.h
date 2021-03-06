#pragma once

#include "cocos_custom.h"
#include "Weapons/IPlayerWeapon.h"

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
	CBulletsPack Fire(Direction direction) final;
	bool IsInfinity() override;
	int GetAmmoCount() const override;

protected:
	cocos2d::Node *m_host;
	CBulletPtr m_bullet;
	float m_currColdown = 0;
	bool m_isInfinity = false;

	virtual CBulletsPack CreateBullets(Direction direction);

	void SetBullet(CBulletPtr bullet);
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
	CBulletsPack CreateBullets(Direction direction) override;
};

class CAkWeapon : public CWeapon
{
public:
	static cocos2d::RefPtr<CAkWeapon> Create(cocos2d::Node *host);
};