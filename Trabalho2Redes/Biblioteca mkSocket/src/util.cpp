#include "../headers/util.h"

void checkOperation(int result, string errorMsg) {
    if(result < 0) {
        cerr << errorMsg << endl;
        exit(EXIT_FAILURE);
    }
}