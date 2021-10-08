#include "text_interface.hpp"

int main(){
    TextInterface interface;
    while(true)
    {
        try{
            interface.run();
        }
        catch(Error e){
            e.print();
        }
        interface.flushCommand();
    }
    return 0;
}