//
//  UTF8World.hpp
//  CSVEditerByCocos2dxV310
//
//  Created by xiayangqun on 16/6/27.
//
//

#ifndef UTF8World_hpp
#define UTF8World_hpp

#include <stdio.h>
#include "CCSVParse.h"


class UTF8World:public CCSVParse{

public:
    static UTF8World * getInstance();
   
    std::string getWorld(int index);
    
protected:
    static UTF8World * instance;
    UTF8World();


    
    
};



#endif /* UTF8World_hpp */
