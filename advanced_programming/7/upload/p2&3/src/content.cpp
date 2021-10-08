// This code is very very DIRTY and I'm sorry about that :(

#include "content.hpp"

Response* jeekDetailPage(Jeek* jeek){
    Response* res = new Response;
    res -> setHeader("Content-Type", "text/html");
    string body;
    body += JEEKHEAD;
    body += FUNCFORM;
    body += TILJEEKID;
    body += jeek -> getId();
    body += "</h2><p><b>";
    body += jeek -> getWriterUsername();
    body += UNTILTEXT;
    body += jeek -> getText();
    body += "</big></p><p>";
    body += "</p><p>";
    body += vectorToString(jeek -> getMentionedIds(), MENTION_MARK);
    body += "</p><p>";
    body += vectorToString(jeek -> getHashtags(), HASHTAG_MARK);
    body += "</p><p style=\"color:red\"><i>#likescore " + to_string(jeek -> likeScore());
    body += RESTOFPAGE;
    res -> setBody(body);
    return res;
}

string jeekToHTML(Jeek jeek){
    string content;
    content += "<p style=\"background-color: darkgreen; color: white\"><b style=\"color: lightgreen;\"></br>@";
    content += jeek.getWriterUsername();
    content += "</b><small> jeeked on </small>";
    content += jeek.getId();
    content += " : </br>";
    content += "<big>" + jeek.getText() + "</big>";
    content += "</br>";
    content += vectorToString(jeek.getHashtags(), HASHTAG_MARK);
    content += "<br></br></p>";
    return content;
}
string jeeksToHTML(vector<Jeek> jeeks){
    string str;
    for(unsigned i = jeeks.size(); i > 0; i--)
        str += jeekToHTML(jeeks.at(i-1));
    return str;
}
Response* resultPage(string username, vector<Jeek> jeeks){
    Response *res = new Response;
    res -> setHeader("Content-Type", "text/html");
    string body;
    body += FUNCFORM;
    body += RESHEAD;
    body += TILUSERNAME;
    body += username;
    body += AFTUSERNAME;
    body += jeeksToHTML(jeeks);
    body += ENDRES;
    res -> setBody(body);
    return res;
}
