#ifndef WEBHLR_H
#define WEBHLR_H
#include "common.hpp"
#include "web_interface.hpp"

class WebInterface;

class WebHlr : public RequestHandler{
public:
    WebHlr(WebInterface* _web);
    void setSession(string sid);
protected:
    WebInterface* web;
    Implementation* session;
};

class LoginHlr:  public WebHlr {
public:
    LoginHlr(WebInterface* interface);
    Response *callback(Request *req);
};

class SignupHlr: public WebHlr {
public:
    SignupHlr(WebInterface* interface);
    Response *callback(Request *req);    
};

class UserWebHlr : public WebHlr{
public:
    UserWebHlr(WebInterface* _web);
    Response *callback(Request *req);
    virtual Response *callbackAfterSet(Request *req) = 0;    
};

class UserpageHlr : public UserWebHlr{
public:
    UserpageHlr(WebInterface* interface);
    Response *callbackAfterSet(Request *req);    
};

class SearchHlr : public UserWebHlr{
public:
    SearchHlr(WebInterface* interface);;
    Response *callbackAfterSet(Request *req);    
};

class LogoutHlr : public UserWebHlr{
public:
    LogoutHlr(WebInterface* interface);
    Response *callbackAfterSet(Request *req);        
};

class NewjeekHlr : public UserWebHlr{
public:
    NewjeekHlr(WebInterface* interface);
    Response *callbackAfterSet(Request *req);        
};

class AbortJeekHlr : public UserWebHlr{
public:
    AbortJeekHlr(WebInterface* interface);
    Response *callbackAfterSet(Request *req);        
};

class FunctionHlr : public UserWebHlr{
public:
    FunctionHlr(WebInterface* interface);
    Response* callbackAfterSet(Request *req);
private:
    Response* responseFunction(string func, string jeekId);
};

#endif