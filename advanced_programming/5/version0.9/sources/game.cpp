#include "game.hpp"
#include "defines.hpp"
#include <cmath>

void Point::setxy(int _x, int _y){
    setx(_x);
    sety(_y);
}
void Moving::move(){
    setx(getx() + getvx());
    sety(gety() + getvy());
}
void User::setuser(std::string _name, int _score){
    name = _name;
    score = _score;
}
Arrow::Arrow(){
    setxy(ARROW_X, ARROW_Y);
    angle = 0;
}
void Arrow::setangle(int _angle){
    angle = _angle;
}
int Arrow::getangle(){
    return angle;
}
void Game::initial_game(){
    setmoving(0);
    lclick = 0;
    firing = 0;
    firing_ball.setmode(Mode::firing_ball);
    firing_ball.kill();
    firing_ball.setinerti(0);
    set_game_pointer();
}
void Game::handle_collisions(){
    coll_objects();
    if(firing){
        firing_ball.coll_wall();
        setmoving(firing_ball.isalive());
    }
    else{
        balls.coll_wall();
        setmoving(balls.check_lives());
    }
}
void Game::coll_objects(){
    if(firing)
            coll_objects_to_ball(&firing_ball);
    else
        for(int i = 0; i < balls.size(); i++)
            coll_objects_to_ball(&balls.at(i));
}
void Game::coll_objects_to_ball(Ball* ball){
    std::vector<Point> location;
    location = ball_location(*ball);
    Mode mode;
    for(int i = 0; i < location.size(); i++){
        mode = table.getmode_extended(location.at(i));
        switch(mode){
            case Mode::brick:
                coll_brick(ball, location.at(i));
            break;
            case Mode::bomb:
                coll_bomb(ball, location.at(i));
            break;
            case Mode::fire_power:
                coll_fire_pow(ball, location.at(i));
            break;
            case Mode::life_ball:
                coll_life_ball(ball, location.at(i));
            break;
            case Mode::none:
            break;
            default:
                throw Error("Invalid table mode.");
            break;
        }
    }
}
void Game::coll_brick(Ball* ball, Point point){
    Brick *brick = &bricks.find(point);
    if(!brick -> isalive())
        return;
    switch(ball -> getmode()){
        case Mode::firing_ball:
            brick -> kill();
            bricks.remove(point);
            table.setmode(point, Mode::none);
        break;
        case Mode::none:
            ball -> reflect(*brick);
            brick -> dec_life();
            if(!brick -> isalive()){
                table.setmode(point, Mode::none);
                bricks.remove(point);
            }
        break;
        default:
            throw Error("invalid ball mode.");
        break;
    }
}
bool Ball::collides(Point bricp){
    int balx = getx();
    int baly = gety();
    int brix = xcordin(bricp.getx());
    int briy = ycordin(bricp.gety());
    return !(   balx + BALL_WIDTH < brix
            ||  baly + BALL_HEIGHT < briy
            ||  balx > brix + BRICK_WIDTH
            ||  baly > briy + BRICK_HEIGHT);
}
void Ball::reflect(Point brickp){
    reflectx();
    if(collides(brickp)){
        unreflectx();
        reflecty();
    }
}
void Game::coll_bomb(Ball* ball, Point point){
    Gift* gift = &gifts.find(point);
    if(ball -> getmode() != Mode::firing_ball)
        ball -> reflect(*gift);
    bang(gift);
}

void Game::bang(Gift* bomb){
    if(bomb -> getmode() != Mode::bomb)
        return;
    Brick* brick;
    Point adjacent;
    Point point = (Point) *bomb; 
    Mode adj_mode;
    bomb -> kill();
    table.setmode(point, Mode::none);
    gifts.remove(point);
    for(int i = 0; i < 8; i++){
        adjacent = point + adjacence[i];
        adj_mode = table.getmode_extended(adjacent);
        if(adj_mode == Mode::brick){
            brick = &bricks.find(adjacent);
            brick -> kill();
            bricks.remove(adjacent);
            table.setmode(adjacent, Mode::none);
        }
        else if(adj_mode == Mode::bomb)
            bang(&gifts.find(adjacent));
    }
}
void Game::coll_fire_pow(Ball* ball, Point point){
    firing_ball.setlife(1);
    table.setmode(point, Mode::none);
    gifts.find(point).kill();
    gifts.remove(point);
}
void Game::coll_life_ball(Ball* ball, Point point){
    Gift* gift = &gifts.find(point);
    gift -> kill();
    table.setmode(point, Mode::none);
    gifts.remove(point);
    balls.generate();
    balls.at(balls.size() - 1).kill();
}
void Game::input_n_process(){
    event = window -> pollForEvent();
    switch(event.type())
    {
        case QUIT:
            stop();
        break;
        case KEY_PRESS:
            handle_key();
        break;
        case LCLICK:
            lclick = 1;
        break;
        case MMOTION: case LRELEASE:
            handle_mouse();
        default:
        break;
    }
}

