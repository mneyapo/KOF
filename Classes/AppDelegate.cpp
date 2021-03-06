#include "AppDelegate.h"
#include "SplashScene.h"
#include "SonarFrameworks.h"

static cocos2d::Size designResolutionSize = cocos2d::Size(1334, 750);

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
        glview = GLViewImpl::create("King of Fighters");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    cocos2d::Size frameSize = glview->getFrameSize();
    
    register_all_packages();
    
    // Add "res" in the search path
    FileUtils *fileUtils = FileUtils::sharedFileUtils();
    std::vector<std::string> searchPaths = fileUtils->getSearchPaths();
    searchPaths.insert(searchPaths.begin(), "res");
    fileUtils->setSearchPaths(searchPaths);
    
    SonarCocosHelper::IOS::Setup();
    
    SonarCocosHelper::GameCenter::signIn();
    
    // create a scene. it's an autorelease object
    auto scene = SplashScene::createScene();
//    auto scene = GamePlayScene::createScene();
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
    SonarCocosHelper::GameCenter::signIn();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}


