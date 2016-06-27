//
//  EachLineWiget.cpp
//  CSVConfig
//
//  Created by xiayangqun on 16/6/22.
//
//

#include "EachLineWidget.h"
#include "SimplePage.h"
#include "SelectPage.h"
#include "UTF8World.h"

EachLineWiget * EachLineWiget::createWithButtonTitle( std::vector<std::string> buttonTitleOption,int newIndex)
{
    std::vector<std::string > buttonValueOption;
    buttonValueOption.resize(buttonTitleOption.size());
    buttonValueOption[0]=buttonTitleOption[0];
    
    return  EachLineWiget::createWithButtonTitleAndValue(buttonTitleOption, buttonValueOption, newIndex);
}


EachLineWiget *  EachLineWiget::createWithButtonValue(std::vector<std::string> buttonValueOption,int newIdex)
{
    
    auto buttonTitleOption=CSVGlobalConfig::getInstance()->getLineOptions(buttonValueOption[0]);
    while (buttonValueOption.size()<buttonTitleOption.size()) {
        buttonValueOption.push_back("");
    }
    
    return EachLineWiget::createWithButtonTitleAndValue(buttonTitleOption, buttonValueOption,newIdex);
}

EachLineWiget *  EachLineWiget::createWithButtonTitleAndValue(std::vector<std::string> buttonTitleOption,std::vector<std::string> buttonValueOption,int newIndex)
{
    auto ptr=new EachLineWiget();
    if(ptr&&ptr->initWithButtonTitleAndValue(buttonTitleOption, buttonValueOption,newIndex))
    {
        ptr->autorelease();
        return  ptr;
    }
    
    CC_SAFE_DELETE(ptr);
    return  nullptr;
}


std::string  EachLineWiget::getLineOptionString()
{
    
    static char c[20];
    sprintf(c, "%d,",index);
    
    std::string lineString(c);
    for(auto& string : buttonValuesNames)
    {
        lineString=lineString+string+',';
    }
    lineString.pop_back();
    lineString.push_back('\r');
    return lineString;
}

void  EachLineWiget::changeButtonTitleOption(std::vector<std::string> newButtonTitleOption)
{
    buttonTitleNames=newButtonTitleOption;
    buttonValuesNames.clear();
    buttonValuesNames.resize(buttonTitleNames.size());
    buttonValuesNames[0]=buttonTitleNames[0];
    updateButtonsLabel();
}


bool EachLineWiget::initWithButtonTitleAndValue(std::vector<std::string> buttonTitleOption,std::vector<std::string> buttonValueOption,int newIndex)
{
    if(!Widget::init())
        return false;
    
    buttonTitleNames=buttonTitleOption;
    buttonValuesNames=buttonValueOption;
    index=newIndex;
    
    initButton();
    updateButtonsLabel();
    
    return true;
}

void EachLineWiget::initButton()
{
    

    
    
    int buttonNumber=buttonTitleNames.size();
    float buttonWidth=(Director::getInstance()->getVisibleSize().width-320)/buttonNumber ;
    float buttonHeight=30;
    
    
    indexLabel=Label::createWithSystemFont("1", "fonts.arial.ttf", 35);
    indexLabel->setPositionX(30);
    indexLabel->setPositionY(buttonHeight/2);
    indexLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    addChild(indexLabel);
    
    
    for(int i=0;i<buttonNumber;i++)
    {
        auto button=cocos2d::ui::Button::create("button.png");
        button->setScale9Enabled(true);
        button->setContentSize(Size(buttonWidth,buttonHeight));
        button->setTitleFontSize(20);
        button->setPosition(Vec2(i*buttonWidth+buttonWidth/2+50,buttonHeight/2));
        addChild(button);
        button->addClickEventListener(CC_CALLBACK_1(EachLineWiget::onClickButton, this));
        buttonsVector.push_back(button);
        button->setTag(i);
    }
    

    
    
    auto buttonUp=cocos2d::ui::Button::create("button.png");
    buttonUp->setScale9Enabled(true);
    buttonUp->setTitleText(UTF8World::getInstance()->getWorld(6));
    buttonUp->setTitleFontSize(25);
    buttonUp->setTitleColor(Color3B::ORANGE);
    buttonUp->setPosition(Vec2( buttonNumber*buttonWidth+buttonWidth/2+20,buttonHeight/2));
    buttonUp->setContentSize(Size(80,30));
    buttonUp->addClickEventListener(CC_CALLBACK_1(EachLineWiget::onClickChange, this));
    buttonUp->setTag(2);
    addChild(buttonUp);
    
    
    auto buttonClose=cocos2d::ui::Button::create("button.png");
    buttonClose->setScale9Enabled(true);
    buttonClose->setTitleText(UTF8World::getInstance()->getWorld(7));
    buttonClose->setTitleFontSize(25);
    buttonClose->setTitleColor(Color3B::RED);
    buttonClose->setPosition(Vec2(buttonUp->getPositionX()+85,buttonHeight/2));
    buttonClose->setContentSize(Size(80,30));
    buttonClose->setTag(1);
    buttonClose->addClickEventListener(CC_CALLBACK_1(EachLineWiget::onClickChange, this));
    addChild(buttonClose);
    
    
    auto buttonDown=cocos2d::ui::Button::create("button.png");
    buttonDown->setScale9Enabled(true);
    buttonDown->setTitleText(UTF8World::getInstance()->getWorld(8));
    buttonDown->setTitleFontSize(25);
    buttonDown->setTitleColor(Color3B::BLUE);
    buttonDown->setPosition(Vec2(buttonClose->getPositionX()+85,buttonHeight/2));
    buttonDown->setContentSize(Size(80,30));
    buttonDown->setTag(3);
    buttonDown->addClickEventListener(CC_CALLBACK_1(EachLineWiget::onClickChange, this));
    addChild(buttonDown);
    
    
    setContentSize(Size(Director::getInstance()->getVisibleSize().width ,35));
}


