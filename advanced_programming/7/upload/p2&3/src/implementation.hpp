#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H
#include "common.hpp"
#include "message.hpp"
#include "user.hpp"

class Implementation : public IData{
public:
    Implementation() : user(NULL){}
    void check_userlog();
    void check_jeeking();
    bool logedin();
    void signup(string username, string user_display_name, string password);
    void login(string username, string password);
    void logout(void);
    Jeek* newJeek(void);
    void text(string text);
    void tag(string hashtag);
    void mention(string username);
    void publish(void);
    void abortJeek(void);
    Jeek* newJeek(string text, string tags, string mentions);
    vector<Jeek> search(string searching);
    vector<Jeek> searchUser(string userDisplayName);
    vector<Jeek> searchTag(string hashtag);
    void comment(string jeekId, string comment_text);
    void reply(string id, string reply_text);
    void replyOnComment(string comment_id, string reply_text);
    void replyOnReply(string reply_id, string reply_text);
    void rejeek(string jeek_id);
    Jeek* findJeek(string jeek_id);
    Comment* findComment(string comment_id);
    Reply* findReply(string reply_id);
    void like(string jeek_id);
    void dislike(string jeek_id);
    void follow(string userDisplayName);
    void unfollow(string userDisplayName);
    vector<string> notifications(void);
    string getUsername() {return user -> getUsername();}
private:
    User* user;
    static Jeeks jeeks;
    static Comments comments;
    static Replies replies;
    static Users users;
};

class Sessions : public DataBase<Implementation>{
public:
    string genId();
};

#endif