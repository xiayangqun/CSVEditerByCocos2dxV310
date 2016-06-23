//
//  SelectPage.cpp
//  CSVEditerByCocos2dxV310
//
//  Created by xiayangqun on 16/6/23.
//
//

#include "SelectPage.h"
#include  "DefaultValueItem.h"


SelectPage * SelectPage::createWithTitleAndValueAndIndex(const string& title, const string& value, int newIndex)
{
    auto ptr=new SelectPage();
    if(ptr&&ptr->initWith(title, value, newIndex))
    {
        ptr->autorelease();
        return ptr;
    }
    
    CC_SAFE_DELETE(ptr);
    return  nullptr;
}

bool SelectPage::initWith(const string& title, const string& value , int newIdex)
{
    if(!Node::init())
        return false;
    
    setName("secondPage");
    
    titleStr=title;
    valueStr=value;
    index=newIdex;
    
    auto rootNode=CSLoader::createNode("editButtonBar.csb");
    rootNode->setPosition(Director::getInstance()->getVisibleSize()/2);
    addChild(rootNode);
    
    initWidget(rootNode);

    
    
    return true;
}

void SelectPage::initWidget(Node * root)
{
    titleText=root->getChildByName<ui::Text *>("title");
    titleText->setString(titleStr);
    
    defalutListView=root->getChildByName<ui::ListView *>("defaultListVIew");
    refreshListView();
    
    valueField=root->getChildByName<ui::TextField *>("inputValue");
    valueField->setString(valueStr);
    
    desFied=root->getChildByName<ui::TextField *>("inputDes");
    
    
    root->getChildByName<ui::Button *>("Button_2")->addClickEventListener(CC_CALLBACK_1(SelectPage::onButtonClick, this));
    root->getChildByName<ui::Button *>("Button_2_0")->addClickEventListener(CC_CALLBACK_1(SelectPage::onButtonClick, this));
    
    root->getChildByName<ui::Button *>("Button_4")->addClickEventListener(CC_CALLBACK_1(SelectPage::onButtonClick, this));
    root->getChildByName<ui::Button *>("Button_3")->addClickEventListener(CC_CALLBACK_1(SelectPage::onButtonClick, this));
    

}


//1：使用  2:使用并保存 3:取消，4.清空
void  SelectPage::onButtonClick(Ref * sender)
{
    int tag=dynamic_cast<ui::Button *>(sender)->getTag();
    
    if(tag==4)
    {
        valueField->setString("");
        desFied->setString("");
        return;
    }
    
    
    if(tag==1)
    {
        onSelectCallBack(valueField->getString(),index);
    }
    else if(tag==2)
    {
        onSelectCallBack(valueField->getString(),index);
        
        if(titleStr!=""&&valueField->getString()!="")
        {
            CSVDefaultKeyConfig::getInstance()->pushNewDefaultValue(titleStr, valueField->getString(), desFied->getString());
            CSVDefaultKeyConfig::getInstance()->saveFile();
        }
    }
    
    removeFromParent();
}


//当点击了默认选项的回调 1:使用， 2,删除
void  SelectPage::onDefaultButtonClick(int tag, const string&value, const string& des)
{
    if(tag==1)
    {
        valueField->setString(value);
        desFied->setString(des);
    }
    else
    {
        CSVDefaultKeyConfig::getInstance()->deleteDefaultValue(titleStr, value, des);
        refreshListView();
    }
    
    
}


void SelectPage::refreshListView()
{
    
    defalutListView->removeAllItems();
    
    auto data=CSVDefaultKeyConfig::getInstance()->getDefaultByKey(titleStr);
    for(auto& str : data)
    {
        size_t iPos = str.find('@');
        auto  value = str.substr(0, iPos);
        auto des = str.substr(iPos+1, str.length()-iPos-1);
        
        auto item=DefaultValueItem::createWithValueAndDes(value, des);
        item->onUseDefaultButtonCallBack=CC_CALLBACK_3(SelectPage::onDefaultButtonClick, this);
        defalutListView->pushBackCustomItem(item);
    }
}

