#include "game.hpp"

int Card::round = 0;
Card::Card(){
    life = 1;
}
bool Card::valid_val(int val){
    return 0 <= val && val <= 100;
}
int Card::add_intell(int val){
    set_intell(get_intell() + val);
}
int Card::add_agilit(int val){
    set_agilit(get_agilit() + val);
}
int Card::add_streng(int val){
    set_streng(get_streng() + val);
}
void Card::set_intell(int intell){
    if(valid_val(intell))
        intelligence = intell;
}
void Card::set_agilit(int agilit){
    if(valid_val(agilit))
        agility = agilit;
}
void Card::set_streng(int streng){
    if(valid_val(streng))
        strength = streng;
}
int Card::get_intell(){
    return intelligence;
}
int Card::get_agilit(){
    return agility;
}
int Card::get_streng(){
    return strength;
}
void Card::die(){
    life = 0;
}
Goblin::Goblin(){
    strength = 50;
    intelligence = 10;
    agility = 90;
}
Archer::Archer(){
    strength = 35;
    intelligence = 40;
    agility = 75;
}
Giant::Giant(){
    strength = 85;
    intelligence = 35;
    agility = 30;
}
Dragon::Dragon(){
    strength = 70;
    intelligence = 30;
    agility = 50;
}
Witch::Witch(){
    strength = 40;
    intelligence = 80;
    agility = 30;
}
Ghost::Ghost(){
    strength = 40;
    intelligence = 70;
    agility = 40;
}

