#include <algorithm>
#include <vector>

#include "choose.h";

void schedule(int N) {
    std::vector<int> tasks(N);
    for (int i = 0; i < N; i++)
        tasks[i] = i + 1;

    std::sort(tasks.begin(), tasks.end(), [](int &a, int &b) {
        return compare_task(a, b) == 1;
    });

    int cur1 = 0, cur2 = 0;
    for (int i = 0; i < N; i++) {
        if (cur1 <= cur2) {
            // printf("%d\n", cur1);
            cur1 = assign_task(1, tasks[i]);
        } else {
            // printf("%d\n", cur2);
            cur2 = assign_task(2, tasks[i]);
        }
    }
}