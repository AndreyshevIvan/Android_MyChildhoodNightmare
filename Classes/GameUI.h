#pragma once;
#include "cocos_custom.h"
#include <string>

using namespace std;
USING_NS_CC;

class GameUI
{
public:
	static GameSprite CreateSprite(const string &pathToFile, Node* parent, Vec2 offset)
	{
		auto winSize = Director::getInstance()->getWinSize();
		GameSprite button = make_node<Sprite>();
		button->initWithFile(pathToFile);
		SetRelativePosOnWindow(button, offset);
		AddChild(parent, button);
		return button;
	}
	static GameText CreateMenuItem(const string &innerText, const string &font, int fontSize, Node* parent, Vec2 offset)
	{
		auto winSize = Director::getInstance()->getWinSize();
		GameText text = make_node<Label>();
		text->initWithTTF(innerText, font, fontSize);
		text->setColor(Color3B::WHITE);
		SetRelativePosOnWindow(text, offset);
		AddChild(parent, text);
		return text;
	}
private:
	static void AddChild(Node* parent, Node* child)
	{
		if (parent && child)
		{
			parent->addChild(child);
		}
	}
	template<class T>
	static void GameUI::SetRelativePosOnWindow(RefPtr<T> element, const Vec2 &offset)
	{
		auto winSize = Director::getInstance()->getVisibleSize();
		const Vec2 &position = Vec2(winSize.width * offset.x, winSize.height * offset.y);
		element->setPosition(position);
	}
};