#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "rsdl.hpp"
#include "defines.hpp"
#include <vector>
#include <string>
#include <cstdlib>

float degtorad(int angle);
int radtodeg(float angle);
int xcordin(int x);
int ycordin(int y);

enum class Mode{
    none = 0,
    bomb = 1,
    firing_ball = 2,
    life_ball = 3,
    fire_power = 4,
    brick = 5
};

class Game;
class Table;

class Point{
   public:
        void setx(int _x)   { x = _x;}
        void sety(int _y)   { y = _y;}
        void setxy(int _x, int _y);
        Point(int _x = 0, int _y = 0)   { setxy(_x, _y);}
        Point operator+(Point point);
        int getx()  { return x;}
        int gety()  { return y;}

    protected:
        int x, y;
};
Point xy_to_colrow(Point cordin);
const Point adjacence[8] = {
    Point(1,0),
    Point(0,1),
    Point(1,1),
    Point(-1,0),
    Point(0,-1),
    Point(-1,-1),
    Point(-1,1),
    Point(1,-1)
};

class Thing{
    public:
        Thing() : life(1) {}
        void inc_life();
        void dec_life();
        void setlife(int _life) { life = _life;}
        void kill() { life = 0;}
        int getlife() {return life;}
        bool isalive() { return bool(life);}
        
    protected:
        int life;
};

class Moving : public Point{
    public:
        virtual void setvx(int _vx)   { vx = _vx;}
        virtual void setvy(int _vy)   { vy = _vy;}
        int getvx()  { return vx;}
        int getvy()  { return vy;}
        virtual void move();
        virtual void undomove();
        void reflectx();
        void reflecty();
        void unreflectx();
        void unreflecty();
    protected:
        int vx, vy;
};
class GameElement{
    public:
        virtual void setgame(Game* _game);
        Game* getgame();
    protected:
        Game* game;
};
std::vector<Point> ball_location(Point ball);
class Ball : public Moving, public Thing, public GameElement{
    public:
        Ball();
        void setvy(int _vy);
        bool collides(Point brickp);
        void reflect(Point brick);
        void coll_wall();
        void move();
        void setmode(Mode _mode)    { mode = _mode;}
        void setvel(int angle);
        Mode getmode()  { return mode;}
        void draw(Window*);
        void setinerti(int _inertia);
        void dec_inerti();
    private:
        int inertia;
        Mode mode;
};
class Balls : public Point, public std::vector<Ball>, public GameElement{
    public:
        Balls();
        void coll_wall();
        bool check_lives();
        void reset_all_alive();
        void reset_all_inertia();
        void reset_all_xy();
        void move();
        void generate();
        void setvel(int angle);
        void draw(Window* window);
        void setgame(Game* game);
    private:
};
class Brick : public Moving, public Thing, public GameElement{
    public:
        Brick();
        void draw(Window*);
        RGB brick_collor();
    private:
};
class Bricks : public std::vector<Brick>, public GameElement{
    public:
        void move();
        void draw(Window* window);
        Brick& find(Point point);
        int findi(Point point);
        void remove(Point point);
        void generate(int num, Table& table, int life);
        void setgame(Game* game);
    private:
};
class Gift : public Moving, public Thing, public GameElement{
    public:
        void setmode(Mode _mode)    { mode = _mode;}
        Mode getmode()  { return mode;}
        void bang();
        Gift();
        void draw(Window*);
    private:
        Mode mode;
};
class Gifts : public std::vector<Gift>, public GameElement{
    public:
        void move();
        void draw(Window* window);
        void generate(int x, int y, Mode mode);
        int findi(Point point);
        Gift& find(Point point);
        void remove(Point point);
        void setgame(Game* game);
    private:
};

class User{
    public:
        int getscore() {return score;}
        void setscore(int _score) { score = _score;}
        void setuser(std::string _name, int _score);
        User(): score(0) {}
        void inc_score()    { score++;}

    private:
        std::string name;
        int score;
};

Mode generate_mode();

class Table{
    public:
        bool valid_table_cor(int x, int y);
        void setmode(int x, int y, Mode mode);
        void setmode(Point point, Mode mode);
        Table();
        void move_down();
        bool failed();
        bool isfree(int x, int y);
        Mode getmode(int x, int y);
        Mode getmode(Point point);
        Mode getmode_extended(Point point);
    private:
        Mode table[WIDTH_NUM][HEIGHT_NUM];
};

class Arrow : Point, public GameElement{
    public:
        Arrow();
        void setangle(int _angle);
        int getangle();
        void draw(Window* window);
        void inc_angle();
        void dec_angle();
    private:
        int angle;
};

class Game{
    public:
        void setwindow(Window* _window) {window = _window;}
        void set_game_pointer();
        void handle_collisions();
        void coll_objects();
        void coll_objects_to_ball(Ball* ball);
        void coll_brick(Ball* ball, Point point);
        void coll_bomb(Ball* ball, Point point);
        void remove_brick(Point at);
        void remove_gift(Point at);
        void bang(Gift* bomb);
        void coll_fire_pow(Ball* ball, Point point);
        void coll_life_ball(Ball* ball, Point point);
        void initial_game();
        void prepare();
        void input_n_process();
        void draw();
        void update();
        void generate_bricks();
        void generate();
        void move();
        void stop();
        void handle_key();
        void handle_mouse();
        void setmoving(bool _m) {moving = _m;}
        bool ismoving()    {return moving;}
        bool continous();
        void show_text_balls_state();
    private:
        User user;
        Balls balls;
        Ball firing_ball;
        Bricks bricks;
        Gifts gifts;
        Arrow arrow;
        Event event;
        Window* window;
        Table table;
        bool moving;
        bool lclick;
        bool firing;
};

#endif