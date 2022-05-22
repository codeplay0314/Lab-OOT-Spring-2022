#include "draw.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    freopen("test_result.txt", "w", stdout);
    run(argc, argv);
    fclose(stdout);
    fprintf(stderr, "OK");
    return 0;
}
