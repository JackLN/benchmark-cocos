#include "BenchmarkEffect.h"
#include "CustomEffectBase.h"
#include "EffectEntity.h"

BenchmarkEffect::BenchmarkEffect()
: _layerDis(nullptr)
, _layerMenu(nullptr)
{
}

BenchmarkEffect::~BenchmarkEffect()
{
}

bool BenchmarkEffect::init()
{
    if (!Scene::init())
        return false;
    

    _layerDis = LayerColor::create(Color4B::BLACK);
    addChild(_layerDis);

    auto winSize = Director::getInstance()->getWinSize();
    auto originRect = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto pGlow = OuterGlowEffect::create();


    /*for (int i = 0; i < 100; i++)
    {
    EffectEntity* pFoo = EffectEntity::create("test1.png");
    pFoo->setPosition(cocos2d::random(0.0f, winSize.width), cocos2d::random(0.0f, winSize.height));
    _layerDis->addChild(pFoo);


    pGlow->setTarget(pFoo);
    }*/


    EffectEntity* pFoo = EffectEntity::create("test1.png");
    pFoo->setPosition(winSize/2);
    _layerDis->addChild(pFoo);
    pGlow->setTarget(pFoo); 

    /*Rect origin = pFoo->getBoundingBox();
    auto pRender = RenderTexture::create(origin.size.width, origin.size.height, kCCTexture2DPixelFormat_RGBA8888);
    pRender->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
    auto tmpSp = Sprite::createWithSpriteFrame(pFoo->getSpriteFrame());
    tmpSp->setPosition(tmpSp->getContentSize() / 2);
    pGlow->setTarget(tmpSp);
    tmpSp->visit();
    pRender->end();
    pRender->saveToFile("Outer.png", cocos2d::Image::Format::PNG);*/

    Rect origin = pFoo->getBoundingBox();
    auto pRender = RenderTexture::create(winSize.width, winSize.height, kCCTexture2DPixelFormat_RGBA8888);
    pRender->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
    pFoo->visit();
    pRender->end();
    pRender->saveToFile("Outer.png", cocos2d::Image::Format::PNG,false);

    return true;
}
