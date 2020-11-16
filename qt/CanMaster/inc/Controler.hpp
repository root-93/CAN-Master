#pragma once
#include "ViewActionData.hpp"

class Controler{
    public:
        Controler(){};
        ~Controler(){};
        void execAction(ViewActionData VAD)const ;
        static void canSniffer();
    private:
        //char** createArgumentTable(vector<string> argV); 
};