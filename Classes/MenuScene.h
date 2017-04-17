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

	void HightlightButton();
	void GoToGame();
	void CloseApp();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void update(float delta) override;

	template<class T> void SetRelativePos(cocos2d::RefPtr<T> element, const cocos2d::Vec2 &offset);

	void cleanup() override;

	cocos2d::RefPtr<cocos2d::Label> m_startButton;
	cocos2d::RefPtr<cocos2d::Label> m_levelsButton;
	cocos2d::RefPtr<cocos2d::Label> m_exitButton;

	cocos2d::EventListenerTouchOneByOne* m_touchListener;
	cocos2d::Touch* m_touch = nullptr;
};