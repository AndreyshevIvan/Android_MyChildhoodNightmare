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
		parent->addChild(button);
		SetRelativePosOnParent(button, offset, parent);
		return button;
	}
	static GameText CreateTextItem(const string &innerText, const string &font, int fontSize, Node* parent, Vec2 offset)
	{
		auto winSize = Director::getInstance()->getWinSize();
		GameText text = make_node<Label>();
		text->initWithTTF(innerText, font, fontSize);
		text->setColor(Color3B::WHITE);
		parent->addChild(text);
		SetRelativePosOnParent(text, offset, parent);
		return text;
	}
private:
	static void GameUI::SetRelativePosOnParent(Node* element, const Vec2 &offset, Node* parent)
	{
		if (!element || !parent)
		{
			return;
		}

		auto parentSize = parent->getContentSize();
		const Vec2 &position = Vec2(parentSize.width * offset.x, parentSize.height * offset.y);
		element->setPosition(position);
	}
};