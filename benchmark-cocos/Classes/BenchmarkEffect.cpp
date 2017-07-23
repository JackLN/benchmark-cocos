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

	OuterGlowEffect* pGlow = OuterGlowEffect::create();


	for (int i = 0; i < 100; i++)
	{
		EffectEntity* pFoo = EffectEntity::create("test1.png");
		pFoo->setPosition(cocos2d::random(0.0f,winSize.width),cocos2d::random(0.0f,winSize.height));
		_layerDis->addChild(pFoo);


		pGlow->setTarget(pFoo);
	}

	




    return true;
}
