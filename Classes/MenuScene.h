#include "cocos_custom.h"
#include "GameScene.h"

class MenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(MenuScene);

private:
	void InitElements();
	void InitListeners();

	void HightlightButton(cocos2d::Touch* touch);
	void GoToGame();
	void CloseApp();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void update(float delta) override;

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *pEvent) override;

	template<class T> void SetRelativePos(cocos2d::RefPtr<T> element, const cocos2d::Vec2 &offset);

	cocos2d::RefPtr<cocos2d::Sprite> m_gameName;
	cocos2d::RefPtr<cocos2d::Sprite> m_background;
	cocos2d::RefPtr<cocos2d::Sprite> m_nameBack;
	cocos2d::RefPtr<cocos2d::Sprite> m_itemsBack;
	cocos2d::RefPtr<cocos2d::Label> m_startButton;
	cocos2d::RefPtr<cocos2d::Label> m_levelsButton;
	cocos2d::RefPtr<cocos2d::Label> m_exitButton;

	std::unique_ptr<cocos2d::Touch> m_touch;
};