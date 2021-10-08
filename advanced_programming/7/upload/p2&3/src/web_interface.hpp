#ifndef WEBINTFS_H
#define WEBINTFS_H

#include "implementation.hpp"
#include "../server/server.hpp"

#define PORTNUM 5000
#define LOGIN   "static/login.html"
#define TLOGIN  "static/trylogin.html"
#define SIGNUP  "static/signup.html"
#define TSIGNUP "static/trysignup.html"
#define NFOUND  "static/404.html"
#define HOME    "static/home.html"
#define NEWJEEK "static/newjeek.html"

class WebInterface{
public:
    void handleLogin();
    void handleSignup();
    void handleUserpage();
    void handleShowJeek();
    void handleNewJeek();
    void run(int port);
    Sessions sessions;
private:
    Server* server;
};

#endif