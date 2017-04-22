#pragma once;
#include "cocos_custom.h"
#include <string>

using namespace std;
USING_NS_CC;

namespace gameUI
{
	enum
	{
		MAX_OPACITY = 255,
	};

	static const char BASE_FONT[] = "fonts/nightmarealley.ttf";

	const int MENU_LARGE_FONT_SIZE = 120;
	const int MENU_NORMAL_FONT_SIZE = 100;
	const int MENU_SMALL_FONT_SIZE = 65;

	static const float BUTTONS_SCALE_FACTOR = 1.6f;
	static const float SCENE_TRANSITION_TIME = 1.1f;

	static void SetRelativePosOnParent(Node* element, const Vec2 &offset, Node* parent);
	static GameSprite CreateSprite(const string &spriteName, Node* parent, Vec2 offset);
	static GameText CreateTextItem(const string &innerText, const string &font, int fontSize, Node* parent, Vec2 offset);
	static bool DoIfTouch(const Rect &area, const vector<Touch*> &touches, function<void()> onTouch);

	GameSprite CreateSprite(const string &spriteName, Node* parent, Vec2 offset)
	{
		auto winSize = Director::getInstance()->getWinSize();
		GameSprite button = make_node<Sprite>();
		button->initWithSpriteFrameName(spriteName);
		parent->addChild(button);
		SetRelativePosOnParent(button, offset, parent);
		return button;
	}

	GameText CreateTextItem(const string &innerText, const string &font, int fontSize, Node* parent, Vec2 offset)
	{
		auto winSize = Director::getInstance()->getWinSize();
		GameText text = make_node<Label>();
		text->initWithTTF(innerText, font, fontSize);
		text->setColor(Color3B::WHITE);
		parent->addChild(text);
		SetRelativePosOnParent(text, offset, parent);
		return text;
	}

	void SetRelativePosOnParent(Node* element, const Vec2 &offset, Node* parent)
	{
		if (!element || !parent)
		{
			return;
		}

		auto parentSize = parent->getContentSize();
		const Vec2 &position = Vec2(parentSize.width * offset.x, parentSize.height * offset.y);
		element->setPosition(position);
	}

	bool DoIfTouch(const Rect &area, const vector<Touch*> &touches, function<void()> onTouch)
	{
		bool isTouch = std::any_of(touches.begin(), touches.end(), [&](Touch* touch) {
			const Vec2 &point = touch->getLocation();
			return area.containsPoint(point);
		});

		if (isTouch) onTouch();
		return isTouch;
	};
}