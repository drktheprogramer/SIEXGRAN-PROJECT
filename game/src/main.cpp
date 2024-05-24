#include<OGame.hpp>
#include<iostream>

int main(void)
{
    try
    {
        OGame game;
        game.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    
    
    return 0;
}
