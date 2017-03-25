#include "cocos_custom.h"
#include "PlayerController.h"

class CUILayer
	: public cocos2d::Layer
{
public:
	static CUILayer *create(std::shared_ptr<CPlayerController> controller);
	virtual bool init();
	void update(float delta) override;

private:
	void InitElements();
	void InitListeners();
	void SetController(std::shared_ptr<CPlayerController> controller);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void CheckSingleTouchButtons(cocos2d::Touch* touch);
	void CheckMoveButtonsTouch();
	void HightlightButtons();
	void DeleteTouch(cocos2d::Touch* touch);

	std::shared_ptr<CPlayerController> m_playerController;

	cocos2d::RefPtr<cocos2d::Sprite> m_healthBar;
	cocos2d::RefPtr<cocos2d::Sprite> m_weaponBar;
	cocos2d::RefPtr<cocos2d::Sprite> m_boxBar;
	cocos2d::RefPtr<cocos2d::Sprite> m_buttonFire;
	cocos2d::RefPtr<cocos2d::Sprite> m_buttonJump;
	cocos2d::RefPtr<cocos2d::Sprite> m_buttonReload;
	cocos2d::RefPtr<cocos2d::Sprite> m_buttonLeft;
	cocos2d::RefPtr<cocos2d::Sprite> m_buttonRight;
	cocos2d::RefPtr<cocos2d::Sprite> m_buttonPause;

	std::vector<cocos2d::Touch*> m_touches;
	std::vector<cocos2d::RefPtr<cocos2d::Sprite>> m_buttons;

};