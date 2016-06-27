//
//  MainScene.cpp
//  CSVEditerByCocos2dxV310
//
//  Created by xiayangqun on 16/6/24.
//
//

#include "MainScene.h"
#include "createNewCSVScene.h"
#include "UTF8World.h"

MainScene * MainScene::create(const std::string& dirName /*=""*/)
{
    auto  ptr= new MainScene();
    if(ptr&&ptr->init(dirName))
    {
        ptr->autorelease();
        return ptr;
    }
    
    CC_SAFE_DELETE(ptr);
    return nullptr;
    
}

Scene * MainScene::createScene(const std::string& dirName /* ="" */)
{
    auto scene=Scene::create();
    auto mainScene=MainScene::create(dirName);
    scene->addChild(mainScene);
    return scene;
}


bool MainScene::init(const std::string& dirName)
{
    if(!Layer::init())
        return false;
    
    auto visibleSize=Director::getInstance()->getVisibleSize();
    auto rootNode=CSLoader::createNode("MainSceneV2.csb");
    rootNode->setPosition(visibleSize/2);
    addChild(rootNode);
    
    listViewDir=rootNode->getChildByName<ui::ListView *>("listViewDir");
    listViewFile=rootNode->getChildByName<ui::ListView *>("listViewFile");
    
    searchDir=rootNode->getChildByName<ui::TextField *>("searchDir");
    searchFile=rootNode->getChildByName<ui::TextField *>("searchFile");
    spliteTextFiled=rootNode->getChildByName<ui::TextField *>("splitTextFiled");
    
    
    path=rootNode->getChildByName<ui::Text *>("path");
    dirNameText=rootNode->getChildByName<ui::Text *>("dirNameText");
    
    auto writePath=FileUtils::getInstance()->getWritablePath();
    auto pathStr=UTF8World::getInstance()->getWorld(2)+ writePath;
    path->setString(pathStr);
    
    
    searchDir->addEventListener(CC_CALLBACK_2(MainScene::onTextFieldChange, this));
    searchFile->addEventListener(CC_CALLBACK_2(MainScene::onTextFieldChange, this));
    rootNode->getChildByName<ui::Button *>("addFile")->addClickEventListener(CC_CALLBACK_1(MainScene::onButtonClickToNewFile, this));
    
    rootNode->getChildByName<ui::Button *>("buttoSplite")->addClickEventListener(CC_CALLBACK_1(MainScene::onButtonClickToEditSplitChar, this));

    
   
    
    
    
    //设置文件夹button
    DirVector=CSVGlobalConfig::getInstance()->getSubFileNameByFullPath(writePath);
    for(auto& dirName : DirVector)
    {
        auto button=ui::Button::create("button.png");
        button->setScale9Enabled(true);
        button->setContentSize(Size(400,40));
        button->setTitleColor(Color3B::YELLOW);
        button->setTitleFontSize(30);
        button->setTitleText(dirName);
        button->addClickEventListener(CC_CALLBACK_1(MainScene::onButtonClickToChangeDir,this));
        listViewDir->pushBackCustomItem(button);
    }
    currentDirName=dirName;
    
    if(currentDirName!="")
        changeDirName(currentDirName);
    
    
  

    return true;
}

void MainScene::changeCSVSplit(const char splitChar/* =','*/)
{
    
        CSVGlobalConfig::getInstance()->currentSplitChar=splitChar;
         auto fullPathForCSVSplitCharTxt=FileUtils::getInstance()->getWritablePath()+currentDirName+"/"+"CSVSpiltChar.txt";
        std::string csvString;
        csvString.push_back(splitChar);
        FileUtils::getInstance()->writeStringToFile(csvString, fullPathForCSVSplitCharTxt);
        MessageBox("修改成功", "提示");
    
}

void MainScene::onButtonClickToEditSplitChar(Ref * sender)
{
    if(currentDirName=="")
    {
        MessageBox("请先选择编辑的文件夹", "出错了");
        return;
    }
    
    auto CSVSplitString=spliteTextFiled->getString();
    if(CSVSplitString.size()!=1)
    {
        MessageBox("文件分隔符必须是长度为1的字符", "出错了");
        return;
    }

    changeCSVSplit(CSVSplitString[0]);

}


