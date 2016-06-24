//
//  DefaultValueItem.hpp
//  CSVEditerByCocos2dxV310
//
//  Created by xiayangqun on 16/6/23.
//
//

#ifndef DefaultValueItem_hpp
#define DefaultValueItem_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CSVGlobalConfig.h"
#include "CSVDefaultKeyConfig.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class DefaultValueItem : public Widget
{

public:
    static DefaultValueItem * createWithValueAndDes(const string& value, const string& des);
    
protected:
    bool initWithValueAndDes(const string& value, const string& des);
    
    string valueStr;
    string desStr;
    
    //1: 使用 , 2:删除
    void onButtonClick(Ref * sender);
    
public:
    std::function<void(int tag, const string&value, const string& des)> onUseDefaultButtonCallBack;
    
};








#endif /* DefaultValueItem_hpp */