void AgileCard::fight(StrongCard* enemy){
    this -> die();
    enemy -> add_agilit(10);
    print_scenario(enemy, this);
}
void AgileCard::fight(IntelligentCard* enemy){
    int my_power = get_streng();
    int enemy_power = enemy -> get_streng();
    if(my_power == enemy_power)
        duel_fight(enemy);
    Card* winner = this;
    Card* loser = enemy;
    if(my_power < enemy_power)
        swap(winner, loser);
    loser -> die();
    winner -> add_agilit(10);
    winner -> add_intell(10);
    print_scenario(winner, loser);
}
void swap(Card* &first, Card* &second){
    Card* temp = first;
    first = second;
    second = temp;
}
void AgileCard::fight(AgileCard* enemy){
    int my_power = get_intell() + get_streng();
    int enemy_power = enemy -> get_intell() + enemy -> get_streng();
    if(my_power == enemy_power)
        return duel_fight(enemy);
    Card* winner = this;
    Card* loser = enemy;
    if(my_power < enemy_power)
        swap(winner, loser);
    loser -> die();
    winner -> add_intell(5);
    winner -> add_streng(5);
    print_scenario(winner, loser);
}
void StrongCard::fight(StrongCard* enemy){
    int my_power = get_streng();
    int enemy_power = enemy -> get_streng();
    if(my_power == enemy_power)
        return duel_fight(enemy);
    Card* winner = this;
    Card* loser = enemy;
    if(my_power < enemy_power)
        swap(winner, loser);
    loser -> die();
    winner -> add_intell(10);
    winner -> add_agilit(10);
    print_scenario(winner, loser);
}
void StrongCard::fight(IntelligentCard* enemy){
    int my_power = get_agilit();
    int enemy_power = enemy -> get_agilit();
    if(my_power == enemy_power)
        return duel_fight(enemy);
    Card* winner = this;
    Card* loser = enemy;
    if(my_power < enemy_power)
        swap(winner, loser);
    loser -> die();
    winner -> add_streng(10);
    print_scenario(winner, loser);
}
void StrongCard::fight(AgileCard* enemy){
    enemy -> fight(this);
}
void IntelligentCard::fight(IntelligentCard* enemy){
    int my_power, enemy_power;
    if(abs(get_intell() - enemy -> get_intell()) >= 20){
        my_power = get_intell();
        enemy_power = enemy -> get_intell();
    }else{
        my_power = get_agilit() + get_streng();
        enemy_power = enemy -> get_agilit() + enemy -> get_streng();
    }
    if(my_power == enemy_power)
        return duel_fight(enemy);
    Card* winner = this;
    Card* loser = enemy;
    if(my_power < enemy_power)
        swap(winner, loser);
    loser -> die();
    winner -> add_streng(5);
    winner -> add_agilit(5);
    print_scenario(winner, loser);
}
void IntelligentCard::fight(StrongCard* enemy){
    enemy -> fight(this);
}
void IntelligentCard::fight(AgileCard* enemy){
    enemy -> fight(this);
}
void Card::duel_fight(Card* enemy){
    srand(time(NULL));    
    bool my_wish = rand() % 2;
    if(my_wish){
        enemy -> die();
        print_scenario(this, enemy);
    }
    else{
        this -> die();
        print_scenario(enemy, this);
    }
}
Card* new_card(string card_name){
    Card* card;
    if(card_name == goblin_s)
        card = new Goblin;
    else if(card_name == archer_s)
        card = new Archer;
    else if(card_name == giant_s)
        card = new Giant;
    else if(card_name == dragon_s)
        card = new Dragon;
    else if(card_name == witch_s)
        card = new Witch;
    else if(card_name == ghost_s)
        card = new Ghost;
    else
        throw Error("invalid card_name");
    return card;
}
void Player::add_card(string card_name){
    Card* card = new_card(card_name);
    if(cards.size() >= CARDS_NUM)
        throw Error("too many cards");
    else
        cards.push_back(card);
}
void Player::take_card(Card* card){
    while(card -> lives() && !this -> lost()){
        get_alive_card() -> fight(card);
    }
}
Card* Player::get_alive_card(){
    for(int i = 0; i < cards.size(); i++)
        if(cards.at(i) -> lives())
            return cards.at(i);
    return NULL;
};
bool Player::lost(){
    bool lost = 1;
    for(int i = 0; i < cards.size(); i++)
        lost &= !cards.at(i) -> lives();
    return lost;
}
void Game::add_player_card(int player_number, string card_name){
    switch(player_number){
        case 1:
            player1.add_card(card_name);
        break;
        case 2:
            player2.add_card(card_name);
        break;
        default:
            throw Error("invalid playar_number");
        break;
    }
}
void Game::play(){
    for(int i = 0; true; i++){
        if(player1.lost() || player2.lost())
            return report();
        player2.take_card(player1.get_alive_card());
        print_cards();
    }
}
Error::Error(string des){
    descrip = des;
    cerr << descrip << endl;
}
void Game::report(){
    if(!player1.lost() && player2.lost())
        cout << "1" << endl;
    else if(player1.lost() && !player2.lost())
        cout << "2" << endl;
    else
        throw Error("invalid result");
}
void IntelligentCard::fight(Card* enemy){
    enemy -> fight(this);
}
void AgileCard::fight(Card* enemy){
    enemy -> fight(this);
}
void StrongCard::fight(Card* enemy){
    enemy -> fight(this);
}
void Game::print_cards(){
    if(!printing_cards)
        return;
    player1.print_alive_cards();
    player2.print_alive_cards();
}
void Card::print_scenario(Card* winner, Card* loser){
    if(!printing_scenario)
        return;
    winner -> print();
    cout << "in round "<< ++round << " killed:" << endl;
    loser -> print();
    cout << "-------------------------------" << endl;
}
void Player::print_cards(){
    for(int i = 0; i < cards.size(); i++){
        cards.at(i) -> print();
    }
    cout << "_______________________________" << endl;
}
void Player::print_alive_cards(){
    for(int i = 0; i < cards.size(); i++){
        if(cards.at(i) -> lives())
            cards.at(i) -> print();
    }
    cout << "_______________________________" << endl;
}
void Card::print(){
    cout << "i(" << get_intell() << ")\t" << 
                 "a(" << get_agilit() << ")\t" <<
                 "s(" << get_streng() << ")\t";
    if(life)
        cout << "alive";
    else
        cout << "died";
    cout << endl;
}
void Goblin::print(){
    cout << goblin_s << endl;
    Card::print();
}
void Archer::print(){
    cout << archer_s << endl;
    Card::print();
}
void Giant::print(){
    cout << giant_s << endl;
    Card::print();
}
void Dragon::print(){
    cout << dragon_s << endl;
    Card::print();
}
void Witch::print(){
    cout << witch_s << endl;
    Card::print();
}
void Ghost::print(){
    cout << ghost_s << endl;
    Card::print();
}