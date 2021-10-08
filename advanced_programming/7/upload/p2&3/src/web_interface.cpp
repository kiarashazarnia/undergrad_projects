#include "web_interface.hpp"
#include "webhandler.hpp"

void WebInterface::run(int port){
    try{
        server = new Server(port, NFOUND);
        handleLogin();
        handleSignup();
        handleUserpage();
        handleNewJeek();
        handleShowJeek();
        server -> run();
    }catch (Server::Exception e) {
        cerr << e.getMessage() << endl;
    }
}

void WebInterface::handleSignup(){
    server -> get("/signup", new ShowPage(SIGNUP));
    server -> get("/trysignup", new ShowPage(TSIGNUP));
    server -> post("/signup", new SignupHlr(this));
    server -> post("/trysignup", new SignupHlr(this));
}

void WebInterface::handleLogin(){
    server -> get("/login", new ShowPage(LOGIN));
    server -> get("/trylogin", new ShowPage(TLOGIN));
    server -> post("/login", new LoginHlr(this));
    server -> post("/trylogin", new LoginHlr(this));
}

void WebInterface::handleUserpage(){
    server -> get("/userp", new UserpageHlr(this));
    server -> get("/logout", new LogoutHlr(this));
    server -> post("/search", new SearchHlr(this));
}

void WebInterface::handleShowJeek(){
    server -> post("/function", new FunctionHlr(this));
}

void WebInterface::handleNewJeek(){
    server -> get("/newjeek", new ShowPage(NEWJEEK));
    server -> post("/publish", new NewjeekHlr(this));
    server -> get("/abort", new AbortJeekHlr(this));
}