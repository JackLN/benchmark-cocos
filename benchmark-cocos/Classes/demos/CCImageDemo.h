#pragma once
#include "cocos2d.h"

USING_NS_CC;

class ImageDemo :public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(ImageDemo);
    static Scene* createScene();
};
