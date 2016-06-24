//
//  CSVGlobal.hpp
//  CSVConfig
//
//  Created by xiayangqun on 16/6/22.
//
//

#ifndef CSVGlobal_hpp
#define CSVGlobal_hpp

#include <stdio.h>
#include "CCSVParse.h"

#include <sys/stat.h>
#include "dirent.h"
#include "unistd.h"

class CSVGlobalConfig:public CCSVParse
{
public:
    static CSVGlobalConfig * getInstance();
    virtual ~CSVGlobalConfig();
    
protected:
    static CSVGlobalConfig * instance;
    CSVGlobalConfig();

    
    
    
public:
    
    std::string currentDirName;
    
    std::vector<std::string> getSubFileNameByFullPath(const std::string& fullPath);
    bool openDirAndReadGlobalConfig(const string& dirName);
    std::vector<std::string> getLineOptions(const std::string& lineKey);
    int getOpetionsNumber();
    int getEachOptionNumber();
    
    float ListViewWidth;
    float ListViewHeight;
    float buttonWidth;

};
#endif /* CSVGlobal_hpp */
