//
//  SelectPage.hpp
//  CSVEditerByCocos2dxV310
//
//  Created by xiayangqun on 16/6/23.
//
//

#ifndef SelectPage_hpp
#define SelectPage_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CSVGlobalConfig.h"
#include "CSVDefaultKeyConfig.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;
using namespace cocos2d::ui;



class SelectPage:public Node
{
public:
    
    static  SelectPage * createWithTitleAndValueAndIndex(const string& title, const string& value, int newIndex);
    
public:
    bool initWith(const string& title, const string& value , int newIdex);
    
    
    void initWidget(Node * root);
    void refreshListView();
    
    
    string titleStr;
    string valueStr;
    
    int index;
    
    ui::Text * titleText;
    ui::ListView *  defalutListView;
    ui::TextField * valueField;
    ui::TextField * desFied;
    
    
    //1：使用  2:使用并保存 3:取消
    void onButtonClick(Ref * sender);
    std::function<void(const std::string& value , int buttonIndex)> onSelectCallBack;
    
    
    //当点击了默认选项的回调 1:使用， 2,删除
    void onDefaultButtonClick(int tag, const string&value, const string& des);
};



#endif /* SelectPage_hpp */
