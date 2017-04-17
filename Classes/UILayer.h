#include "cocos_custom.h"
#include "PlayerController.h"

struct WeaponBar
{
	WeaponBar(cocos2d::RefPtr<cocos2d::Sprite> icon, cocos2d::RefPtr<cocos2d::Label> ammo)
		: m_icon(icon)
		, m_ammoCount(ammo)
	{
		SetVisible(false);
	}
	void SetVisible(bool isVisible)
	{
		m_icon->setVisible(isVisible);
		m_ammoCount->setVisible(isVisible);
	}
	void SetAmmoCount(int ammoCount)
	{
		std::string ammoStr = std::to_string(ammoCount);
		m_ammoCount->setString(ammoStr);
	}

private:
	cocos2d::RefPtr<cocos2d::Sprite> m_icon;
	cocos2d::RefPtr<cocos2d::Label> m_ammoCount;
};

class CUILayer : public cocos2d::Layer
{
public:
	static CUILayer *create(std::shared_ptr<CPlayerController> controller);
	virtual bool init();
	void update(float delta) override;

	cocos2d::RefPtr<cocos2d::Label> GetPlayerHealthBar();
	WeaponBar *GetPistolWeaponBar();
	WeaponBar *GetShootgunWeaponBar();
	WeaponBar *GetAkWeaponBar();

	static void UpdateWeaponBar(WeaponBar *weaponBar, int ammoCount);

private:
	void InitElements();
	void InitListeners();
	
	void SetController(std::shared_ptr<CPlayerController> controller);

	void onTouchesBegan(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event* event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event* event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event* event);
	void CheckSingleTouchButtons(const std::vector<cocos2d::Touch*> &touches);
	void CheckAlwaysTouchButtons();
	void HightlightButtons();
	void DeleteTouch(cocos2d::Touch *touch);

	void Pause();

	void cleanup() override;

	std::shared_ptr<WeaponBar> m_pistolBar;
	std::shared_ptr<WeaponBar> m_shootgunBar;
	std::shared_ptr<WeaponBar> m_akBar;

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
	cocos2d::RefPtr<cocos2d::Sprite> m_weaponBarAK;
	cocos2d::RefPtr<cocos2d::Sprite> m_weaponBarPistol;
	cocos2d::RefPtr<cocos2d::Sprite> m_weaponBarShootgun;
	cocos2d::RefPtr<cocos2d::Label> m_playerHealth;
	cocos2d::RefPtr<cocos2d::Label> m_playerAmmo;

	cocos2d::EventListenerTouchAllAtOnce* m_touchListener;
	std::vector<cocos2d::Touch*> m_touches;
	std::vector<cocos2d::RefPtr<cocos2d::Sprite>> m_buttons;

};