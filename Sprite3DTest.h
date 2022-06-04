#ifndef _SPRITE3D_TEST_H_
#define _SPRITE3D_TEST_H_

#include <cocos2d.h>
#include <string>

USING_NS_CC;

class Sprite3DReskinTest : public Layer
{
public:
    CREATE_FUNC(Sprite3DReskinTest);
    Sprite3DReskinTest();
    void addNewSpriteWithCoords(Vec2 p);
    void menuCallback_reSkin(Ref* sender);

protected:
    void applyCurSkin();

    enum class SkinType
    {
        UPPER_BODY = 0,
        PANTS,
        SHOES,
        HAIR,
        FACE,
        HAND,
        GLASSES,
        MAX_TYPE,   //7
    };

    std::vector<std::string> _skins[(int)SkinType::MAX_TYPE]; //all skins
    int                      _curSkin[(int)SkinType::MAX_TYPE]; //current skin index
    cocos2d::Sprite3D* _sprite;
};



#endif
