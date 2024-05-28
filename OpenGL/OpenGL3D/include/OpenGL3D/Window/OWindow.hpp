#pragma once
#include<ORect.hpp>

struct OWindow {
    OWindow();
    ~OWindow();

    void makeCurrentContext();
    void present(bool vsync);
 ORect getInnerSize();

private:
    void* m_handle=nullptr;
    void* m_context=nullptr;
};


