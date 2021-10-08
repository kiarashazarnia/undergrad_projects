#include <iostream>
#include "game.hpp"
#include "rsdl.hpp"
#include "pages.hpp"
using namespace std;

int main()
{
    GamePage playing;
    GameOverPage game_over;
    playing.start();
    playing.new_game();
    playing.update_game();
    playing.play();
    
    game_over.setwindow(playing.getwindow());
    game_over.draw();
    game_over.update();
    Delay(1000);
    playing.stop_game();
    
    return 0;
}