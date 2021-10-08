#include "message.hpp"

void Message::addText(string _text){
    text += _text;
}
void Jeek::printDetail(){
    println(getWriterName());
    println(text);
    hashtags.printby(HASHTAG_MARK);
    mentions.printby(MENTION_MARK);
    println("Likes\t" + to_string(likeScore()));
    println("Rejeeks\t" + to_string(rejeeksNum()));
    println("Comments:");
    comments.print();
}
void Repliable::printDetail(){
    println(getWriterName());
    println(text);
    println("Replies:");
    replyIds.print();    
}
void Jeek::addText(string _text){
    if(_text.size() > JEEKSIZE)
        throw Error("jeek out of size");
    text += _text;
}
void Jeek::addHashtag(string hashtag){
    hashtags.add(hashtag);
}
void Jeek::addMention(string mention){
    mentions.add(mention);
}
string Message::getWriterName(){
    return writer -> getDisplayName();
}
void Reply::setRepliedId(string _replied_id){
    replied_id = _replied_id;
}
bool Jeek::hasTag(string hashtag){
    return hashtags.have(hashtag);
}
void Message::print(){
    println(id + " " + getWriterName());
    println(text);
}
Jeek::Jeek(string id, User* user, string text) : Message(id, user, text){
    rejeeked_on = NULL;
}
Comment::Comment(User* user, string text){
    setWriter(user);
    addText(text);
}
Reply::Reply(User* user, string text, string replied_id){
    setWriter(user);
    addText(text);
    setRepliedId(replied_id);
}
int Jeek::likeScore(){
    return likers.size() - haters.size();
}
void Jeek::likedby(string userId){
    if(haters.have(userId))
        haters.remove(userId);
    else
        likers.add(userId);
}
void Jeek::hatedby(string userId){
    if(likers.have(userId))
        likers.remove(userId);
    else
        haters.add(userId);
}
void Jeek::rejeekedby(string jeek_id){
    rejeeks.add(jeek_id);
}
int Jeek::rejeeksNum(){
    return rejeeks.size();
}
Message::Message(string id, User* user, string text){
    setId(id);
    setWriter(user);
    addText(text);
}
vector<string> Jeek::getMentionedIds(){
    vector<string> list;
    for(unsigned i = 0; i < mentions.size(); i++)
        list.push_back(mentions.IDat(i));
    return list;
}
vector<Jeek> Jeeks::searchHashtag(string hashtag){
    vector<Jeek> jeeks;
    for(int i = 0; i < size(); i++){
        if(at(i) -> hasTag(hashtag))
            jeeks.push_back(*at(i));
        }
    return jeeks;
}
void Message::setWriter(User* _writer){
    writer = _writer;
}
User* Message::getWriter(){
    return writer;
}
void Message::addComment(string comment_id){
    comments.add(comment_id);
}
void Repliable::addReply(string reply_id){
    replyIds.add(reply_id);
}
vector<Reply> Repliable::getReplies(Replies& replies){
    vector<Reply> myreplies;
    for(unsigned i = 0; i < replyIds.size(); i++)
        myreplies.push_back(*replies.searchId(replyIds.at(i)));
    return myreplies;
}
void Jeek::rejeekedOn(Jeek* jeek){
    rejeeked_on = jeek;
}
Jeek* Jeek::rejeekedOn(){
    return rejeeked_on;
}


string Jeeks::genId(){
    string id = "Jeek";
    id += to_string(size());
    return id;
}

string Comments::genId(){
    string id = "Comment";
    id += to_string(size());
    return id;
}

string Replies::genId(){
    string id = "Reply";
    id += to_string(size());
    return id;
}
string Message::getWriterUsername(){
    return writer -> getUsername();
}