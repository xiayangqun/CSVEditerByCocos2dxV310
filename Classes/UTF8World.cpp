//
//  UTF8World.cpp
//  CSVEditerByCocos2dxV310
//
//  Created by xiayangqun on 16/6/27.
//
//

#include "UTF8World.h"

UTF8World * UTF8World::getInstance()
{
        if(instance==nullptr)
            instance=new UTF8World();
    
    return instance;
}

std::string UTF8World::getWorld(int index)
{
    return data[0][index];
}


UTF8World * UTF8World::instance=nullptr;


UTF8World::UTF8World()
{
    openFile("UTF8.csv");
}


