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
    unsigned char* pTmpData = pImgData;
    int i;
    int j;

    int iMaxOffset = 20;

    //change image buffer data
    for (i = 0; i < iWidth ; ++i)
    {
        for (j = 0; j < iHeight; ++j)
        {

            GLubyte byteValue = *(pImgData += 3);
            pImgData++;
            if (byteValue  == 255)
                continue;

            unsigned char* tmpStart = pImgData - 4;
            int iStartX = std::max(0,i - iMaxOffset);
            int iEndX = std::min(i + iMaxOffset, iWidth);
            int iStartY = std::max(0, j - iMaxOffset);
            int iEndY = std::min(j + iMaxOffset, iHeight);

            int iAlpha = 0;

            for (int m = iStartX; m < iEndX; ++m)
            {
                for (int n = iStartY; n < iEndY; ++n)
                {
                    iAlpha += *(pTmpData +( m*iWidth + n)*4 + 3);
                    log("%d", iAlpha);
                }
            }

            iAlpha = iAlpha / (iEndY - iStartY) / (iEndX - iStartX);
            
            *(pImgData - 1) = iAlpha;
            //*(pImgData - 2) = 255;

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
