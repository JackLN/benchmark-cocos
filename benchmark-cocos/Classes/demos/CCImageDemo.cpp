#include "CCImageDemo.h"





Scene* ImageDemo::createScene()
{
    auto scene = Scene::create();
    auto layer = ImageDemo::create();
    scene->addChild(layer);
    return scene;
}

bool ImageDemo::init()
{
    if (!Layer::init())
        return false;

    auto winSize = Director::getInstance()->getWinSize();
    auto originRect = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    //input image buffer
    std::string fullpath = FileUtils::getInstance()->fullPathForFilename("test1.png");
    auto image = new Image();
    image->initWithImageFile(fullpath);

    int iWidth = image->getWidth();
    int iHeight = image->getHeight();

    unsigned char* pImgData = image->getData();
    int i;
    int j;

    //change image buffer data
    for (i = 0; i < iWidth ; ++i)
    {
        for (j = 0; j < iHeight; ++j)
        {

            //GLubyte byteValue = *(pImgData += 3);
            //pImgData++;
            *(pImgData) = 255.0;
            *(pImgData += 1) = 0.0;
            *(pImgData += 1) = 0.0;
            *(pImgData += 1) = 255.0;

            pImgData++;
            //cocos2d::log("%d", byteValue);

        }
    }

    //create texture & sprite
    Texture2D* tex = new Texture2D();
    tex->initWithImage(image);
    auto pSprite = Sprite::createWithTexture(tex);
    pSprite->setPosition(winSize / 2);
    addChild(pSprite);

    return true;
}
