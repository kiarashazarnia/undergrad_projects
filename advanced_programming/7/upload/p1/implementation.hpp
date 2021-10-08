#ifndef IMPLEMENTATION_H
#define IMPLEMENTATION_H
#include "common.hpp"
#include "message.hpp"
#include "user.hpp"

class Implementation{
public:
    Implementation() : user(NULL), jeek(NULL) {}
    void check_userlog();
    void check_jeeking();
    bool logedin();
    void signup(string username, string user_display_name, string password);
    void login(string username, string password);
    void logout(void);
    void newJeek(void);
    void text(string text);
    void tag(string hashtag);
    void mention(string username);
    void publish(void);
    void abortJeek(void);
    vector<Jeek> search(string searching);
    vector<Jeek> searchUser(string userDisplayName);
    vector<Jeek> searchTag(string hashtag);
    void comment(string jeekId, string comment_text);
    void reply(string id, string reply_text);
    void replyOnComment(string comment_id, string reply_text);
    void replyOnReply(string reply_id, string reply_text);
    void rejeek(string jeek_id);
    void showJeek(string jeek_id);
    void showComment(string comment_id);
    void showReply(string reply_id);
    void like(string jeek_id);
    void dislike(string jeek_id);
    void follow(string userDisplayName);
    void unfollow(string userDisplayName);
    vector<string> notifications(void);
private:
    Jeek* jeek;
    Jeeks jeeks;
    Comments comments;
    Replies replies;
    User* user;
    Users users;
};
#endif