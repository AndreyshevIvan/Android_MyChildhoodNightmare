#pragma once

#include "cocos_custom.h"

enum struct Direction
{
	LEFT,
	RIGHT,
};

class CBullet : public cocos2d::Node
{
public:

	static cocos2d::RefPtr<CBullet> CreateAKBullet();
	static cocos2d::RefPtr<CBullet> CreateShootgunBullet();
	static cocos2d::RefPtr<CBullet> CreatePistolBullet();

	void update(float delta) override;
	cocos2d::RefPtr<CBullet> CloneAndStart(const cocos2d::Vec2 &position, Direction dir, int demage = 0);
	bool IsDistanceValid();

	int GetDemage() const;

	void onExit() override;

private:
	static cocos2d::RefPtr<CBullet> Create();
	void InitBody(const std::string &spritePath);

	void SetSpeed(float speed);
	void SetDemage(int demage);

	GameSprite m_body;
	float m_speed = 100;
	float m_distance = 0;
	int m_demage = 0;

};

typedef cocos2d::RefPtr<CBullet> CBulletPtr;