void EachLineWiget::updateButtonsLabel()
{
    int buttonNumber=buttonsVector.size();
    for(int i=1;i<buttonNumber;i++)
    {
        
        if(buttonTitleNames[i]=="")
            buttonsVector[i]->setColor(Color3B::GRAY);
        else
            buttonsVector[i]->setColor(Color3B::WHITE);
        
        if(buttonValuesNames[i]=="")
        {
            buttonsVector[i]->setTitleColor(Color3B::WHITE);
            buttonsVector[i]->setOpacity(150);
            buttonsVector[i]->setTitleText(buttonTitleNames[i]);
        }
        else
        {
            buttonsVector[i]->setTitleColor(Color3B::GREEN);
             buttonsVector[i]->setOpacity(255);
            buttonsVector[i]->setTitleText(buttonValuesNames[i]);
        }
        
        auto showLabel=buttonsVector[i]->getTitleText();
        float labelSize=300.0f/showLabel.size();
        if(labelSize>25) labelSize=25;
        if(labelSize<5) labelSize=5;
        buttonsVector[i]->setTitleFontSize(labelSize);
    }
    
    buttonsVector[0]->setTitleText(buttonValuesNames[0]);
    buttonsVector[0]->setTitleColor(Color3B::YELLOW);
    
    static char c[32];
    sprintf(c, "%d",index);
    indexLabel->setString(c);

}


//tag表示点击了哪些些按钮
void EachLineWiget::onClickButton(Ref * sender)
{
    
    if (Director::getInstance()->getRunningScene()->getChildByName("secondPage"))
        return;
        
    
    
    int tag=  dynamic_cast<ui::Button *>(sender) ->getTag();
    if(tag==0)
    {
        //选择表首
            auto simplePage=SimplePage::createWithIndex(tag);
            simplePage->onSelectCallBack=CC_CALLBACK_2(EachLineWiget::onSelectCallBack, this);
            Director::getInstance()->getRunningScene()->addChild(simplePage,2,2);
        
    }
    else
    {
        //todo
        auto selPag=SelectPage::createWithTitleAndValueAndIndex(buttonTitleNames[tag], buttonValuesNames[tag], tag);
        selPag->onSelectCallBack=CC_CALLBACK_2(EachLineWiget::onSelectCallBack, this);
        Director::getInstance()->getRunningScene()->addChild(selPag,2,2);
    }
}

void EachLineWiget::onSelectCallBack(const std::string& value, int buttonIndex)
{
    if(buttonIndex==0)
    {
        //改变了表首
        auto newButtonTitleOption=CSVGlobalConfig::getInstance()->getLineOptions(value);
        changeButtonTitleOption(newButtonTitleOption);
    }
    else
    {
        //改变了表的某一项
        buttonValuesNames[buttonIndex]=value;
        updateButtonsLabel();
    }
    
}


//tag=1 表示删除这行，tag=2表示向上移动 3
void EachLineWiget::onClickChange(Ref * sender)
{
    if (Director::getInstance()->getRunningScene()->getChildByName("secondPage"))
        return;
    
    int tag=((Node*)sender)->getTag();
    onUpOrDeleteCall(this,tag);
}

void EachLineWiget::changIndex(int newIndex)
{
    index=newIndex;
    updateButtonsLabel();
}

int EachLineWiget::getIndex()
{
    return index;
}





