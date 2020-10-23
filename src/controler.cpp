#include "../include/controler.hpp"
#include "../include/canutils.hpp"
#include "../include/viewactiondata.hpp"

using namespace std;


void Controler::execAction(ViewActionData VAD)const {

    if( VAD.cellName == "Candump"){
        char *param0 = const_cast<char *>("canDump");
        char *param1 = const_cast<char *>("vcan0");
        char *pCanDumpArg[] {param0,
                             param1};

        char **ppCanDumpArg = pCanDumpArg;
        [[maybe_unused]] int returnValue = canDump(2, ppCanDumpArg);
    }
    else if (VAD.cellName == "Cangen"){

    }
    else if (VAD.cellName == "Canpalyer"){

    }
    else if (VAD.cellName == "Cansend"){

    }
    else if (VAD.cellName == "Cansniffer"){
        char *param0 = const_cast<char *>("canSniffer");
        char *param1 = const_cast<char *>("vcan0");
        char *pCanDumpArg[] {param0,
                             param1};

        char **ppCanDumpArg = pCanDumpArg;
        [[maybe_unused]] int returnValue = canSniffer(2, ppCanDumpArg);
    }
}

// char** Controler::createArgumentTable(vector<string> argV){
//     //char *param0 = const_cast<char *>(func);
//     //char *param1 = const_cast<char *>(socket);
//     char *pArgT[] {argV};
//     return &pArgT;
// }