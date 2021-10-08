#include "web_interface.hpp"

int main(int argc, char **argv) {
    WebInterface* web = new WebInterface;
    int port = argc > 1 ? atoi(argv[1]) : PORTNUM;
    web -> run(port);
    return 0;
}