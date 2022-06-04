#include "Sprite3DTest.h"
#include "base/CCAsyncTaskPool.h"
#include "3d/CCAnimation3D.h"
#include "3d/CCAnimate3D.h"
#include "3d/CCAttachNode.h"
#include "3d/CCRay.h"
#include "3d/CCSprite3D.h"
#include "renderer/CCVertexIndexBuffer.h"
//#include "DrawNode3D.h"

#include <algorithm>

#include <SimpleAudioEngine.h>
using namespace CocosDenshion;


Sprite3DReskinTest::Sprite3DReskinTest()
    : _sprite(nullptr)
{
    auto s = Director::getInstance()->getWinSize();
    addNewSpriteWithCoords(Vec2(s.width / 2, s.height / 2 - 40));

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesEnded = CC_CALLBACK_2(Sprite3DReskinTest::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    //TTFConfig ttfConfig("fonts/arial.ttf", 10);
    auto label1 = LabelTTF::create("头发", "Arial", 10);
    auto item1 = MenuItemLabel::create(label1, CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_reSkin, this));
    auto label2 = LabelTTF::create("眼镜", "Arial", 10);
    auto item2 = MenuItemLabel::create(label2, CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_reSkin, this));
    auto label3 = LabelTTF::create("外套", "Arial", 10);
    auto item3 = MenuItemLabel::create(label3, CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_reSkin, this));
    auto label4 = LabelTTF::create("裤子", "Arial", 10);
    auto item4 = MenuItemLabel::create(label4, CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_reSkin, this));
    auto label5 = LabelTTF::create("鞋子", "Arial", 10);
    auto item5 = MenuItemLabel::create(label5, CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_reSkin, this));
    item1->setPosition(Vec2(50, item1->getContentSize().height * 4));
    item2->setPosition(Vec2(50, item1->getContentSize().height * 5));
    item3->setPosition(Vec2(50, item1->getContentSize().height * 6));
    item4->setPosition(Vec2(50, item1->getContentSize().height * 7));
    item5->setPosition(Vec2(50, item1->getContentSize().height * 8));
    item1->setUserData((void*)SkinType::HAIR);
    item2->setUserData((void*)SkinType::GLASSES);
    item3->setUserData((void*)SkinType::UPPER_BODY);
    item4->setUserData((void*)SkinType::PANTS);
    item5->setUserData((void*)SkinType::SHOES);
    auto pMenu1 = CCMenu::create(item1, item2, item3, item4, item5, nullptr);
    pMenu1->setPosition(Vec2(0, 0));
    this->addChild(pMenu1, 10);

    //bg music

    SimpleAudioEngine::getInstance()->playBackgroundMusic(
        "mygirl.mp3",   //音频的文件名
        true);         //是否循环播放， 默认不循环播放

}
void Sprite3DReskinTest::menuCallback_reSkin(Ref* sender)
{
    long index = (long)(((MenuItemLabel*)sender)->getUserData());
    if (index < (int)SkinType::MAX_TYPE)
    {
        _curSkin[index] = (_curSkin[index] + 1) % _skins[index].size();
        applyCurSkin();
    }
}

void Sprite3DReskinTest::addNewSpriteWithCoords(Vec2 p)
{
    std::string fileName = "Sprite3DTest/ReskinGirl.c3b";
    auto sprite = Sprite3D::create(fileName);
    sprite->setScale(4);
    addChild(sprite);
    sprite->setPosition(Vec2(p.x, p.y - 60));
    auto animation = Animation3D::create(fileName);
    if (animation)
    {
        auto animate = Animate3D::create(animation);

        sprite->runAction(RepeatForever::create(animate));
    }
    _sprite = sprite;

    auto& body = _skins[(int)SkinType::UPPER_BODY];
    body.push_back("Girl_UpperBody01");
    body.push_back("Girl_UpperBody02");

    auto& pants = _skins[(int)SkinType::PANTS];
    pants.push_back("Girl_LowerBody01");
    pants.push_back("Girl_LowerBody02");

    auto& shoes = _skins[(int)SkinType::SHOES];
    shoes.push_back("Girl_Shoes01");
    shoes.push_back("Girl_Shoes02");

    auto& hair = _skins[(int)SkinType::HAIR];
    hair.push_back("Girl_Hair01");
    hair.push_back("Girl_Hair02");

    auto& face = _skins[(int)SkinType::FACE];
    face.push_back("Girl_Face01");
    face.push_back("Girl_Face02");

    auto& hand = _skins[(int)SkinType::HAND];
    hand.push_back("Girl_Hand01");
    hand.push_back("Girl_Hand02");

    auto& glasses = _skins[(int)SkinType::GLASSES];
    glasses.push_back("");
    glasses.push_back("Girl_Glasses01");

    memset(_curSkin, 0, (int)SkinType::MAX_TYPE * sizeof(int));

    applyCurSkin();
}


void Sprite3DReskinTest::applyCurSkin()
{
    for (ssize_t i = 0; i < _sprite->getMeshCount(); i++) {
        auto mesh = _sprite->getMeshByIndex(static_cast<int>(i));
        bool isVisible = false;
        for (int j = 0; j < (int)SkinType::MAX_TYPE; j++) {
            if (mesh->getName() == _skins[j].at(_curSkin[j]))
            {
                isVisible = true;
                break;
            }
        }
        _sprite->getMeshByIndex(static_cast<int>(i))->setVisible(isVisible);
    }
}
