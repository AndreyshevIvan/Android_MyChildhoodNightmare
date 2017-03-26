#pragma once

#include "cocos_custom.h"
#include "Bullet.h"

class CWeapon : public cocos2d::Node
{
public:
	static cocos2d::RefPtr<CWeapon> CreatePistol();
	static cocos2d::RefPtr<CWeapon> CreateShootgun();
	static cocos2d::RefPtr<CWeapon> CreateAk();
	cocos2d::RefPtr<CBullet> CreateBullet();
	void update(float delta) override;

private:
	static cocos2d::RefPtr<CWeapon> Create();
	void SetBullet(cocos2d::RefPtr<CBullet> bullet);

	cocos2d::RefPtr<CBullet> m_bullet;

	float m_coldown = 0;
	float m_currColdown = 0;
	int m_ammo = 0;
	int m_maxAmmo = 0;

};