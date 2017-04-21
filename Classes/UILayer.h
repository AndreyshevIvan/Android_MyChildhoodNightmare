#include "cocos_custom.h"
#include "PlayerController.h"
#include <string>

typedef std::function<void(bool isPause)> onPauseEvent;

namespace UILayer
{
	struct WeaponBar
	{
		WeaponBar(GameSprite icon, GameText ammo)
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
		void SetInfinity(bool isInfinity)
		{
			m_isInfinity = isInfinity;

			if (m_isInfinity)
			{
				m_ammoCount->setString("");
			}
		}
		void Update(int ammoCount)
		{
			SetVisible(true);
			SetAmmoCount(ammoCount);
		}
	private:
		void SetAmmoCount(int ammoCount)
		{
			if (ammoCount < 0)
			{
				return;
			}

			std::string ammoStr = (m_isInfinity) ? "" : std::to_string(ammoCount);
			m_ammoCount->setString(ammoStr);
		}

		GameSprite m_icon;
		GameText m_ammoCount;
		bool m_isInfinity = false;
	};
}

class CUILayer : public cocos2d::Layer
{
public:
	static CUILayer *create(std::shared_ptr<CPlayerController> controller);
	virtual bool init();
	void update(float delta) override;

	GameText GetPlayerHealthBar();
	UILayer::WeaponBar *GetPistolWeaponBar();
	UILayer::WeaponBar *GetShootgunWeaponBar();
	UILayer::WeaponBar *GetAkWeaponBar();

	onPauseEvent onPause;

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

	std::shared_ptr<UILayer::WeaponBar> m_pistolBar;
	std::shared_ptr<UILayer::WeaponBar> m_shootgunBar;
	std::shared_ptr<UILayer::WeaponBar> m_akBar;

	std::shared_ptr<CPlayerController> m_playerController;

	GameSprite m_healthBar;
	GameSprite m_weaponBar;
	GameSprite m_boxBar;
	GameSprite m_buttonFire;
	GameSprite m_buttonJump;
	GameSprite m_buttonReload;
	GameSprite m_buttonLeft;
	GameSprite m_buttonRight;
	GameSprite m_buttonPause;
	GameText m_playerHealth;
	GameText m_playerAmmo;

	cocos2d::EventListenerTouchAllAtOnce* m_touchListener;
	std::vector<cocos2d::Touch*> m_touches;
	std::vector<GameSprite> m_buttons;

	bool m_isPause = false;
};