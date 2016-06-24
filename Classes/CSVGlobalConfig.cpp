//
//  CSVGlobal.cpp
//  CSVConfig
//
//  Created by xiayangqun on 16/6/22.
//
//

#include "CSVGlobalConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <sys/stat.h>
#include "dirent.h"
#include "unistd.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <iostream> 
#include <io.h>
#include <fstream>
#include <windows.h>

#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
string  CSVGlobalConfig::GBKToUTF8(const std::string& strGBK)
{
	string strOutUTF8 = "";
	WCHAR * str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char * str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return strOutUTF8;
}

string CSVGlobalConfig::UTF8ToGBK(const std::string& strUTF8)
{
	/*
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
	unsigned short * wszGBK = new unsigned short[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUTF8.c_str(), -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
    std::string strTemp(szGBK);
	delete[]szGBK;
	delete[]wszGBK;
	return strTemp;
	*/
	return "";
}


#endif


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
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

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

#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	
	setlocale(LC_ALL, ".936");
	long hFile = 0;
	struct _finddata_t fileInfo;

	string pathName, exdName;

	if ((hFile = _findfirst(pathName.assign(fullPath).append("/*").c_str(), &fileInfo)) != -1)
	{
		do
		{
			std::string str = fileInfo.name;
			if (str != "GlobalConfig.csv"&& str != "CSVDefaultKeyConfig.csv"&&str[0] != '.')
				retVec.push_back(str);
		} while (_findnext(hFile, &fileInfo) == 0);

		_findclose(hFile);
	}

#endif


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




