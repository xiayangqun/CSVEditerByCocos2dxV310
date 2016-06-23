//
//  CSVGlobal.cpp
//  CSVConfig
//
//  Created by xiayangqun on 16/6/22.
//
//

#include "CSVGlobalConfig.h"


CSVGlobalConfig *  CSVGlobalConfig::getInstance()
{
        if(instance==nullptr)
            instance=new CSVGlobalConfig();

        return instance;
}


CSVGlobalConfig::~CSVGlobalConfig()
{
    
}

CSVGlobalConfig * CSVGlobalConfig::instance=nullptr;


CSVGlobalConfig::CSVGlobalConfig():CCSVParse()
{
    openFile("GlobalConfig.csv");
    //ListViewWidth=1000;
    ListViewHeight=700;
}


std::vector<std::string> CSVGlobalConfig::getLineOptions(const std::string& lineKey)
{
    for(auto& lineOption : data)
    {
        if(lineOption[0]==lineKey)
            return lineOption;
    }
    
    return data[0];
}


int CSVGlobalConfig::getOpetionsNumber()
{
    return data.size();
}

int CSVGlobalConfig::getEachOptionNumber()
{
    return data[0].size();
}




