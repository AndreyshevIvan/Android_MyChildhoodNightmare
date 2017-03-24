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

	void GoToGame();
	void CloseApp();

	cocos2d::RefPtr<cocos2d::Sprite> m_background;
	cocos2d::RefPtr<cocos2d::Sprite> m_startButton;
	cocos2d::RefPtr<cocos2d::Sprite> m_changeLevelButton;
	cocos2d::RefPtr<cocos2d::Sprite> m_exitButton;

};