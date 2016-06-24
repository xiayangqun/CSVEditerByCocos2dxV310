//
//  MainScene.hpp
//  CSVEditerByCocos2dxV310
//
//  Created by xiayangqun on 16/6/24.
//
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CSVGlobalConfig.h"
#include "CSVDefaultKeyConfig.h"
#include "cocostudio/CocoStudio.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class MainScene :public Layer
{

public:
    static MainScene * create(const std::string& dirName="");
    static Scene * createScene(const std::string& dirName="");
    
    
protected:
    
    bool init(const std::string& dirName="");
    
    void changeDirName(const std::string& changedName);
    void onButtonClickToChangeDir(Ref * sender);
    
    std::vector<std::string> findHitString(const std::vector<std::string>&comperVec,   std::string  comperChar);
    
    
    std::string currentDirName;
    
    void onButtonClickToEditFile(Ref * sender);
    void onButtonClickToNewFile(Ref * sender);
    
    //tag:1 是SearchDir . tag:2 是SearchFile
    void onTextFieldChange(Ref * sender, ui::TextField::EventType ty);
    
    ui::ListView * listViewDir;
    ui::ListView * listViewFile;
    
    std::vector<std::string> DirVector;
    std::vector<std::string> FileVector;
    
    
    ui::TextField * searchDir;
    ui::TextField * searchFile;
    
    ui::Text * dirNameText;
    ui::Text * path;
    
    
};




#endif /* MainScene_hpp */
