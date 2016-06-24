//
//  EachLineListView.hpp
//  CSVConfig
//
//  Created by xiayangqun on 16/6/22.
//
//

#ifndef EachLineListView_hpp
#define EachLineListView_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "CSVGlobalConfig.h"
#include "EachLineWidget.h"
USING_NS_CC;
using namespace cocos2d::ui;

class EachLineListVew:public Node
{

public:
    static EachLineListVew * createWithFileName(const std::string& fileName, const std::string& driName);
    
protected:
    bool initWithFileName(const std::string& fileName, const std::string& driName );
    std::string getCSVString();

protected:
    ui::ListView * listView;
    ui::EditBox * fileNameEditBox;
    
    std::string currentDirName;
    
    void onButtonClickToAddLine(Ref * sender);
    void onButtonClickToSaveCSVFile(Ref * sender);
    //1 是删除，2是向上移动
    void onUpOrDelete(EachLineWiget * sender,int tag);
    void changeItemsIndex();
    
};







#endif /* EachLineListView_hpp */
