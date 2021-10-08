#ifndef CONTENT_H
#define CONTENT_H
#include "common.hpp"
#include "../server/server.hpp"
#include "message.hpp"

#define RESHEAD "<!DOCTYPE html><html style=\"background-color: lightblue; text-align: left; border-radius: 3px; margin: auto;\"><header style=\"background-color: white; text-align: center; color: darkgreen;\"><b > Jeek to World! </b></header>"
#define TILUSERNAME "<body><p style=\"color: darkblue;\">Hi "
#define AFTUSERNAME " :) <a href=\"/logout\"> Logout </a></p><p style=\"color: darkred;\"><a href=\"/newjeek\"> New Jeek! <a></p><div class=\"wrap\"><div class=\"search\">      <p style=\"color: darkgreen;\">Easily search by <b>hashtags</b> or <b>username</b> and find all related <big>Jeeks</big>.</p><form action=\"/search\" method=\"post\"><p> <input type=\"text\" name=\"search\" placeholder=\"@username or #hashtag\"><button type=\"submit\"> search </button></p></form></div></div><div><h2>Resaults</h2>"
#define ENDRES "</div></html>"
#define JEEKHEAD "<!DOCTYPE html><html  style=\"background-color: lightgreen; text-align: center; max-width: 300px; border-radius: 3px; margin: auto;\"><header>Jeek to World!</header><body><p></p>"
#define TILJEEKID "<div style=\"color: darkgreen; background-color: lightblue; padding: 1%;\"><h2>"
#define UNTILTEXT " </b> jeeked:</p><p style=\"color:black\"><big>"
#define RESTOFPAGE "</i></p><p><a href=\"/like\">like</a><a href=\"/dislike\">dislike</a></br><a href=\"/newjeek\">rejeek <a></p><p><a href=\"/logout\"> logout </a> </p></div></body></html>"
#define FUNCFORM "<p><form method=\"post\" action=\"/function\"><input name=\"jeekId\" type=\"text\" placeholder=\"jeekId\"></br>Function: </br></b> <input type=\"radio\" name=\"function\" value=\"showJeek\" checked> showJeek detail<br><input type=\"radio\" name=\"function\" value=\"rejeek\"        > Rejeek <br><input type=\"radio\" name=\"function\" value=\"like\"        > Like<br><input type=\"radio\" name=\"function\" value=\"dislike\"        > Disike</br><button type=\"submit\"> Do it! </button></form></p>"

Response* resultPage(string username, vector<Jeek> jeeks);
string vectorToString(vector<string> vec, string label = "");
string jeekToHTML(Jeek jeek);
string jeeksToHTML(vector<Jeek> jeeks);
Response* jeekDetailPage(Jeek* jeek);

#endif