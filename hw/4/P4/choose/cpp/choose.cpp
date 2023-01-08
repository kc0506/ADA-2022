#include "choose.h"

/*
Feel free to use global variables.
However, if you want to write your code more "correctly",
you can search for the keyword "anonymous namespace", a helpful tool in C++.
*/

// this is an example usage
void schedule(int N) {
    int endtime[3];
    if (compare_task(1, 2) <= 0) {
        endtime[1] = assign_task(1, 1);
        endtime[2] = assign_task(2, 2);
    }
    else {
        endtime[2] = assign_task(2, 1);
        endtime[1] = assign_task(1, 2);
    }
}

