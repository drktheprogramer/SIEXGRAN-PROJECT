#include<memory>
struct OWindow;
struct OGame {
    OGame();
    ~OGame();

    void run();
    void quit();
protected:
    bool m_isRunning=true;
    std::unique_ptr<OWindow> m_display;
};