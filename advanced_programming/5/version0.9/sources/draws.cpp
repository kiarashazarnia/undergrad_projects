#include "game.hpp"

void Ball::draw(Window* window){
    switch(getmode()){
        case Mode::none:
            window -> draw_png(BALL_IMG, getx(), gety(), BALL_WIDTH, BALL_HEIGHT);
        break;
        case Mode::firing_ball:
            window -> draw_png(FIRE_BALL_IMG, getx(), gety(), BALL_WIDTH, BALL_HEIGHT);
        break;
    }
}
void sync_collor(unsigned& collor){
    while(collor >= 256){
        collor %= 256;
    }
}
void sync_collor(unsigned& R,unsigned& G,unsigned& B){
    sync_collor(R);
    sync_collor(G);
    sync_collor(B);
}
RGB Brick::brick_collor(){
    unsigned    R = 200 + 10*getlife(),
                G = 100 + 5*getlife(),
                B = 50 + 5*getlife();
    sync_collor(R, G, B);
    RGB brown(R, G, B);
    return brown;
}
RGB compliment(RGB collor){
    unsigned    R = 255 - collor.red,
                G = 255 - collor.green,
                B = 255 - collor.blue;
    RGB compliment_collor(R, G, B);
    return compliment_collor;
}
int xcordin(int x){
    return GWIN_X + x*BRICK_WIDTH;
}
int ycordin(int y){
    return GWIN_Y + LOG_HEIGHT + y*BRICK_HEIGHT;
}
void Brick::draw(Window* window){
    int x = xcordin(getx());
    int y = ycordin(gety());
    RGB collor = brick_collor();
    window -> fill_rect(x , y, BRICK_WIDTH, BRICK_HEIGHT, collor);
    window -> draw_rect(x , y, BRICK_WIDTH, BRICK_HEIGHT, compliment(collor));
    window -> show_text(std::to_string(getlife()), x + TXMARGIN, y + TYMARGIN, compliment(collor), FONT, FSIZE);
}
void Gift::draw(Window* window){
    int x = xcordin(getx()) + BRICK_WIDTH/4;
    int y = ycordin(gety());
    if(gety() >= HEIGHT_NUM)
        return;
    switch(mode){
        case Mode::fire_power:
            window -> draw_png(FIRE_POW_IMG, x, y, FIRE_POW_WIDTH, FIRE_POW_HEIGHT);
            break;
        case Mode::bomb:
            window -> draw_png(BOMB_IMG, x, y, BOMB_WIDTH, BOMB_HEIGHT);
            break;
        case Mode::life_ball:
            window -> draw_png(LIFE_BALL_IMG, x, y, LIFE_BALL_WIDTH, LIFE_BALL_HEIGHT);
            break;
        default:
        break;
    }
}

void Balls::draw(Window* window){
    for(int i = 0; i < this -> size(); i++){
        if(at(i).isalive())
            this -> at(i).draw(window);
    }
}

void Bricks::draw(Window* window){
    for(int i = 0; i < this -> size(); i++){
        if(at(i).isalive())
            this -> at(i).draw(window);
    }
}

void Gifts::draw(Window* window){
    for(int i = 0; i < this -> size(); i++){
        if(at(i).isalive())
            this -> at(i).draw(window);
    }
}
void Arrow::draw(Window* window){
    if(getangle() < 90)
        window -> draw_png(ARROW1_IMG ,ARROW_X, ARROW_Y, ARROW_WIDTH, ARROW_HEIGHT, getangle());
    else
        window -> draw_png(ARROW2_IMG ,ARROW_X, ARROW_Y, ARROW_WIDTH, ARROW_HEIGHT, getangle() - 180);
}
void Game::draw(){
    window -> draw_line(MIN_X, MIN_Y, MAX_X + BALL_WIDTH, MIN_Y, BLACK);
    window -> draw_line(MIN_X, MAX_Y + BALL_HEIGHT, MAX_X + BALL_WIDTH, MAX_Y + BALL_HEIGHT, BLACK);
    bricks.draw(window);
    gifts.draw(window);
    if(moving)
    {   
        if(firing)
            firing_ball.draw(window);
        else
            balls.draw(window);
    }
    else{
        show_text_balls_state();
        arrow.draw(window);
    }
}
void Game::show_text_balls_state(){
    if(firing)
        window -> show_text("Firing YingYang!", ARROW_X + 25, GWIN_Y+GWIN_HEIGTH - BALL_NUMH, BLACK, FONT, FSIZE);
    else
        window -> show_text(std::to_string(balls.size()) + "#YY", BALL_X , GWIN_Y+GWIN_HEIGTH - BALL_NUMH, RGB(150,50,50), FONT, FSIZE + 2);
}