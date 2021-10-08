#include "text_interface.hpp"

void TextInterface::run(){
    running_command.giveCommand();
    command_name = running_command.whatCommanded();
    validate_input();
    switch(command_name){
    case CommandName::signup:
        signup();
    break;
    case CommandName::login:
        login();
    break;
    case CommandName::logout:
        implement.check_userlog();
        logout();
    break;
    case CommandName::jeek:
        implement.check_userlog();
        newJeek();
    break;
    case CommandName::text:
        implement.check_jeeking();
        text();
    break;
    case CommandName::tag:
        implement.check_jeeking();
        tag();
    break;
    case CommandName::mention:
        implement.check_jeeking();
        mention();
    break;
    case CommandName::publish:
        implement.check_jeeking();
        publish();
    break;
    case CommandName::abort:
        implement.check_jeeking();
        abortJeek();
    break;
    case CommandName::showJeek:
        showJeek();
    break;
    case CommandName::search:
        search();
    break;
    case CommandName::comment:
        implement.check_userlog();
        comment();
    break;
    case CommandName::reply:
        implement.check_userlog();
        reply();
    break;
    case CommandName::rejeek:
        implement.check_userlog();
        rejeek();
    break;
    case CommandName::showComment:
        showComment();
    break;
    case CommandName::showReply:
        showReply();
    break;
    case CommandName::like:
        implement.check_userlog();
        like();
    break;
    case CommandName::dislike:
        implement.check_userlog();
        dislike();
    break;
    case CommandName::follow:
        implement.check_userlog();
        follow();
    break;
    case CommandName::unfollow:
        implement.check_userlog();
        unfollow();
    break;
    case CommandName::notifications:
        notifications();
    break;
    case CommandName::invalid:
        throw Error("invalid command");
    break;
    }
}

bool multiParameter(CommandName command_name){
    switch(command_name){
    case CommandName::text:
    case CommandName::comment:
    case CommandName::reply:
        return true;
    default:
        return false;
    }
}

void TextInterface::validate_input(){
    if(command_name == CommandName::invalid)
        return;
    input = running_command.split();
    if(multiParameter(command_name) && input.size() > 1)
        return;
    if(input.size() != commands[command_name].param + 1)
        throw Error(commands[command_name].str + " needs " + to_string(commands[command_name].param) + " parameter");
}
void TextInterface::signup(){
    implement.signup(input.at(1), input.at(2), input.at(3));
}
void TextInterface::login(){
    implement.login(input.at(1), input.at(2));
}
void TextInterface::logout(){
    implement.logout();
}
void TextInterface::newJeek(){
    implement.newJeek();
}
string deleteCotation(vector<string> str){
    if(str.at(0).at(0) == '"' && str.at(str.size() - 1).at(str.size() - 1) == '"'){
        str.at(0).erase(0,1);    
        str.at(str.size() - 1).erase(str.at(str.size() - 1).size() - 1 ,1);
    }
}
void TextInterface::text(){
    implement.text(running_command.text());
}
void TextInterface::tag(){
    implement.tag(running_command.text());
}
void TextInterface::mention(){
    implement.mention(input.at(1));
}
void TextInterface::publish(){
    implement.publish();
}
void TextInterface::abortJeek(){
    implement.abortJeek();
}
void TextInterface::search(){
    vector<Jeek> jeeks = implement.search(input.at(1));
    printJeeks(jeeks);
}
void TextInterface::comment(){
    string text = running_command.fromWordNum(2);
    implement.comment(input.at(1), text);
}
void TextInterface::reply(){
    string text = running_command.fromWordNum(2);
    implement.reply(input.at(1), text);
}
void TextInterface::rejeek(){
    implement.rejeek(input.at(1));
}
void TextInterface::showJeek(){
    implement.showJeek(input.at(1));
}
void TextInterface::showComment(){
    implement.showComment(input.at(1));
}
void TextInterface::showReply(){
    implement.showReply(input.at(1));
}
void TextInterface::like(){
    implement.like(input.at(1));
}
void TextInterface::dislike(){
    implement.dislike(input.at(1));
}
void TextInterface::follow(){
    implement.follow(input.at(1));
}
void TextInterface::unfollow(){
    implement.unfollow(input.at(1));
}
void TextInterface::notifications(){
    vector<string> notes = implement.notifications();
    printStrings(notes);
}
void TextInterface::flushCommand(){
    running_command.flush();
}

void printJeeks(vector<Jeek>& jeeks){
    for(int i = 0; i < jeeks.size(); i++){
        jeeks.at(i).print();
    }
}
void printStrings(vector<string>& strings){
    for(int i = 0; i < strings.size(); i++){
        println(strings.at(i));
    }
}