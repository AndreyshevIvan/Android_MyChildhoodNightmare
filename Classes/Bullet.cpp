#include "Bullet.h"

USING_NS_CC;

RefPtr<CBullet> CBullet::Create()
{
	RefPtr<CBullet> bullet = make_node<CBullet>();
	return bullet;
}

RefPtr<CBullet> CBullet::CreateAKBullet()
{
	RefPtr<CBullet> bullet = CBullet::Create();
	return bullet;
}

RefPtr<CBullet> CBullet::CreateShootgunBullet()
{
	RefPtr<CBullet> bullet = CBullet::Create();
	return bullet;
}

RefPtr<CBullet> CBullet::CreatePistolBullet()
{
	RefPtr<CBullet> bullet = CBullet::Create();
	return bullet;
}

void CBullet::update(float delta)
{

}