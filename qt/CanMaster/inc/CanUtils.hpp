#pragma once

namespace canutils{
#ifdef __cplusplus
extern "C"{
#endif
    int canGen(int argc, char **argv, int* pR);
    int canDump(int argc, char **argv);
    int canPlayer(int argc, char **argv);
    int canSend(int argc, char **argv);
    int canSniffer(int argc, char **argv, int *pR, void **pSniffBuf);
#ifdef __cplusplus
}
#endif
}
