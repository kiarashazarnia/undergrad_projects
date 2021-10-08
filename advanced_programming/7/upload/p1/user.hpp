#ifndef USER_H
#define USER_H
#include <stack>
#include "common.hpp"
#include "message.hpp"

class Users;
class Jeek;
class Jeeks;
class Reply;
class Replies;
class Comments;

class Person{
public:
    void setUsername(string _username);
    void setPassword(string _password);
    void setDisplayName(string _display_name);
    string getUsername();
    string getDisplayName();
    bool isPassword(string _pass);
    bool isDisplayName(string _name);
    bool isUsername(string _user);
    void addNotif(string notif);
    string nextNotif();
    vector<string> getNotifications();
protected:
    string username;
    string password;
    string display_name;
    stack<string> notifications;
};

class User : public Person, public IData{
public:
    User(){}
    User(string user, string display, string pass);
    void follow(User* following);
    void followedby(User* follower);
    void unfollow(User* unfollowing);
    void unfollowedby(User* unfollower);
    int followersNum();
    Jeek* newJeek(Jeeks& jeeks);
    void writeText(string text);
    void addHashtag(string hashtag);
    void addMention(string mentioned);
    void abortJeek(Jeeks& jeeks);
    void notifyNewJeek(Users& users);
    void notifyMentioned(Users& users);
    void notifyFollowers(Users& users);
    void notifyComment(string jeek_id, User* notifying);
    void notifyReply(string replied_id, User* notifying);
    void notifyRejeeked();
    void replyOnComment(string comment_id, string reply_text, Comments& comments, Replies& replies);
    void replyOnReply(string comment_id, string reply_text, Replies& replies);
    void rejeekOn(string jeek_id, Jeeks& jeeks);
    bool jeeking();
    void endJeek();
    vector<Jeek> findjeeks(Jeeks& jeeks);
    void commentOn(string jeek_id, string comment_text, Jeeks& jeeks, Comments& comments);

private:
    IdBank followings;
    IdBank followers;
    Jeek* jeek;
};

class Users : public DataBase<User>{
public:
    User* findbyUsername(string display_name);
    bool existUsername(string username);
    void notify(string username, string notif);
    User* addUser(string username, string user_display_name, string password);
    User* login(string username, string password);
    string genId();
private:

};
#endif