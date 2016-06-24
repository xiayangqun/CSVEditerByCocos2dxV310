﻿#include "AppDelegate.h"
#include "CSVGlobalConfig.h"
#include "CSVDefaultKeyConfig.h"
#include "MainScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

#if CC_TARGET_PLATFORM==CC_PLATFORM_WIN32
    //Set Win FrameSize
	glview->setFrameSize(1280, 720);
#endif
    
    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(1280,720,ResolutionPolicy::SHOW_ALL);
    
    auto wirtePath=FileUtils::getInstance()->getWritablePath();
    FileUtils::getInstance()->addSearchPath(wirtePath);
    FileUtils::getInstance()->addSearchPath("res/");
    FileUtils::getInstance()->addSearchPath("res/Res");
    FileUtils::getInstance()->addSearchPath("res/Default");
    FileUtils::getInstance()->addSearchPath("res/CSBFile");
  
    CCLOG("fullPath:%s",wirtePath.c_str());
    
    
    
    CSVGlobalConfig::getInstance();
    CSVDefaultKeyConfig::getInstance();
    
    
    //auto ret=CSVGlobalConfig::getInstance()->getSubFileNameByFullPath(wirtePath);
    
    // create a scene. it's an autorelease object
    auto scene =MainScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
