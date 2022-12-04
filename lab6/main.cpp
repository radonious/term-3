#include "includes.h"


int main() {

    LoggerTemplate<int> DT;
    *DT.modifyObj() = 3;
    // Return
    return 0;
}
