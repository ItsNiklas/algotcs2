#include <iostream>
#include <queue>
#include <string>

int main() {
    // Initialize cookie holding area.
    // Implemented as a double priority queue.
    std::priority_queue<int, std::vector<int>, std::greater<>> qmin;
    std::priority_queue<int, std::vector<int>, std::less<>> qmax;

    std::string input;
    int val;

    while (std::cin >> input) {
        if (input == "#") {
            // Return 2/3 position. This is always qmin.top() by queue design.
            std::cout << qmin.top() << std::endl, qmin.pop();

            // Rebalance.
            if (qmin.size() * 2 != qmax.size())
                qmin.push(qmax.top()), qmax.pop();

        } else {
            // Insert cookie into correct queue.
            val = std::stol(input);
            if (qmin.size() == 0)
                qmin.push(val);
            else
                val > qmin.top() ? qmin.push(val) : qmax.push(val);

            // Rebalance.
            if (qmin.size() * 2 > qmax.size() + 2)
                qmax.push(qmin.top()), qmin.pop();
            else if (qmin.size() * 2 < qmax.size())
                qmin.push(qmax.top()), qmax.pop();
        }
    }
}