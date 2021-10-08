#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>

#define CARDS_NUM 4
#define goblin_s string("goblin")
#define archer_s string("archer")
#define giant_s string("giant")
#define dragon_s string("dragon")
#define witch_s string("witch")
#define ghost_s string("ghost")

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::cerr;

const bool printing_cards = 0;
const bool printing_scenario = 0;

class StrongCard;
class IntelligentCard;
class AgileCard;

class Card{
public:
    Card();
    virtual void fight(Card* enemy) = 0;
    virtual void fight(StrongCard* strong) = 0;
    virtual void fight(IntelligentCard* intelligent) = 0;
    virtual void fight(AgileCard* agile) = 0;
    virtual void print();
    virtual void print_scenario(Card* winner, Card* loser);
    bool valid_val(int val);
    void set_intell(int intell);
    void set_agilit(int agilit);
    void set_streng(int streng);
    int get_intell();
    int get_agilit();
    int get_streng();
    int add_intell(int val);
    int add_agilit(int val);
    int add_streng(int val);    
    void die();
    void duel_fight(Card* enemy);
    bool lives()    { return life;}
    static int round;
protected:
    int intelligence;
    int agility;
    int strength;
    bool life;
};

void swap(Card* &first, Card* &second);

class AgileCard : public Card{
public:
    void fight(Card* card);
    void fight(StrongCard* strong);
    void fight(IntelligentCard* intelligent);
    void fight(AgileCard* agile);
};
class IntelligentCard : public Card{
public:
    void fight(Card* card);
    void fight(StrongCard* strong);
    void fight(IntelligentCard* intelligent);
    void fight(AgileCard* agile);
};
class StrongCard : public Card{
public:
    void fight(Card* card);
    void fight(StrongCard* strong);
    void fight(IntelligentCard* intelligent);
    void fight(AgileCard* agile);
};

class Goblin : public AgileCard{
public:
    Goblin();
    void print();
};
class Archer : public AgileCard{
public:
    Archer();
    void print();
};
class Giant : public StrongCard{
public:
    Giant();
    void print();
};
class Dragon : public StrongCard{
public:
    Dragon();
    void print();
};
class Witch : public IntelligentCard{
public:
    Witch();
    void print();    
};
class Ghost : public IntelligentCard{
public:
    Ghost();
    void print();
};

class Player{
public:
    Card* get_alive_card();
    void print_cards();
    void print_alive_cards();
    void add_card(string card_name);
    void take_card(Card* card);
    bool lost();
    void print();
private:
    vector<Card*> cards;
};

class Game{
public:
    void add_player_card(int player_number, string card_name);
    void play();
    void print_cards();
    void report();
private:
    Player player1;
    Player player2;
};
class Error{
public:
    Error(string des);
private:
    string descrip;
};

#endif