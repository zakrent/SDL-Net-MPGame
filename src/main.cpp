#include <iostream>
#include "Program.h"

int main() {
    Program program;
    program.startMainLoop(true, true, "127.0.0.1", 2000);
    return 0;
}