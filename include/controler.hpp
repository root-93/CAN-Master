#pragma once
#include "viewactiondata.hpp"

class Controler{
    public:
        Controler(){};
        ~Controler(){};
        void execAction(ViewActionData VAD)const ;

    private:
        //char** createArgumentTable(vector<string> argV); 
};