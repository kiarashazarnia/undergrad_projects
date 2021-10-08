#include "implementation.hpp"
#include <typeinfo>

Jeeks Implementation::jeeks;
Comments Implementation::comments;
Replies Implementation::replies;
Users Implementation::users;

bool Implementation::logedin(){
    return user != NULL;
}
void Implementation::signup(string username, string user_display_name, string password){
    users.addUser(username, user_display_name, password);
}
void Implementation::login(string username, string password){
    if(user != NULL)
        throw Error("user " + user -> getUsername() + " already logged in");
    user = users.login(username, password);
}
void Implementation::logout(void){
    user = NULL;
}
Jeek* Implementation::newJeek(void){
    return user -> newJeek(jeeks);
}
void Implementation::text(string text){
    user -> writeText(text);
}
void Implementation::tag(string hashtag){
    user -> addHashtag(hashtag);
}
void Implementation::mention(string user_id){
    user -> addMention(user_id);     
}
void Implementation::publish(void){
    user -> notifyNewJeek(users);
    user -> endJeek();
}
void Implementation::check_userlog(){    
    if(user == NULL)
        throw Error("no logedin user");
}
void Implementation::check_jeeking(){
    if(!user -> jeeking())
        throw Error("no new jeek");
}
void Implementation::abortJeek(void){
    user -> abortJeek(jeeks);
}
vector<Jeek> Implementation::search(string searching){
    if(searching.substr(0,1) == MENTION_MARK)
        return searchUser(searching.substr(1));
    else if(searching.substr(0,1) == HASHTAG_MARK)
        return searchTag(searching.substr(1));
    else 
        throw Error("invalid search");
}
vector<Jeek> Implementation::searchUser(string username){
    if(!users.existUsername(username))
        throw Error("not found");
    User* searching_user = users.findbyUsername(username);
    return searching_user -> findjeeks(jeeks);
}
vector<Jeek> Implementation::searchTag(string hashtag){
    return jeeks.searchHashtag(hashtag);
}
void Implementation::comment(string jeek_id, string comment_text){
    user -> commentOn(jeek_id, comment_text, jeeks, comments);
    Jeek* commenting_jeek = jeeks.searchId(jeek_id);
    user -> notifyComment(jeek_id, commenting_jeek -> getWriter());
}
void Implementation::reply(string id, string reply_text){
    if(id.substr(0,5) == "Reply")
        return replyOnReply(id, reply_text);
    else if(id.substr(0,7) == "Comment")
        return replyOnComment(id, reply_text);
    else 
        throw Error("invalid id to reply");
}
void Implementation::replyOnComment(string comment_id, string reply_text){
    user -> replyOnComment(comment_id, reply_text, comments, replies);
    user -> notifyReply(comment_id, comments.searchId(comment_id) -> getWriter());
}
void Implementation::replyOnReply(string reply_id, string reply_text){
    user -> replyOnReply(reply_id, reply_text, replies);
    user -> notifyReply(reply_id, comments.searchId(reply_id) -> getWriter());
}
void Implementation::rejeek(string jeek_id){
    user -> rejeekOn(jeek_id, jeeks);
}
Jeek* Implementation::findJeek(string jeek_id){
    return jeeks.searchId(jeek_id);
}
Comment* Implementation::findComment(string comment_id){
    return comments.searchId(comment_id);
}
Reply* Implementation::findReply(string reply_id){
    return replies.searchId(reply_id);
}
void Implementation::like(string jeek_id){
    Jeek* jeek = jeeks.searchId(jeek_id);
    jeek -> likedby(user -> getUsername());
    string notif = user -> getUsername() + " liked " + jeek_id;
    users.notify(jeek -> getWriterUsername(), notif);
}
void Implementation::dislike(string jeek_id){
    Jeek* jeek = jeeks.searchId(jeek_id);
    jeek -> hatedby(user -> getUsername());
    string notif = user -> getUsername() + " disliked " + jeek_id;
    users.notify(jeek -> getWriterUsername(), notif);
}
void Implementation::follow(string username){
    User* following = users.findbyUsername(username);
    user -> follow(following);
}
void Implementation::unfollow(string username){
    User* unfollowing = users.findbyUsername(username);
    user -> unfollow(unfollowing);
}
vector<string> Implementation::notifications(void){
    return user -> getNotifications();
}
string Sessions::genId(){
    return "Session" + to_string(size());
}
Jeek* Implementation::newJeek(string _text, string _tags, string _mentions){
    vector<string> tags = split(_tags);
    vector<string> mentions = split(_mentions);
    Jeek* jeek = newJeek();
    text(_text);
    for(unsigned i = 0; i < tags.size(); i++){
        tag(tags.at(i));
    }
    for(unsigned i = 0; i < mentions.size(); i++){
        mention(mentions.at(i));
    }
    publish();
    return jeek;
}
