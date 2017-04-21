#include "DifficultScene.h"
#include <iostream>

USING_NS_CC;

namespace
{
	const char BACKGROUND_IMG[] = "textures/menu_wrapper.png";
	const char TITLE_IMG[] = "textures/difficult_title.png";
}

Scene* DifficultScene::createScene()
{
	auto scene = Scene::create();

	auto layer = DifficultScene::create();
	scene->addChild(layer);

	return scene;
}

bool DifficultScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	InitElements();
	InitEvents();

	return true;
}

void DifficultScene::InitElements()
{

}
void DifficultScene::InitEvents()
{

}