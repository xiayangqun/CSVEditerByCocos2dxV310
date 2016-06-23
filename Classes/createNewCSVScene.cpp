//
//  createNewCSVScene.cpp
//  CSVConfig
//
//  Created by xiayangqun on 16/6/22.
//
//

#include "createNewCSVScene.h"


Scene * CreateNewCSVScene::getSceenByName(const std::string& fileName)
{
    auto scene=Scene::create();
    auto layer=CreateNewCSVScene::createWithFileName(fileName);
    scene->addChild(layer);
    
    return scene;
    
}


CreateNewCSVScene *  CreateNewCSVScene::createWithFileName(const std::string& fileName)
{
    auto ptr=new (std::nothrow)  CreateNewCSVScene();
    if(ptr&&ptr->initWithFileName(fileName))
    {
        ptr->autorelease();
        return ptr;
    }
    
    CC_SAFE_DELETE(ptr);
    return  nullptr;
}


bool CreateNewCSVScene::initWithFileName(const std::string& fileName)
{
    if(!Layer::init())
        return false;

    
    listView=EachLineListVew::createWithFileName(fileName);
    listView->setPosition(Vec2::ZERO);
    addChild(listView);
    
       
    
    //
    return  true;
}