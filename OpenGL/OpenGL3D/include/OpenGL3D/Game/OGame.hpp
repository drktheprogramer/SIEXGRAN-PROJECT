#pragma once
#include<memory>
#include<OPrerequisites.hpp>
struct OGraphicsEngine;
struct OWindow;

struct OGame {
    OGame();
    ~OGame();

    virtual void onCreate();
    virtual void onUpdate();
    virtual void onQuit();

    void run();
    void quit();
protected:
    bool m_isRunning=true;
    std::unique_ptr<OGraphicsEngine> m_graphicsEngine;
    std::unique_ptr<OWindow> m_display;
 OVertexArrayObjectPtr m_triangleVAO;
};