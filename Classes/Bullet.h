#pragma once

#include "cocos_custom.h"

class CBullet : public cocos2d::Node
{
public:
	static cocos2d::RefPtr<CBullet> CreateAKBullet();
	static cocos2d::RefPtr<CBullet> CreateShootgunBullet();
	static cocos2d::RefPtr<CBullet> CreatePistolBullet();

	void update(float delta) override;

private:
	static cocos2d::RefPtr<CBullet> Create();

	cocos2d::RefPtr<cocos2d::Sprite> m_body;
	float m_speed = 0;

};