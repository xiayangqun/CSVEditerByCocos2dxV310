//
//  SimplePage.hpp
//  CSVEditerByCocos2dxV310
//
//  Created by xiayangqun on 16/6/23.
//
//

#ifndef SimplePage_hpp
#define SimplePage_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CSVGlobalConfig.h"
#include "CSVDefaultKeyConfig.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;
using namespace cocos2d::ui;


class SimplePage:public Node
{
    
public:
    static SimplePage * createWithIndex(int newIndex);
    
protected:
    bool initWithIndex(int newIndex);
    int index;

public:
    void onButtonClickCallBack(Ref * sender);
    std::function<void(const std::string& value , int buttonIndex)> onSelectCallBack;
};


#endif /* SimplePage_hpp */
