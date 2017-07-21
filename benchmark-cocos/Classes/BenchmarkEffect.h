#pragma once
#include "cocos2d.h"

USING_NS_CC;

//Scene
class BenchmarkEffect : public Scene
{
public:
    CREATE_FUNC(BenchmarkEffect);
    virtual ~BenchmarkEffect();
    virtual bool init();
protected:
    BenchmarkEffect();
protected:
    Layer* _layerMenu;
    Layer* _layerDis;
};

