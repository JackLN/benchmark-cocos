#include "BenchmarkEffect.h"
#include "CustomEffectBase.h"

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

    Sprite* pFoo = Sprite::create("test1.png");
    pFoo->setPosition(winSize / 2);
    _layerDis->addChild(pFoo);
    
    OuterGlowEffect* pGlow = OuterGlowEffect::create();
    pGlow->setTarget(pFoo);




    return true;
}
