#include "cocos_custom.h"
#include "GameUI.h"
#include "GameScene.h"

enum class MenuState
{
	NONE,
	WAIT_EVENT,
};

class MenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(MenuScene);

private:
	void InitElements();
	void InitListeners();

	void SetGameScene();
	void SetDifficulScene();
	void CloseApp();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void update(float delta) override;

	void cleanup() override;

	GameSprite m_fadeSprite;
	GameText m_startButton;
	GameText m_levelsButton;
	GameText m_exitButton;

	cocos2d::EventListenerTouchOneByOne* m_touchListener;
	cocos2d::Touch* m_touch = nullptr;

	MenuState m_state = MenuState::NONE;
};