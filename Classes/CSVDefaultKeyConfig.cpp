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
    if(defaultValueMap.find(key)==defaultValueMap.end())
        defaultValueMap.insert(std::make_pair(key, std::vector<std::string>()));
    
    return defaultValueMap.at(key);
}


void CSVDefaultKeyConfig::pushNewDefaultValue(const std::string& key ,  const std::string& defaultValue , const std::string& defaultDes)
{
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
    if(FileUtils::getInstance()->isFileExist("CSVDefaultKeyConfig.csv")==false)
        return false;
    
    openFile("CSVDefaultKeyConfig.csv");
    
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
    
    std::string fullPath=FileUtils::getInstance()->getWritablePath()+"CSVDefaultKeyConfig.csv";
    FileUtils::getInstance()->writeStringToFile(WriteStr, fullPath);
    CCLOG("fullPath :%s",fullPath.c_str());
}


CSVDefaultKeyConfig::CSVDefaultKeyConfig()
{
    loadFromFile();
}

