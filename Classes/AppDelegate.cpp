#include "AppDelegate.h"
#include "GameScene.h"

USING_NS_CC;

static const cocos2d::Size RESOLUTION = cocos2d::Size(1280, 720);
static const cocos2d::Rect RESOLUTION_RECT = cocos2d::Rect(0, 0, RESOLUTION.width, RESOLUTION.height);
static const std::string GAME_NAME = "MyChildhoodNightmares";

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
	return 0;
}

bool AppDelegate::applicationDidFinishLaunching()
{
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect(GAME_NAME, RESOLUTION_RECT);
#else
		glview = GLViewImpl::create(GAME_NAME);
#endif
		director->setOpenGLView(glview);
	}

	director->setDisplayStats(true);
	director->setAnimationInterval(1.0f / 60);

	glview->setDesignResolutionSize(RESOLUTION.width, RESOLUTION.height, ResolutionPolicy::NO_BORDER);
	director->setContentScaleFactor(1.f);

	register_all_packages();

	auto scene = GameScene::createScene();
	director->runWithScene(scene);

	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();
}
