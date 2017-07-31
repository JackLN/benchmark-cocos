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

	auto pLayerColor = LayerColor::create(Color4B::BLACK);
	addChild(pLayerColor);

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

	//GLubyte byteValue = *(pImgData + (70*155+70)*4 + 3);

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
					int iAlphaTmp = *(pTmpData + (m*iWidth + n) * 4 + 3);
                    //iAlpha += 
					iAlpha += iAlphaTmp;
					//if (iAlphaTmp > 0)
						//log("%d", iAlphaTmp);
                    
                }
            }

            iAlpha = iAlpha / ((iEndY - iStartY) * (iEndX - iStartX));

			//float fTmp = (float)iAlpha / 255.0f;
            
			*(pImgData - 1) = iAlpha;
			*(pImgData - 2) = 255;
			*(pImgData - 3) = 0;
			*(pImgData - 4) = 0;

        }
    }

    //create texture & sprite
    Texture2D* tex = new Texture2D();
	tex->initWithData(image->getData(), image->getDataLen(), Texture2D::PixelFormat::RGBA8888, iWidth, iHeight, CCSize(iWidth, iHeight));
    auto pSprite = Sprite::createWithTexture(tex);
    pSprite->setPosition(winSize / 2);
    pLayerColor->addChild(pSprite);

	auto pSprite2 = Sprite::create("test1.png");
	pSprite2->setPosition(winSize.width/2 + 200,winSize.height/2);
	pLayerColor->addChild(pSprite2);

    return true;
}
