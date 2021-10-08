#ifndef __DEFINES_HPP__
#define __DEFINES_HPP__

#define CLK 10
#define ANGLE_RATE 2
#define TICK_TIME 60
#define PI 3.14
#define ALOT 9999

#define BOMB_PROB 0.1
#define LIFE_PROB 0.3
#define NONE_PROB 0.5
#define FIRE_PROB 0.1

#define WIN_WIDTH 908
#define WIN_HEIGTH 600

#define WIN_TITLE "PandaKungFu"

#define GWIN_X 59
#define GWIN_Y 59
#define LOG_HEIGHT 70
#define GWIN_WIDTH 370
#define GWIN_HEIGTH 486

#define MIN_X GWIN_X
#define MIN_Y GWIN_Y + LOG_HEIGHT
#define MAX_X (GWIN_X + GWIN_WIDTH - BALL_WIDTH)
#define MAX_Y (GWIN_Y + GWIN_HEIGTH - BALL_HEIGHT - BALL_NUMH)

#define WINDOW_TITLE "RSDL Tutorial"

#define WIDTH_NUM 5
#define HEIGHT_NUM 8

#define BGROUND "../assets/bg.png"

#define FALL_VELOCITY 1

#define BALL_IMG "../assets/yingyang.png"
#define FIRE_BALL_IMG "../assets/fireball.png"
#define BALL_WIDTH  30
#define BALL_HEIGHT  30
#define BALL_X (GWIN_X + (GWIN_WIDTH - BALL_WIDTH) / 2)
#define BALL_Y (GWIN_Y + GWIN_HEIGTH - BALL_HEIGHT - BALL_NUMH)
#define BALL_V 10
#define BALL_NUMH 20

#define BRICK_WIDTH 74 
#define BRICK_HEIGHT 40

#define FIRE_POW_IMG        "../assets/fire.png"
#define FIRE_POW_WIDTH  BRICK_HEIGHT
#define FIRE_POW_HEIGHT  BRICK_HEIGHT
#define BOMB_IMG    "../assets/bomb.png"
#define BOMB_WIDTH  BRICK_HEIGHT
#define BOMB_HEIGHT  BRICK_HEIGHT
#define LIFE_BALL_IMG   "../assets/lifeball.png"
#define LIFE_BALL_WIDTH BRICK_HEIGHT
#define LIFE_BALL_HEIGHT BRICK_HEIGHT


#define ARROW1_IMG        "../assets/arrow1.png"
#define ARROW2_IMG        "../assets/arrow2.png"
#define ARROW_X (GWIN_X + (GWIN_WIDTH - ARROW_WIDTH)/2)
#define ARROW_Y (GWIN_Y + GWIN_HEIGTH - ARROW_HEIGHT)
#define ARROW_WIDTH  180
#define ARROW_HEIGHT  55

#define TXMARGIN (BRICK_WIDTH / 2 - 5)
#define TYMARGIN 10
#define FONT "../assets/Jellee-Roman.ttf"
#define FSIZE 16

#define UP      'w'
#define DOWN    's'
#define RIGHT   'd'    
#define LEFT    'a'
#define SPACE   32

#define IMG_X 150
#define IMG_Y 120
#define IMG_WIDTH 220
#define IMG_HEIGHT 220
#define FIELD_WIDTH 100
#define FIELD_HEIGHT 50
#define MARGIN 10
#define TITLE_X (GWIN_X + 20)
#define TITLE_Y (GWIN_Y + 20)
#define BIGFS 40
#define USER_IMG "../assets/username.png"

#define GOVER_TX (GWIN_X + 30)
#define GOVER_TY (GWIN_Y + 20)  
#define GOVER_TS 35
#define GOVER_IMG "../assets/gameover.png"

class Error{
    public:
        Error(std::string _exp) : exp(_exp) {
            std::cerr << "\nE: " << exp << std::endl;
        }
    private:
        std::string exp;
};

#endif