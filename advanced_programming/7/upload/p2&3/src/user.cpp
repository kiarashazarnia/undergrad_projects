#include "user.hpp"   
User::User(string user, string display, string pass){
    username = user;
    display_name = display;
    password = pass;
}
void Person::setUsername(string _username){
    username = _username;
}
void Person::setPassword(string _password){
    password = _password;
}
void Person::setDisplayName(string _display_name){
    display_name = _display_name;
}
string Person::getUsername(){
    return username;
}
bool Person::isPassword(string _pass){
    return password == _pass;
}
bool Person::isUsername(string _user){
    return username == _user;
}
string Person::getDisplayName(){
    return display_name;
}
bool Person::isDisplayName(string _name){
    return display_name == _name;
}
// User* Users::findbyDisplayName(string display_name){
//     for(unsigned i = 0; i < size(); i++)
//         if(at(i) -> isDisplayName(display_name))
//             return at(i);
//     throw Error("user displayname: " + display_name + " not found");
// }
User* Users::findbyUsername(string username){
    for(unsigned i = 0; i < size(); i++)
        if(at(i) -> isUsername(username))
            return at(i);
    throw Error("username: " + username + " not found");
}
// bool Users::existDisplayName(string display_name){
//     for(unsigned i = 0; i < size(); i++)
//         if(at(i) -> isDisplayName(display_name))
//             return true;
//     return false;
// }
bool Users::existUsername(string username){
    for(unsigned i = 0; i < size(); i++)
        if(at(i) -> isUsername(username))
            return true;
    return false;
}
void User::follow(User* following){
    if(followings.have(following -> getUsername()))
        throw Error(getUsername() + " already follows " + following -> getUsername());
    followings.add(following -> getUsername());
    following -> followedby(this);
}
void User::followedby(User* follower){
    if(followers.have(follower -> getUsername()))
        throw Error(getUsername() + " is already followed by " + follower -> getUsername());
    followers.add(this -> getUsername());
}       
void User::unfollow(User* unfollowing){
    if(!followings.have(unfollowing -> getUsername()))
        throw Error(getUsername() + " does not follow " + unfollowing -> getUsername());
    followings.remove(unfollowing -> getUsername());
    unfollowing -> unfollowedby(this);
}
void User::unfollowedby(User* follower){
    if(!followers.have(follower -> getUsername()))
        throw Error(getUsername() + " is not followed by " + follower -> getUsername());
    followers.remove(this -> getUsername());
}
int User::followersNum(){
    return followers.size();
}
void Person::addNotif(string notif){
    notifications.push(notif);
}
string Person::nextNotif(){
    string notif = notifications.top();
    notifications.pop();
    return notif;
}
void Users::notify(string username, string notif){
    User* notifying = findbyUsername(username);
    notifying -> addNotif(notif);
}
Jeek* User::newJeek(Jeeks& jeeks){
    jeek = jeeks.newData();
    jeek -> rejeekedOn(NULL);
    jeek -> setWriter(this);
    return jeek;
}
void User::writeText(string text){
    jeek -> addText(text);
}
void User::addHashtag(string hashtag){
    jeek -> addHashtag(hashtag);
}
void User::addMention(string mentioned){
    jeek -> addMention(mentioned);
}
void User::endJeek(){
    jeek = NULL;
}
void User::abortJeek(Jeeks& jeeks){
    jeeks.pop_back();
    jeek = NULL;
}
bool User::jeeking(){
    return jeek != NULL;
}
void User::notifyNewJeek(Users& users){
    notifyFollowers(users);
    notifyMentioned(users);
    notifyRejeeked();
}
void User::notifyRejeeked(){
    Jeek* rejeeked = jeek -> rejeekedOn();
    if(rejeeked == NULL)
        return;
    rejeeked -> rejeekedby(jeek -> getId());
    User* notifying = rejeeked -> getWriter();
    notifying -> addNotif(getUsername() + " rejeeked " + jeek -> getId());
}
void User::notifyMentioned(Users& users){
    vector<string> mentioned_list = jeek -> getMentionedIds();
    string notif = getUsername() + " mentioned you in " + jeek -> getId();
    for(unsigned i = 0; i < mentioned_list.size(); i++)
        users.notify(mentioned_list.at(i), notif);
}
void User::notifyFollowers(Users& users){
    string notif = getUsername() + " jeeked " + jeek -> getId();
    for(unsigned i = 0; i < followersNum(); i++)
        users.notify(followers.IDat(i), notif);    
}
User* Users::addUser(string username, string user_display_name, string password){
    if(existUsername(user_display_name))
        throw Error("current username is already exist, try again.");
    User* user = newData(User(username, user_display_name, password));
    return user;
}
User* Users::login(string username, string password){
    if(!existUsername(username))
        throw Error("incorrect username");
    User* user = findbyUsername(username);
    if(!user -> isPassword(password)){
        user = NULL;
        throw Error("incorrect password");
    } else
        return user;
}
vector<Jeek> User::findjeeks(Jeeks& jeeks){
    vector<Jeek> myjeeks;
    User* jeeker;
    for(int i = 0; i < jeeks.size(); i++){
        jeeker = jeeks.at(i) -> getWriter();
        if(jeeker == this)
            myjeeks.push_back(*jeeks.at(i));
        }
    return myjeeks;
}
void User::commentOn(string jeek_id, string comment_text, Jeeks& jeeks, Comments& comments){
    Jeek* commenting = jeeks.searchId(jeek_id); 
    Comment* comment = comments.newData(Comment(this, comment_text));
    commenting -> addComment(comment -> getId());
}
void User::notifyComment(string jeek_id, User* notifying){
    string notif = getUsername() + " commented on " + jeek_id;
    notifying -> addNotif(notif);
}
void User::notifyReply(string replied_id, User* notifying){
    string notif = getUsername() + " replied " + replied_id;
    notifying -> addNotif(notif);
}
void User::replyOnComment(string comment_id, string reply_text, Comments& comments, Replies& replies){
    Reply* reply = replies.newData(Reply(this, reply_text, comment_id));
    Repliable* repling = comments.searchId(comment_id);
    repling -> addReply(reply -> getId());
}
void User::replyOnReply(string reply_id, string reply_text, Replies& replies){
    Reply* reply = replies.newData(Reply(this, reply_text, reply_id));
    Repliable* repling = replies.searchId(reply_id);
    repling -> addReply(reply -> getId());    
}
void User::rejeekOn(string jeek_id, Jeeks& jeeks){
    jeek = newJeek(jeeks);
    jeek -> addText("Rejeeked:\n");
    jeek -> rejeekedOn(jeeks.searchId(jeek_id));
}
vector<string> Person::getNotifications(){
    vector<string> notifs;
    while(!notifications.empty()){
        notifs.push_back(notifications.top());
        notifications.pop();
    }
    return notifs;
}
string Users::genId(){
    string id = "User";
    id += to_string(size());
    return id;
}