void MainScene::changeDirName(const std::string& changedName)
{
    if(CSVGlobalConfig::getInstance()->openDirAndReadGlobalConfig(changedName))
    {
        currentDirName=changedName;
        dirNameText->setString(UTF8World::getInstance()->getWorld(1)+changedName);
        CSVDefaultKeyConfig::getInstance()->changeDirName(changedName);
        auto fullPathDir=FileUtils::getInstance()->getWritablePath()+changedName;
        FileVector=CSVGlobalConfig::getInstance()->getSubFileNameByFullPath(fullPathDir);
        
        listViewFile->removeAllItems();
        
        for(auto fileName : FileVector)
        {
            auto button=ui::Button::create("button.png");
            button->setScale9Enabled(true);
            button->setContentSize(Size(500,40));
            button->setTitleColor(Color3B::YELLOW);
            button->setTitleFontSize(30);
            button->setTitleText(fileName);
            button->addClickEventListener(CC_CALLBACK_1(MainScene::onButtonClickToEditFile,this));
            listViewFile->pushBackCustomItem(button);
        }
         searchFile->setString("");
        
        //设置文件分隔符
        auto fullPathForCSVSplitCharTxt=FileUtils::getInstance()->getWritablePath()+currentDirName+"/"+"CSVSpiltChar.txt";
        if(FileUtils::getInstance()->isFileExist(fullPathForCSVSplitCharTxt))
        {
            //存在
            auto string=FileUtils::getInstance()->getInstance()->getStringFromFile(fullPathForCSVSplitCharTxt);
            if(string.size()!=1)
            {
                MessageBox("当前文件夹下的CSV分隔符长度不是1,采用默认的文件分隔符','", "提示");
                CSVGlobalConfig::getInstance()->currentSplitChar=',';
                spliteTextFiled->setString(",");
            }
            else
            {
                CSVGlobalConfig::getInstance()->currentSplitChar=string[0];
                spliteTextFiled->setString(string);
            }
        }
        else
        {
            CSVGlobalConfig::getInstance()->currentSplitChar=',';
            spliteTextFiled->setString(",");
        }

        
        
    }
}

std::vector<std::string> MainScene::findHitString(const std::vector<std::string>&comperVec,   std::string  comperChar)
{
    std::vector<std::string> retVec;
    
    for(auto& item : comperVec)
    {
        if(item.find(comperChar)!=string::npos)
        {
            retVec.push_back(item);
        }
    }
    
    return retVec;
}

void MainScene::onButtonClickToChangeDir(Ref * sender)
{
    auto button=dynamic_cast<ui::Button *>(sender);
    changeDirName(button->getTitleText());
}

void MainScene::onButtonClickToEditFile(Ref * sender)
{
    if(currentDirName=="")
    {
        MessageBox("当前都没有选中编辑哪个文件夹，怎么就能选中编辑哪个文件呢？", "出错了");
        return ;
    }
    
    auto fileName=dynamic_cast<ui::Button *>(sender)->getTitleText();
    auto scene=CreateNewCSVScene::getSceenByName(fileName, currentDirName);
    Director::getInstance()->replaceScene(scene);
    
}

void MainScene::onButtonClickToNewFile(Ref * sender)
{
    if(currentDirName=="")
    {
        MessageBox("当前都没有选中编辑哪个文件夹，所以不能添加新的csv？", "出错了");
        return ;
    }

    auto scene=CreateNewCSVScene::getSceenByName("", currentDirName);
    Director::getInstance()->replaceScene(scene);
}


void MainScene::onTextFieldChange(Ref * sender, ui::TextField::EventType ty)
{
    // 1： DirSearch             2://FileSeach
    int tag=dynamic_cast<ui::TextField *>(sender)->getTag();
    std::string compareStr=dynamic_cast<ui::TextField *>(sender)->getString();
    
    if(tag==1)
    {
       
        auto showStringVec=findHitString(DirVector, compareStr);
        listViewDir->removeAllItems();
        for(auto& dirName : showStringVec)
        {
            auto button=ui::Button::create("button.png");
            button->setScale9Enabled(true);
            button->setContentSize(Size(400,40));
            button->setTitleColor(Color3B::YELLOW);
            button->setTitleFontSize(30);
            button->setTitleText(dirName);
            button->addClickEventListener(CC_CALLBACK_1(MainScene::onButtonClickToChangeDir,this));
            listViewDir->pushBackCustomItem(button);
        }
    }
    else if(tag==2)
    {
        auto showStringVec=findHitString(FileVector, compareStr);
        listViewFile->removeAllItems();
        for(auto& dirName : showStringVec)
        {
            auto button=ui::Button::create("button.png");
            button->setScale9Enabled(true);
            button->setContentSize(Size(500,40));
            button->setTitleColor(Color3B::YELLOW);
            button->setTitleFontSize(30);
            button->setTitleText(dirName);
            button->addClickEventListener(CC_CALLBACK_1(MainScene::onButtonClickToEditFile,this));
            listViewFile->pushBackCustomItem(button);
        }
    }
    
}


