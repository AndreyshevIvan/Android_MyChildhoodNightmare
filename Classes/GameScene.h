#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos_custom.h"
#include "CustomMap.h"
#include "Player.h"
#include "Enemy.h"

#include "HeroPuppeteer.h"
#include "EnemyPuppeteer.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene *createScene();
	virtual bool init();
	void update(float delta) override;

	CREATE_FUNC(GameScene);

private:
	void InitCamera(cocos2d::Camera* camera);

	void StartGame(const char* newLevelName);
	void PauseGame(bool isPause);
	void ReturnToMenu();

	void CreateGameElements(const char* levelName);
	void CreateLevel(const char* levelName);
	void CreatePlayer();
	void CreateUI();

	void SpawnEnemies();
	void SpawnItems();

	void UpdateCamera();

	cocos2d::Size m_winSize;

	cocos2d::Camera *m_camera = nullptr;
	CCustomMap *m_gameMap = nullptr;

	cocos2d::RefPtr<CPlayer> m_player = nullptr;
	CHeroPuppeteerPtr m_playerPuppeteer = nullptr;

	std::vector<cocos2d::RefPtr<CEnemy>> m_enemies;
	std::vector<std::shared_ptr<CEnemyPuppeteer>> m_enemiesPuppeeters;

	CUILayer *m_UILayer = nullptr;

	bool m_isPause = false;
};