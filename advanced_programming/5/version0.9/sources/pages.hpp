#ifndef __PAGES_HPP__
#define __PAGES_HPP__

#include "rsdl.hpp"
#include "defines.hpp"
#include "game.hpp"
class Page{
    public:
        Page(): window(NULL) {}
        void start();
        void refresh();
        void update();
        Window* getwindow();
        void setwindow(Window* _window);    
    protected:
        Window* window;
};

class GamePage : public Page{
    public:
        void update_game();
        void new_game();
        void play();
        void stop_game();
    private:
        Game* game;
};
class UserPage : public Page{
    public:
        void draw();
        void save();
        void cancel();
    private:
};
class GameOverPage : public Page{
    public:
        void draw();
    private:
};


#endif