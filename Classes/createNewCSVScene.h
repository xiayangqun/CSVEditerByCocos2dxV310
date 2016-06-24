//
//  createNewCSVScene.hpp
//  CSVConfig
//
//  Created by xiayangqun on 16/6/22.
//
//

#ifndef createNewCSVScene_hpp
#define createNewCSVScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "EachLineWidget.h"
#include "EachLineListView.h"
USING_NS_CC;
using namespace cocos2d::ui;

class CreateNewCSVScene: public Layer
{
    
public:
    static Scene * getSceenByName(const std::string& fileName,const std::string& dirName);
    static CreateNewCSVScene * createWithFileName(const std::string& fileName, const std::string& dirName);
    
protected:
    bool initWithFileName(const std::string& fileName, const std::string& dirName);
    EachLineListVew * listView;
};




#endif /* createNewCSVScene_hpp */
