#include "webhandler.hpp"
#include "content.hpp"

WebHlr::WebHlr(WebInterface* _web) : session(NULL) { web = _web;}
LoginHlr::LoginHlr(WebInterface* _web) : WebHlr(_web) {}
SignupHlr::SignupHlr(WebInterface* _web) : WebHlr(_web) {}
UserWebHlr::UserWebHlr(WebInterface* _web) : WebHlr(_web) {}
SearchHlr::SearchHlr(WebInterface* _web) : UserWebHlr(_web) {}
UserpageHlr::UserpageHlr(WebInterface* _web) : UserWebHlr(_web) {}
LogoutHlr::LogoutHlr(WebInterface* _web) : UserWebHlr(_web) {}
NewjeekHlr::NewjeekHlr(WebInterface* _web) : UserWebHlr(_web) {}
AbortJeekHlr::AbortJeekHlr(WebInterface* _web) : UserWebHlr(_web) {}
FunctionHlr::FunctionHlr(WebInterface* _web) : UserWebHlr(_web) {}

void WebHlr::setSession(string sid){
    session = web -> sessions.searchId(sid);
}

Response* UserWebHlr::callback(Request *req){
    string sid = req -> getSessionId();
    try{
        setSession(sid);
    }catch(Error e){
        e.print();
        return Response::redirect("/login");
    }
    return callbackAfterSet(req);
}

Response* LoginHlr::callback(Request *req){
    string username = req -> getBodyParam("username");
    string password = req -> getBodyParam("password");
    if(username.empty() || username.empty())
        return Response::redirect("/login");
    session = web -> sessions.newData();
    try{
        session -> login(username, password);
        Response* res = Response::redirect("/userp");
        res -> setSessionId(session -> getId());
        return res;
    }catch(Error e){
        e.print();
        web -> sessions.pop_back();
        return Response::redirect("/trylogin");
    }
}

Response* SignupHlr::callback(Request *req){
    string username = req -> getBodyParam("username");
    string displayname = req -> getBodyParam("displayname");
    string password = req -> getBodyParam("password");
    Response *res;
    if(username.empty() || password.empty() || displayname.empty())
        res = Response::redirect("/signup");
    else try{
        session -> signup(username, displayname, password);
        res = Response::redirect("/login");
    }catch(Error e){
        res = Response::redirect("/trysignup");
    }
    return res;
}

Response* FunctionHlr::callbackAfterSet(Request* req){
    string func = req -> getBodyParam("function");
    string jeekId = req -> getBodyParam("jeekId");
    Response* res;
    try{
        res = responseFunction(func, jeekId);
    }
    catch(Error e){
        e.print();
        res = Response::redirect("/userp");
    }
    res -> setSessionId(session -> getId());
    return res;
}

Response* FunctionHlr::responseFunction(string func, string jeekId){
    if(func == "showJeek"){
        Jeek* jeek = session -> findJeek(jeekId);
        return jeekDetailPage(jeek);
    }
    else if(func == "like"){
        session -> like(jeekId);

    }
    else if(func == "dislike"){
        session -> dislike(jeekId);
    }
    return Response::redirect("/userp");
}

Response* UserpageHlr::callbackAfterSet(Request *req){
    string username = session -> getUsername();
    Response* res;
    try{
        vector<Jeek> jeeks = session -> search(MENTION_MARK + username); 
        res = resultPage(username, jeeks);
    }catch(Error e){
        e.print();
        res = Response::redirect("/userp");
    }
    res -> setSessionId(session -> getId());
    return res;
}

Response* SearchHlr::callbackAfterSet(Request *req){
    string username = session -> getUsername();
    string searching = req -> getBodyParam("search");
    Response* res;
    try{
        vector<Jeek> jeeks = session -> search(searching);
        res = resultPage(username, jeeks);
    }catch(Error e){
        e.print();
        res = Response::redirect("/userp");
    }
    res -> setSessionId(session -> getId());
    return res;
}

Response* LogoutHlr::callbackAfterSet(Request *req){
    try{
        web -> sessions.remove(req -> getSessionId());
    }
    catch(Error e){
        e.print();
    }
    Response* res = Response::redirect("/login");
    res -> setSessionId("");
    return res;
}

Response* NewjeekHlr::callbackAfterSet(Request *req){
    string text = req -> getBodyParam("text");
    string tags = req -> getBodyParam("hashtags");
    string mentions = req -> getBodyParam("mentions");
    Response* res;
    try{
        Jeek* jeek = session -> newJeek(text, tags, mentions);
        string jeekid = jeek -> getId();
    }catch(Error e){
        e.print();
    }
    res = Response::redirect("/userp");
    res -> setSessionId(session -> getId());
    return res;
}

Response* AbortJeekHlr::callbackAfterSet(Request *req){
    Response* res;
    res = Response::redirect("/userp");
    res -> setSessionId(session -> getId());
    return res;
}