//
//  CCSVParse.cpp
//  Girls3
//
//  Created by bob on 14-2-21.
//
//

#include "CCSVParse.h"


using namespace cocos2d;


CCSVParse::~CCSVParse(void)
{
    
}

void CCSVParse::StringSplit( const string& str, vector<string>& tokens, const char& delimiters )
{
    if(tokens.size()>0)//保证vec是空的
        tokens.clear();
    int length = str.length();
    int start=0;
 
    for(int i=0;i<length;i++)
    {
        
        if(str[i] == delimiters && i == 0)//第一个就遇到分割符
        {
            tokens.push_back("");
            start=i+1;
        }
        else if(str[i] == delimiters)
        {
            tokens.push_back(str.substr(start,i - start));
            start = i+1;
        }
        else if(i == length-1)//到达尾部
        {
            tokens.push_back(str.substr(start,i+1 - start));
        }
        
        
        if(str[i] == delimiters&&i==length-1&&delimiters!='\r')
        {
            tokens.push_back("");
        }
        
    }
    
}


//void CCSVParse::split( vector<string>& field, string line )
//{
//    string fld;
//    unsigned int i,j=0;
//    
//    if( line.length() ==0 )
//        return;
//    i=0;
//    
//    do
//    {
//        if(j<line.length() && line[i]=='"')
//            j = advquoted(line, fld, ++i);
//        else
//            j = advplain(line, fld, i);
//        
//        field.push_back(fld);
//        i = j+1;
//    } while (j<line.length());
//}
//

//
//int CCSVParse::advplain( const string& s, string& fld, int i)
//{
//    unsigned int j;
//    j = s.find_first_of(fieldsep, i);
//    if(j>s.length())
//        j=s.length();
//    fld = string(s,i,j-i);
//    return j;
//}
//
//int CCSVParse::advquoted( const string& s, string& fld, int i)
//{
//    unsigned int j;
//    fld = "";
//    for (j=i; j<s.length(); ++j)
//    {
//        if(s[j]=='"' && s[++j]!='"')
//        {
//            unsigned int k = s.find_first_of(fieldsep, j);
//            if(k>s.length())
//                k = s.length();
//            for(k-=j; k-->0;)
//                fld += s[j++];
//            break;
//        }
//        fld += s[j];
//    }
//    return j;
//}

//bool CCSVParse::openFileNoJiami(const char *fileName)
//{
//    bool isOpend = true;
//    //清空数据就不用每次都创建新的了
//    bodata.clear();
//    string pathKey = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
//    //    CCLog("这里的路径是多少%s",pathKey.c_str());
//    unsigned char* pBuffer = NULL;
//    ssize_t bufferSize = 0;
//    pBuffer = CCFileUtils::sharedFileUtils()->getFileData(pathKey.c_str(), "r", &bufferSize);
//    //    CCLog("pbffer is %s",pBuffer);
//    if (!pBuffer) {
//        isOpend = false;
//        return isOpend;
//    }
//    
//    string s = (char*)pBuffer;
//    string str = s.substr(0,bufferSize);
////    CCLOG("你妹的%s",s.c_str());
//    
//      vector<string> line;
//    //这里我自己改了哈，\n改成\r了
//    //    StringSplit(str, line, '\r');  // 未解密
//    StringSplit(str, line, '\r'); //解密
//    //    CCLOG("容器内的数量是多少%d",line.size());
//    
//    for(unsigned int i=0; i<line.size(); ++i)
//    {
//        vector<string> field;
//        //        CCLog("%s",line[i].c_str());
//        bodata.push_back(line[i]);
//    }
//    
//    return isOpend;
//
//}

//解析 CVS 文件
bool CCSVParse::openFile( const char* fileName, const char splitChar /*=','*/ )
{
    bool isOpend = true;
    data.clear();
    string pathKey = CCFileUtils::sharedFileUtils()->fullPathForFilename(fileName);
    unsigned char* pBuffer = NULL;
    ssize_t bufferSize = 0;
    pBuffer = CCFileUtils::sharedFileUtils()->getFileData(pathKey.c_str(), "r", &bufferSize);

    if (!pBuffer) {
        isOpend = false;
        return isOpend;
    }
    
    string s = (char*)pBuffer;
    string str = s.substr(0,bufferSize);
    
    vector<string> line;
    StringSplit(str, line, '\r'); //解密

    
    for(unsigned int i=0; i<line.size(); ++i)
    {
        vector<string> closVec;
        StringSplit(line[i], closVec, splitChar);
        data.push_back(closVec);
    }
    return isOpend;
}

//获取指定行列的数据
const char* CCSVParse::getData(unsigned int rows, unsigned int cols )
{
    if (rows<0 || rows>=data.size() || cols<0 || cols>=data[rows].size())
    {
        return "";
    }
    return data[rows][cols].c_str();
}

//获取指定数据的列下标
int CCSVParse::findColsData( int cols, const char* value )
{
    for (unsigned int i=0; i<data.size(); ++i)
    {
        if(strcmp(getData(i,cols),value)==0)
            return i;
    }
    return -1;
}