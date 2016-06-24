//
//  CSVDefaultKeyConfig.hpp
//  CSVEditerByCocos2dxV310
//
//  Created by xiayangqun on 16/6/23.
//
//

#ifndef CSVDefaultKeyConfig_hpp
#define CSVDefaultKeyConfig_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "CCSVParse.h"


class CSVDefaultKeyConfig:public CCSVParse
{

public:
    static CSVDefaultKeyConfig * getInstance();
    
public:
    
    std::vector<std::string>  getDefaultByKey(const std::string& key);
    
    void changeDirName(const std::string& dirName);
    void pushNewDefaultValue(const std::string& key ,  const std::string& defaultValue , const std::string& defaultDes);
    void deleteDefaultValue(const std::string&key , const std::string& deleteValue, const std::string& defaultDes);
    bool  loadFromFile();
    void saveFile();
    
protected:
    
    std::string currentDirName;
    
    std::map<std::string ,   std::vector<std::string>> defaultValueMap;
    
    static CSVDefaultKeyConfig * instance;
    CSVDefaultKeyConfig();
    
};




#endif /* CSVDefaultKeyConfig_hpp */
