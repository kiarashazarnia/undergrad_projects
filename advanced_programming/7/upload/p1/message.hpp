#ifndef MESSAGE_H
#define MESSAGE_H
#include "common.hpp"
#include "user.hpp"

class User;
class Users;
class Comment;

class Message : public IData{
public:
    string getWriterName();
    string getWriterUsername();
    void setWriter(User* _writer);
    User* getWriter();
    virtual void addText(string _text);
    Message(string id, User* user, string text); 
    Message(){}
    void print();
    int commentNum();
    void addComment(string comment_id);
    vector<Comment> getComments();  
protected:
    string text;
    User* writer;
    IdBank comments;
};

class Jeek : public Message{
public:
    Jeek() : rejeeked_on(NULL){}
    Jeek(string id, User* user, string text); 
    void printDetail();
    void addText(string _text);
    void likedby(string userId);
    void hatedby(string userId);
    int likeScore();
    void addHashtag(string hashtagh);
    void addMention(string mention);
    bool hasTag(string hashtag);
    void rejeekedby(string jeek_id);
    int rejeeksNum();
    void rejeekedOn(Jeek* jeek);
    Jeek* rejeekedOn();
    vector<string> getMentionedIds();
private:
    IdBank hashtags;
    IdBank mentions;
    IdBank likers;
    IdBank haters;
    IdBank rejeeks;
    Jeek* rejeeked_on;
};


class Reply;
class Replies;
class Repliable : public Message{
public:
    void addReply(string replyId);
    vector<Reply> getReplies(Replies& replies);
    void printDetail();
private:
    IdBank replyIds;
};

class Comment : public Repliable{
public:
    Comment(){}
    Comment(User* user, string text); 
};

class Reply : public Repliable{
public:
    Reply(){}
    Reply(User* user, string text, string replied_id); 
    void setRepliedId(string replied_id);
private:
    string replied_id;
};

class Jeeks : public DataBase<Jeek>{
public:
    vector<Jeek> searchHashtag(string hashtag);
    string genId();
private: 
};

class Comments : public DataBase<Comment>{
public:
    string genId();
private:
};

class Replies : public DataBase<Reply>{
public:
    string genId();
private:
};

void println(string s);
#endif
