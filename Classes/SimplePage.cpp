//
//  SimplePage.cpp
//  CSVEditerByCocos2dxV310
//
//  Created by xiayangqun on 16/6/23.
//
//

#include "SimplePage.h"


SimplePage * SimplePage::createWithIndex(int newIndex)
{
    auto ptr=new SimplePage();
    if(ptr&&ptr->initWithIndex(newIndex))
    {
        ptr->autorelease();
        return ptr;
    }

    CC_SAFE_DELETE(ptr);
    return  nullptr;
    
}

bool SimplePage::initWithIndex(int newIndex)
{
    if(!Node::init())
        return  false;

    setName("secondPage");
    
    auto visibleSize=Director::getInstance()->getVisibleSize();
    auto rootNode= CSLoader::createNode("simplePage.csb");
    rootNode->setPosition(visibleSize/2);
    addChild(rootNode);
    
    auto listView=rootNode->getChildByName<ui::ListView *>("listView");
    
    const auto& data=CSVGlobalConfig::getInstance()->data;
    for(const auto& lineData : data)
    {
        auto buttonTitle=lineData[0];
        
        auto button=ui::Button::create("button.png");
        button->setScale9Enabled(true);
        button->setTitleFontSize(25);
        button->setContentSize(Size( 300,30));
        button->setTitleText(buttonTitle);
        button->addClickEventListener(CC_CALLBACK_1(SimplePage::onButtonClickCallBack, this));
        listView->pushBackCustomItem(button);
    }
    
    return true;
}


void SimplePage::onButtonClickCallBack(Ref * sender)
{
    auto button=dynamic_cast<ui::Button *>(sender);
    onSelectCallBack(button->getTitleText(),index);
    removeFromParent();
}



