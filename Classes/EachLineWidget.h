//
//  EachLineWiget.hpp
//  CSVConfig
//
//  Created by xiayangqun on 16/6/22.
//
//

#ifndef EachLineWiget_hpp
#define EachLineWiget_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CSVGlobalConfig.h"
using namespace cocos2d;
using namespace cocos2d::ui;

class EachLineWiget:public cocos2d::ui::Widget
{
    
public:
    
    static EachLineWiget * createWithButtonTitle( std::vector<std::string> buttonTitleOption, int newIndex);
    static EachLineWiget * createWithButtonValue(std::vector<std::string> buttonValueOption,int newIndex );
    static EachLineWiget * createWithButtonTitleAndValue(std::vector<std::string> buttonTitleOption,std::vector<std::string> buttonValueOption,int Index);
    
    std::string getLineOptionString();
    void changeButtonTitleOption(std::vector<std::string> newButtonTitleOption);
    void changIndex(int newIndex);
    int getIndex();
protected:
    

    
    bool initWithButtonTitleAndValue(std::vector<std::string> buttonTitleOption,std::vector<std::string> buttonValueOption,int newIndex);
    
    int index;
    std::vector<std::string > buttonTitleNames;
    std::vector<std::string > buttonValuesNames;
    std::vector<ui::Button *> buttonsVector;
    Label * indexLabel;
    
    
    //tag表示点击了哪些些按钮
    void onClickButton(Ref * sender);
    
    //tag=1 表示删除这行，tag=2表示向上移动, tag=3表示向下
    void onClickChange(Ref * sender);
    
    
    void initButton();
    void updateButtonsLabel();
    
public:
    std::function<void(EachLineWiget * ,int)> onUpOrDeleteCall;
    //std::function<void(const std::string& value , int buttonIndex)> onSelectCallBack;
    
    void onSelectCallBack(const std::string& value, int buttonIndex);
};




#endif /* EachLineWiget_hpp */
