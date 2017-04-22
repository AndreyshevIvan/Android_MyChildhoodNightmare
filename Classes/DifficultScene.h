#include "cocos2d.h"
#include "GameUI.h"
#include "SimpleAudioEngine.h"
#include "cocos_custom.h"
#include "DataManager.h"

class DifficultScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene *createScene();
	virtual bool init();

	CREATE_FUNC(DifficultScene);

private:
	void InitElements();
	void InitEvents();
	void InitListener();

	void SetMenuScene();
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	void cleanup() override;

	std::vector<GameText> m_buttons;
	GameText m_easyButton;
	GameText m_normalButton;
	GameText m_hardButton;

	GameSprite m_background;

	Difficult m_difficult;

	cocos2d::EventListenerTouchOneByOne* m_touchListener;
};