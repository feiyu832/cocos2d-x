#include "BugsTest.h"
#include "Bug-350.h"
#include "Bug-422.h"
#include "Bug-458/Bug-458.h"
#include "Bug-624.h"
#include "Bug-886.h"
#include "Bug-899.h"
#include "Bug-914.h"
#include "Bug-1159.h"
#include "Bug-1174.h"

#define TEST_BUG(__bug__)									\
{															\
	Scene* pScene = Scene::create();					\
	Bug##__bug__##Layer* pLayer = new Bug##__bug__##Layer();	\
	pLayer->init();                                         \
	pScene->addChild(pLayer);                               \
	Director::getInstance()->replaceScene(pScene);     \
	pLayer->autorelease();                                  \
}

enum
{
    LINE_SPACE = 40,
    kItemTagBasic = 5432,
};

static Point s_tCurPos = Point::ZERO;

struct {
	const char *test_name;
	std::function<void(Object*)> callback;
} g_bugs[] = {
	{ "Bug-350", [](Object* sender){ TEST_BUG(350)} },
	{ "Bug-422", [](Object* sender){ TEST_BUG(422)} },
	{ "Bug-458", [](Object* sender){ TEST_BUG(458)} },
	{ "Bug-624", [](Object* sender){ TEST_BUG(624)} },
	{ "Bug-886", [](Object* sender){ TEST_BUG(886)} },
	{ "Bug-899", [](Object* sender){ TEST_BUG(899)} },
	{ "Bug-914", [](Object* sender){ TEST_BUG(914)} },
	{ "Bug-1159", [](Object* sender){ TEST_BUG(1159)} },
	{ "Bug-1174", [](Object* sender){ TEST_BUG(1174)} },
};

static const int g_maxitems = sizeof(g_bugs) / sizeof(g_bugs[0]);


////////////////////////////////////////////////////////
//
// BugsTestMainLayer
//
////////////////////////////////////////////////////////
void BugsTestMainLayer::onEnter()
{
    Layer::onEnter();

    Size s = Director::getInstance()->getWinSize();
    _itmeMenu = Menu::create();
    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(24);
    for (int i = 0; i < g_maxitems; ++i)
    {
        MenuItemFont* pItem = MenuItemFont::create(g_bugs[i].test_name, g_bugs[i].callback);
        pItem->setPosition(Point(s.width / 2, s.height - (i + 1) * LINE_SPACE));
        _itmeMenu->addChild(pItem, kItemTagBasic + i);
    }

    _itmeMenu->setPosition(s_tCurPos);
    addChild(_itmeMenu);
    setTouchEnabled(true);
}

void BugsTestMainLayer::ccTouchesBegan(Set *pTouches, Event *pEvent)
{
    Touch* touch = (Touch*) pTouches->anyObject();

    _beginPos = touch->getLocation();    
}

void BugsTestMainLayer::ccTouchesMoved(Set *pTouches, Event *pEvent)
{
    Touch* touch = (Touch*) pTouches->anyObject();

    Point touchLocation = touch->getLocation();    
    float nMoveY = touchLocation.y - _beginPos.y;

    Point curPos  = _itmeMenu->getPosition();
    Point nextPos = Point(curPos.x, curPos.y + nMoveY);
    Size winSize = Director::getInstance()->getWinSize();
    if (nextPos.y < 0.0f)
    {
        _itmeMenu->setPosition(Point::ZERO);
        return;
    }

    if (nextPos.y > ((g_maxitems + 1)* LINE_SPACE - winSize.height))
    {
        _itmeMenu->setPosition(Point(0, ((g_maxitems + 1)* LINE_SPACE - winSize.height)));
        return;
    }

    _itmeMenu->setPosition(nextPos);
    _beginPos = touchLocation;
    s_tCurPos   = nextPos;
}

////////////////////////////////////////////////////////
//
// BugsTestBaseLayer
//
////////////////////////////////////////////////////////
void BugsTestBaseLayer::onEnter()
{
    Layer::onEnter();

    MenuItemFont::setFontName("Arial");
    MenuItemFont::setFontSize(24);
    MenuItemFont* pMainItem = MenuItemFont::create("Back", CC_CALLBACK_1(BugsTestBaseLayer::backCallback, this));
    pMainItem->setPosition(Point(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
    Menu* pMenu = Menu::create(pMainItem, NULL);
    pMenu->setPosition( Point::ZERO );
    addChild(pMenu);
}

void BugsTestBaseLayer::backCallback(Object* pSender)
{
//    Director::getInstance()->enableRetinaDisplay(false);
    BugsTestScene* pScene = new BugsTestScene();
    pScene->runThisTest();
    pScene->autorelease();
}

////////////////////////////////////////////////////////
//
// BugsTestScene
//
////////////////////////////////////////////////////////
void BugsTestScene::runThisTest()
{
    Layer* pLayer = new BugsTestMainLayer();
    addChild(pLayer);
    pLayer->release();

    Director::getInstance()->replaceScene(this);
}
