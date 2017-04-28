#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos_custom.h"
#include "CustomMap.h"
#include "Player.h"
#include "Enemies/EnemyShadow.h"
#include "Enemies/EnemyPuppeteer.h"
#include "HeroPuppeteer.h"

typedef std::pair<std::function<void()>, bool> DoorData;
typedef std::map<std::string, DoorData> DoorActionMap;

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene *createScene();
	virtual bool init();
	void update(float delta) override;

	CREATE_FUNC(GameScene);

private:
	void InitCamera(cocos2d::Camera* camera);
	void InitDoorActions();

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

	void OnDoorContact(const std::string &doorKey);

	cocos2d::Size m_winSize;

	cocos2d::Camera *m_camera = nullptr;
	CCustomMap *m_gameMap = nullptr;
	DoorActionMap m_doorActions;

	cocos2d::RefPtr<CPlayer> m_player = nullptr;
	CHeroPuppeteerPtr m_playerPuppeteer = nullptr;
	std::vector<std::shared_ptr<CEnemyPuppeteer>> m_enemiesPuppeteers;

	CUILayer *m_UILayer = nullptr;

	bool m_isPause = false;
};