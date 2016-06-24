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

std::vector<std::string> CSVGlobalConfig::getSubFileNameByFullPath(const std::string& fullPath)
{

    std::vector<std::string >retVec;
    
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    int i=0;
    
    dp=opendir(fullPath.c_str());
    chdir(fullPath.c_str());
    while((entry=readdir(dp))!=NULL&&i<255)
    {
        stat(entry->d_name,&statbuf);
        if(S_ISREG(statbuf.st_mode)||S_ISDIR(statbuf.st_mode)  )
        {
            std::string str=entry->d_name;
            if( str!="GlobalConfig.csv"&& str!="CSVDefaultKeyConfig.csv"&&str[0]!='.')
                retVec.push_back(entry->d_name);
        }
    }

    return retVec;
    
}


bool CSVGlobalConfig::openDirAndReadGlobalConfig(const string& dirName)
{
    auto writePath=FileUtils::getInstance()->getWritablePath();
    auto fullFilePath=writePath+dirName+"/GlobalConfig.csv";
    
    if(FileUtils::getInstance()->isFileExist(fullFilePath)==false)
    {
        auto errorMessage="csv模板文件不存在："+fullFilePath;
        MessageBox(errorMessage.c_str(), "出错啦！！！");
        return false;
    }
    else
    {
        openFile(fullFilePath.c_str());
        currentDirName=dirName;
        return true;
    }
}




