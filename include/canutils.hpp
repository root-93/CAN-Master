#ifndef CANUTILS_H
#define CANUTILS_H

#ifdef C_PLUS_PLUS
extern "C"{
#endif

    int canGen(int argc, char **argv);
    int canDump(int argc, char **argv);
    int canPlayer(int argc, char **argv);
    int canSend(int argc, char **argv);
    int canSniffer(int argc, char **argv);

#ifdef C_PLUS_PLUS
}
#endif

#endif //CANUTILS_H