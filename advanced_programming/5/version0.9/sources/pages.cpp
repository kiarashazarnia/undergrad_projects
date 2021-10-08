#include "pages.hpp"

void Page::refresh(){
    window -> fill_rect(GWIN_X, GWIN_Y, GWIN_WIDTH, GWIN_HEIGTH, WHITE);
}
void Page::start(){
    window = new Window(WIN_WIDTH, WIN_HEIGTH, WIN_TITLE);
    window -> clear();
    window -> draw_bg(BGROUND);
}
void Page::update(){
    window -> draw_bg(BGROUND);
    window -> update_screen();
}
Window* Page::getwindow(){
    return window;
}
void GamePage::update_game(){
    window -> clear();
    refresh();
    game -> draw();
    window -> draw_bg(BGROUND);
    window -> update_screen();
}
void GamePage::new_game(){
    game = new Game;
    game -> initial_game();
    game -> setwindow(getwindow());
}
void GamePage::play(){
    while(game -> continous()){
        game -> move();
        game -> generate();
        game -> prepare();
        while(!game -> ismoving()){
            game -> input_n_process();
            update_game();
            Delay(CLK);
        }
        while(game -> ismoving()){
            game -> move();
            game -> handle_collisions();
            update_game();
            Delay(CLK);
        }
    }
}
void GamePage::stop_game(){
    game -> stop();
    delete game;
}
void UserPage::draw(){
    window -> show_text("Enter Username:",TITLE_X, TITLE_Y , BLACK, FONT, BIGFS);
    window -> draw_png(USER_IMG, IMG_X, IMG_Y, IMG_WIDTH, IMG_HEIGHT);
}
void GameOverPage::draw(){
    Page::refresh();
    window -> show_text("Game Over Panda!", GOVER_TX, GOVER_TY, BLACK, FONT, GOVER_TS);
    window -> draw_png(GOVER_IMG, IMG_X, IMG_Y, IMG_WIDTH, IMG_HEIGHT);
}
void Page::setwindow(Window* _window){
    window = _window;
}
