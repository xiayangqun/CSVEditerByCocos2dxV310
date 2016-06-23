#include "HelloWorldScene.h"
#include "CCSVParse.h"
#include "ui/CocosGUI.h"
#include "createNewCSVScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto rootNode=CSLoader::createNode("MainScene.csb");
    rootNode->setPosition(visibleSize/2);
    addChild(rootNode);
    
    
    
    string message="请将要载入的CSV表放入到"+FileUtils::getInstance()->getWritablePath();
    auto label= rootNode->getChildByName<cocos2d::ui::Text *>("text");
    label->setString(message);
    
    
    auto button1=rootNode->getChildByName<cocos2d::ui::Button *>("button1");
    button1->addClickEventListener(CC_CALLBACK_1(HelloWorld::onButtonClick, this));

 
    
    editBox=rootNode->getChildByName<ui::TextField *>("inputValue");
    
    auto button2=rootNode->getChildByName<cocos2d::ui::Button *>("button2");
    button2->addClickEventListener(CC_CALLBACK_1(HelloWorld::onButtonClick, this));

    
    
    return true;
}


void   HelloWorld::onButtonClick(Ref* sender)
{
    int tag=((Node *)sender)->getTag();
    if(tag==1)
    {
        auto newScene=CreateNewCSVScene::getSceenByName("");
        Director::getInstance()->replaceScene(newScene);
    }
    else
    {
        if(editBox->getString()=="")
        {
            MessageBox("请输入要载入的表的名字", "提示");
        }
        else
        {
            auto newScene=CreateNewCSVScene::getSceenByName(editBox->getString());
            Director::getInstance()->replaceScene(newScene);
        }
    }

}