bool valid_arrow_key(char key){
    return (key != SPACE) && (key == RIGHT) || (key == LEFT);
}

void Game::handle_key(){
    char key = event.pressedKey();
    switch(key){
        case RIGHT:
            arrow.inc_angle();
        break;
        case LEFT:
            arrow.dec_angle();
        break;
        case SPACE:
            balls.setvel(arrow.getangle());
            firing_ball.setvel(arrow.getangle());
            setmoving(1);
        break;
    }
}
void Game::handle_mouse(){
    if(!lclick)
        return;
    int delta = event.mouseY() / event.mouseX();
    switch(event.type()){
        MMOTION:
            delta = radtodeg(atan(delta));
            arrow.setangle(arrow.getangle() + delta);
        break;
        LRELEASE:
            balls.setvel(arrow.getangle());
            lclick = 0;
            setmoving(1);
        break;
    }
}
void Game::update(){
    window -> update_screen();
}
Mode generate_mode(){
    float random_val, prob = 0;
    random_val = (rand() % 10) / 10.0;
    prob += LIFE_PROB;
    if(random_val < prob)
        return Mode::life_ball;
    prob += FIRE_PROB;
    if(random_val < prob)
        return Mode::fire_power;
    prob += BOMB_PROB;
    if(random_val < prob)
        return Mode::bomb;
    return Mode::none;
}
void Game::generate_bricks(){
    int state = user.getscore() % 5;
    int brick_life = user.getscore() + 1;
    switch(state)
    {
        case 0: case 1: case 2:
            bricks.generate(1, table, brick_life);
        break;
        case 3:
            bricks.generate(2, table, brick_life);
        break;
        case 4:
            bricks.generate(4, table, brick_life);
        break;
    }
}
bool Table::valid_table_cor(int x, int y){
    return x >= 0 && y >= 0 && x < WIDTH_NUM && y < HEIGHT_NUM;
}
void  Table::setmode(int x, int y, Mode mode){
    if(valid_table_cor(x, y))
        table[x][y] = mode;
}
Table::Table(){
    for(int x = 0; x < WIDTH_NUM; x++)
        for(int y = 0; y < HEIGHT_NUM; y++)
            setmode(x, y, Mode::none);
}
void  Table::move_down(){
    for(int x = 0; x < WIDTH_NUM; x++)
        for(int y = HEIGHT_NUM - 1; y > 0; y--)
            setmode(x, y, getmode(x,y - 1));
    for(int x = 0; x < WIDTH_NUM; x++)
        setmode(x, 0, Mode::none);
}
bool  Table::failed(){
    for(int x = 0; x < WIDTH_NUM; x++)
        if(getmode(x, HEIGHT_NUM-1) == Mode::brick || getmode(x, HEIGHT_NUM-1) == Mode::bomb)
            return 1;
    return 0;
}
bool  Table::isfree(int x, int y){
    if(valid_table_cor(x,y))
        return getmode(x,y) == Mode::none;
    else throw Error("invalid table cor.");
}
void Game::generate(){
    generate_bricks();
    Mode mode;
    srand(time(NULL));
    for(int x = 0; x < WIDTH_NUM; x++){
        if(!table.isfree(x, 0))
            continue;
        mode = generate_mode();
        switch(mode){
            case Mode::life_ball:
            case Mode::fire_power:
                gifts.generate(x, 0, mode);
            break;
            case Mode::bomb:
                gifts.generate(x, 0, mode);
            break;
            case Mode::none:
            break;
        }
        table.setmode(x, 0, mode);
    }
}
void Balls::generate(){
    Ball ball;
    push_back(ball);
}
Gift::Gift()
{
    setvx(0);
    setvy(FALL_VELOCITY);
}
void Gifts::generate(int x, int y, Mode mode){
    Gift gift;
    gift.setxy(x, y);
    gift.setvy(FALL_VELOCITY);
    gift.setmode(mode);
    push_back(gift);
}
Brick gen_one_brick(Table& table, int life){
    int x;
    Brick brick;
    brick.setlife(life);
    brick.setvy(FALL_VELOCITY);
    srand(time(NULL));
    while(true){
        x = rand() % WIDTH_NUM;
        if(table.isfree(x, 0)){
            table.setmode(x, 0, Mode::brick);
            brick.setxy(x, 0);
            break;
        }
    }
    return brick;
}
void Bricks::generate(int num, Table& table, int life){
    Brick brick;
    for(int i = 0; i < num; i++){
        brick = gen_one_brick(table, life);
        push_back(brick);
    }
}
void Game::stop(){
    delete window;
}
void Arrow::inc_angle(){
    if(getangle() < 180)
        setangle(getangle() + ANGLE_RATE);
}
void Arrow::dec_angle(){
    if(getangle() > 0)
        setangle(getangle() - ANGLE_RATE);
}
void Ball::move(){
    if(!isalive())
        return;
    if(inertia){
        dec_inerti();
        return;
    }
    Moving::move();
}
void Game::move(){
    if(moving){
        if(firing)
            firing_ball.move();
        else    
            balls.move();
    }
    else{
        bricks.move();
        gifts.move();
        table.move_down();
    }
}
void Bricks::move(){
    for(int i = 0; i < size(); i++){
        at(i).move();
    }
}
void Gifts::move(){
    for(int i = 0; i < size(); i++){
        at(i).move();
    }
}
void Balls::move(){
    for(int i = 0; i < size(); i++){
        at(i).move();
    }
}
Ball::Ball(){
    setxy(BALL_X, BALL_Y);
    setvx(BALL_V);
    setvy(BALL_V);
    setinerti(ALOT);
    setmode(Mode::none);
}
void Ball::setinerti(int _inertia){
    if(_inertia >= 0)
        inertia = _inertia;
    else throw Error("inertia underflowed.");
}
void Ball::dec_inerti(){
    if(inertia >= 1)
        inertia--;
    else throw Error("inertia underflowed.");
}
void Balls::setvel(int angle){
    for(int i = 0; i < size(); i++){
        at(i).setvel(angle);
    }
}
void Ball::setvel(int angle){
    float teta = degtorad(angle);
    float _vy = -sin(teta) * BALL_V;
    float _vx = -cos(teta) * BALL_V;
    setvy(_vy);
    setvx(_vx);
}
float degtorad(int angle){
    return angle*PI/180.0;
}
int radtodeg(float angle){
    return angle*180.0/PI;
}
void Moving::undomove(){
    x -= vx;
    y -= vy;
}
void Moving::reflectx(){
        vx *= -1;
        move();
}
void Moving::reflecty(){
        vy *= -1;
        move();
}
void Moving::unreflectx(){
        undomove();
        vx *= -1;
}
void Moving::unreflecty(){
        undomove();
        vy *= -1;
}
void Ball::coll_wall(){
    switch(getmode()){
        case Mode::firing_ball:
            if(x > MAX_X || x < MIN_X || y > MAX_Y || y < MIN_Y)
                kill();
        break;
        case Mode::none:
            if(x > MAX_X || x < MIN_X){
            reflectx();
            }
            if(y < MIN_Y){
                reflecty();
            }
            if(y > MAX_Y){
                kill();
            }
        break;
        default:
            throw Error("invalid ball mode.");
    }
}
void Balls::coll_wall(){
    for(int i = 0; i < size(); i++){
        at(i).coll_wall();
    }
}
bool Balls::check_lives(){
    for(int i = 0; i < size(); i++){
        if(at(i).isalive())
            return true;
    }
    return false;
}
void Balls::reset_all_alive(){
    for(int i = 0; i < size(); i++){
        at(i).setlife(true);
    }
}
void Balls::reset_all_inertia(){
    for(int i = 0; i < size(); i++){
        at(i).setinerti(i*(TICK_TIME/CLK));
    }
}
void Game::prepare(){
    balls.reset_all_alive();
    balls.reset_all_inertia();
    balls.reset_all_xy();

    firing = firing_ball.isalive();
    firing_ball.setinerti(0);
    firing_ball.setxy(BALL_X, BALL_Y);

    user.inc_score();
}
void Balls::reset_all_xy(){
    for(int i = 0; i < size(); i++){
        at(i).setxy(getx(), gety());
    }
}
bool Game::continous(){
    return !table.failed();
}
Mode Table::getmode(int x, int y){
    if(valid_table_cor(x,y))
        return table[x][y];
    throw Error("invalid table cor.");
}
Mode Table::getmode_extended(Point point){
    int x = point.getx();
    int y = point.gety();
    if(valid_table_cor(x,y))
        return table[x][y];
    else return Mode::none;    
}
Balls::Balls(){
    generate();
    setxy(BALL_X, BALL_Y);
}
Point xy_to_colrow(Point cordin){
    int x = cordin.getx();
    int y = cordin.gety();
    int col = (x - GWIN_X)/BRICK_WIDTH;
    int row = (y - GWIN_Y - LOG_HEIGHT)/BRICK_HEIGHT;
    return Point(col, row);
}
std::vector<Point> ball_location(Point ball){
    int x = xy_to_colrow(ball).getx();
    int y = xy_to_colrow(ball).gety();
    std::vector<Point> location;
    location.push_back(Point(x, y));
    if(ball.getx() + BALL_WIDTH > xcordin(x + 1))
        location.push_back(Point(x + 1, y));
    if(ball.gety()  + BALL_HEIGHT > ycordin(y + 1))
        location.push_back(Point(x, y + 1));
    if(location.size() == 3)
        location.push_back(Point(x + 1, y + 1));
    return location;
}
Mode Table::getmode(Point point){
    return getmode(point.getx(), point.gety());
}
Brick& Bricks::find(Point point){
    int i = findi(point);
    return at(i);
}
int Bricks::findi(Point point){
    for(int i = 0; i < size(); i++){
        if(point.getx() == at(i).getx() && point.gety() == at(i).gety())
            return i;
    }
    throw Error("brick not found at point.");
}
void Thing::inc_life(){
    life++;
}
void Thing::dec_life(){
    if(life > 0)
        life--;
    else throw Error("life is underflowed.");
}
void Table::setmode(Point point, Mode mode){
    setmode(point.getx(),point.gety(), mode);
}
Point Point::operator+(Point point){
    return Point(x + point.x, y + point.y);
}
void Bricks::remove(Point point){
    erase(begin() + findi(point));
}
Gift& Gifts::find(Point point){
    int i = findi(point);
    return at(i);
}
int Gifts::findi(Point point){
    for(int i = 0; i < size(); i++){
        if(point.getx() == at(i).getx() && point.gety() == at(i).gety())
            return i;
    }
    throw Error("gift not found at point.");
}
void Gifts::remove(Point point){
    erase(begin() + findi(point));
}
Brick::Brick(){
    setvx(0);
    setvy(FALL_VELOCITY);
}
void Ball::setvy(int _vy){
    if(_vy == 0){
        if(y >= MAX_Y-1)
            setvy(-1);
        else
            setvy(1);
    }
    else Moving::setvy(_vy);
}
void  GameElement::setgame(Game* _game){
    if(_game == NULL)
        throw Error("null game pointer.");
    game = _game;
}
Game* GameElement::getgame(){
    if(game == NULL)
        throw Error("null game pointer.");
    return game;    
}
void Balls::setgame(Game* _game){
    GameElement::setgame(_game);
    for(int i = 0; i < size(); i++){
        at(i).setgame(_game);
    }
}
void Bricks::setgame(Game* _game){
    GameElement::setgame(_game);
    for(int i = 0; i < size(); i++){
        at(i).setgame(_game);
    }
}
void Gifts::setgame(Game* _game){
    GameElement::setgame(_game);
    for(int i = 0; i < size(); i++){
        at(i).setgame(_game);
    }
}
void Game::set_game_pointer(){
    bricks.setgame(this);
    balls.setgame(this);
    gifts.setgame(this);
    arrow.setgame(this);
}