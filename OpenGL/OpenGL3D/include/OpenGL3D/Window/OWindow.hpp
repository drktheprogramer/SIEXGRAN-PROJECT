struct OWindow {
    OWindow();
    ~OWindow();

    void onDestroy();
    bool isClosed();
private:
    void* m_handle=nullptr;
};


