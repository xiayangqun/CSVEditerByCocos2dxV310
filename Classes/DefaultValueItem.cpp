//
//  DefaultValueItem.cpp
//  CSVEditerByCocos2dxV310
//
//  Created by xiayangqun on 16/6/23.
//
//

#include "DefaultValueItem.h"

DefaultValueItem * DefaultValueItem::createWithValueAndDes(const string& value, const string& des)
{
    auto ptr=new DefaultValueItem();
    if(ptr&&ptr->initWithValueAndDes(value, des))
    {
        ptr->autorelease();
        return ptr;
    }
    
    CC_SAFE_DELETE(ptr);
    return nullptr;
}


bool DefaultValueItem::initWithValueAndDes(const string& value, const string& des)
{
    if(!Widget::init())
        return false;

    valueStr=value;
    desStr=des;
    
    auto rootNode=CSLoader::createNode("editCommendTool.csb");
    rootNode->setPosition(Vec2::ZERO);
    addChild(rootNode);
    
    
    rootNode->getChildByName<ui::Text *>("value")->setString(valueStr);
    rootNode->getChildByName<ui::Text *>("des")->setString(desStr);
    
    rootNode->getChildByName<ui::Button *>("use")->addClickEventListener(CC_CALLBACK_1(DefaultValueItem::onButtonClick, this));
    rootNode->getChildByName<ui::Button *>("close")->addClickEventListener(CC_CALLBACK_1(DefaultValueItem::onButtonClick, this));
    
    setContentSize(Size(400,100));
    
    return true;
}



//1: 使用 , 2:删除
void  DefaultValueItem::onButtonClick(Ref * sender)
{
    int tag=dynamic_cast<ui::Button *>(sender)->getTag();
    onUseDefaultButtonCallBack(tag, valueStr, desStr);
}

