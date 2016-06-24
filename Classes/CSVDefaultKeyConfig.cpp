//
//  CSVDefaultKeyConfig.cpp
//  CSVEditerByCocos2dxV310
//
//  Created by xiayangqun on 16/6/23.
//
//

#include "CSVDefaultKeyConfig.h"

CSVDefaultKeyConfig * CSVDefaultKeyConfig::instance=nullptr;

CSVDefaultKeyConfig * CSVDefaultKeyConfig::getInstance()
{
    if(instance==nullptr)
        instance=new CSVDefaultKeyConfig();
    
    return instance;
}

std::vector<std::string>  CSVDefaultKeyConfig::getDefaultByKey(const std::string& key)
{
    static std::vector<std::string>  emptyVec;
    
    if(defaultValueMap.find(key)!=defaultValueMap.end())
        return defaultValueMap.at(key);
    else
        return emptyVec;
    
}


void CSVDefaultKeyConfig::pushNewDefaultValue(const std::string& key ,  const std::string& defaultValue , const std::string& defaultDes)
{
    
    if(key=="" || defaultValue=="")
        return;
    
    if(defaultValueMap.find(key)==defaultValueMap.end())
        defaultValueMap.insert(std::make_pair(key, std::vector<std::string>()));
    
    auto& vectorString=defaultValueMap.at(key);
    vectorString.push_back(defaultValue+"@"+defaultDes);
    
}


void CSVDefaultKeyConfig::deleteDefaultValue(const std::string&key , const std::string& deleteValue, const std::string& defaultDes)
{
    
       if(defaultValueMap.find(key)==defaultValueMap.end())
           return;
    
       auto& vectorString=defaultValueMap.at(key);
    
    for(auto itor=vectorString.begin();itor!=vectorString.end();itor++)
    {
        if( *itor == (deleteValue+"@"+defaultDes)  )
        {
            vectorString.erase(itor);
            break;
        }
    }
    
}

bool  CSVDefaultKeyConfig::loadFromFile()
{
    
    defaultValueMap.clear();
    
    auto fullKeyFileNamePath=FileUtils::getInstance()->getWritablePath()+currentDirName+"/CSVDefaultKeyConfig.csv";
    if(FileUtils::getInstance()->isFileExist(fullKeyFileNamePath)==false)
        return false;
    
    openFile(fullKeyFileNamePath.c_str());
    
    for(auto lineDefaultKeyConfig : data)
    {
        std::string key=lineDefaultKeyConfig[0];
        std::vector<std::string> defaultValueConfig;
        
        for(int i=1;i<lineDefaultKeyConfig.size();i++)
            defaultValueConfig.push_back(lineDefaultKeyConfig[i]);
        
        defaultValueMap.insert(std::make_pair(key, defaultValueConfig));
    }
    
    return true;
}


void CSVDefaultKeyConfig::saveFile()
{
    
    if(defaultValueMap.size()==0) return;
    
    std::string WriteStr;
    
    for(auto& item: defaultValueMap)
    {
        auto& key=item.first;
        auto & vec=item.second;
        
        std::string lineStr=key+",";
        
        for(auto& str : vec)
            lineStr=lineStr+str+",";
        
        lineStr.pop_back();
        lineStr.push_back('\r');
    
        WriteStr=WriteStr+lineStr;
    }
    
    std::string fullPath=FileUtils::getInstance()->getWritablePath()+currentDirName+"/CSVDefaultKeyConfig.csv";
    FileUtils::getInstance()->writeStringToFile(WriteStr, fullPath);
    //CCLOG("fullPath :%s",fullPath.c_str());
}

void CSVDefaultKeyConfig::changeDirName(const std::string& dirName)
{
    saveFile();
    currentDirName=dirName;
    loadFromFile();
}



CSVDefaultKeyConfig::CSVDefaultKeyConfig()
{
}

