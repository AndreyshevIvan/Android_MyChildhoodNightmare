#include "cocos2d.h"
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

	cocos2d::RefPtr<cocos2d::Label> m_easyButton;
	cocos2d::RefPtr<cocos2d::Label> m_normalButton;
	cocos2d::RefPtr<cocos2d::Label> m_hardButton;

	cocos2d::RefPtr<cocos2d::Sprite> m_background;

	Difficult m_difficult;
};