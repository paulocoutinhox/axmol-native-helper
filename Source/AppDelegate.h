#pragma once

#include "axmol.h"

/**
@brief    The axmol Application.

Private inheritance here hides part of interface from Director.
*/
class AppDelegate : private ax::Application {
public:
    AppDelegate();
    ~AppDelegate() override;

    void initGLContextAttrs() override;

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    bool applicationDidFinishLaunching() override;

    /**
    @brief  Called when the application moves to the background
    */
    void applicationDidEnterBackground() override;

    /**
    @brief  Called when the application reenters the foreground
    */
    void applicationWillEnterForeground() override;
};
