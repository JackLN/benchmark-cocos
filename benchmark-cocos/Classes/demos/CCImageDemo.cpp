#include "CCImageDemo.h"
#include "CustomEffectBase.h"


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

    unsigned char* pImgData = image->getData();
    auto iDataLen = image->getDataLen();
    int iWidth = image->getWidth();
    int iHeight = image->getHeight();

    //target data
    unsigned char* pTarData = (unsigned char*)(malloc(iDataLen * sizeof(unsigned char)));
    //memset(pTarData,0,iDataLen * sizeof(unsigned char));

    //change image buffer data
    int i;
    int j;
    int iMaxOffset = 30;
    unsigned char* pDataStart = image->getData();
    for (i = 0; i < iWidth ; ++i)
    {
        for (j = 0; j < iHeight; ++j)
        {

            int offset = (iWidth* i + j) * 4;

            /* *(pTarData + offset)     = 255;
             *(pTarData + offset + 1) = 255;
             *(pTarData + offset + 2) = 0;
             *(pTarData + offset + 3) = 255;*/

           /* *(pTarData) = 255;
            *(pTarData + 1) = 255;
            *(pTarData + 2) = 0;
            *(pTarData + 3) = 255;
            *(pTarData += 4);*/

            //不透明的不需要处理
            GLubyte byteValue = *(pImgData += 3);
            pImgData++;
            if (byteValue == 255)
            {
                *(pTarData + offset+ 3) = 0;
                continue;
            }
                

            int iOriginA = *(pImgData - 1);

            int iStartX = std::max(0,i - iMaxOffset);
            int iEndX = std::min(i + iMaxOffset, iWidth);
            int iStartY = std::max(0, j - iMaxOffset);
            int iEndY = std::min(j + iMaxOffset, iHeight);

            int iCnt = 0;

            //在周围的像素点取alpha均值
            for (int m = iStartX; m < iEndX; ++m)
            {
                for (int n = iStartY; n < iEndY; ++n)
                {
					int iAlphaTmp = *(pDataStart + (m*iWidth + n) * 4 + 3);
                    if (iAlphaTmp > 100) //不透明计数
                        iCnt++;
                }
            }

            int iAlpha = std::max(iCnt * 255 / ((iEndY - iStartY) * (iEndX - iStartX)),iOriginA);

            //test
            //*(pTarData + offset)     = 255;

            //save alpha
            *(pTarData + offset + 3) = iAlpha;

            /**(pImgData - 2) += (int)((255.0f - (float)iOriginAlpha) / 255.0f * 0.0f   );
            *(pImgData - 3) += (int)((255.0f - (float)iOriginAlpha) / 255.0f * 127.0f );
            *(pImgData - 4) += (int)((255.0f - (float)iOriginAlpha) / 255.0f * 255.0f );*/

           /* *(pImgData - 2) = int((float)(*(pImgData - 2)) * (float)iAlpha / 255.0f);
            *(pImgData - 3) = int((float)(*(pImgData - 3)) * (float)iAlpha / 255.0f);
            *(pImgData - 4) = int((float)(*(pImgData - 4)) * (float)iAlpha / 255.0f);*/

            /**(pImgData - 1) = iAlpha;
            *(pImgData - 2) = 0;
            *(pImgData - 3) = 215;
            *(pImgData - 4) = 255;*/


            //下一个像素
            //*(pTmpData += 4);
        }
    }

    //copy image data
    memcpy(image->getData(), pTarData, image->getDataLen());
    CC_SAFE_FREE(pTarData);

    //create texture & sprite
    /*Texture2D* tex = new Texture2D();
    tex->initWithData(image->getData(), image->getDataLen(), Texture2D::PixelFormat::RGBA8888, iWidth, iHeight, CCSize(iWidth, iHeight));*/

    auto tex = Director::getInstance()->getTextureCache()->addImage("test1.png");
    auto pSprite = Sprite::createWithTexture(tex);
    pSprite->setPosition(winSize / 2);
    pLayerColor->addChild(pSprite);

    //auto pEffectGlow = OuterGlowTex::create();
    

    //for (i = 0; i < 100;i++)
    //{
    //    Vec2 pos(cocos2d::random(0.0f, winSize.width), cocos2d::random(0.0f, winSize.height));

    //    auto pSprite2 = Sprite::create("test1.png");
    //    pSprite2->setPosition(pos);
    //    pLayerColor->addChild(pSprite2);

    //    
    //    auto pSprite = Sprite::createWithTexture(tex);
    //    pSprite->setPosition(pSprite2->getContentSize()/2);
    //    pSprite2->addChild(pSprite);
    //    //pEffectGlow->setTarget(pSprite);
    //}

    //pEffectGlow->setGlowColor(Color4F(1.0f,0.85f,0.74f,1.0f));
    //pEffectGlow->setTarget(pSprite);

    //sprite
    /*auto pSprite2 = Sprite::create("test1.png");
    pSprite2->setPosition(winSize/2);
    pLayerColor->addChild(pSprite2);*/


    /*auto pSprite3 = Sprite::create("test1.png");
    pSprite3->setPosition(winSize.width / 2 + 155, winSize.height / 2);
    pLayerColor->addChild(pSprite3);*/

    /*auto pGlow = OuterGlowEffect::create();
    pGlow->setTarget(pSprite3);
*/
    return true;
}
