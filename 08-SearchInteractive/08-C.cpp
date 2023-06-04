#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>

std::vector<std::pair<int, int>> schedule;   // (pace, time)
std::vector<std::pair<int, int>> trainstops; // (time, distance)

int L, N;
int totalTime = 0;
int totalDistance = 0;

// Ternary search function.
double f(double offset) {
    std::set<double> points;
    for (auto p : trainstops) {
        int time = p.first;
        if (time >= offset)
            points.insert(time);
        if (time + offset <= totalTime)
            points.insert(time + offset);
    }

    double minDistance = 1e7;
    for (auto time : points) {
        int segment = 0;
        while (trainstops[segment + 1].first < time)
            segment++;

        double distance1 = trainstops[segment].second;
        if (schedule[segment].first > 0) {
            double timeInSegment = time - trainstops[segment].first;
            distance1 += timeInSegment * schedule[segment].first;
        }

        int segment2 = 0;
        while (trainstops[segment2 + 1].first < time - offset)
            segment2++;

        double distance2 = trainstops[segment2].second;
        if (schedule[segment2].first > 0) {
            double timeInSegment = time - offset - trainstops[segment2].first;
            distance2 += timeInSegment * schedule[segment2].first;
        }

        double distance = std::abs(distance1 - distance2);
        minDistance = std::min(minDistance, distance);
    }

    return std::fabs(minDistance - L);
}

double minimize(double l, double r, double eps) {
    while (r - l > eps) {
        double x1 = l + (r - l) / 3.0;
        double x2 = l + 2.0 * (r - l) / 3.0;
        if (f(x1) > f(x2))
            l = x1;
        else
            r = x2;
    }
    return l;
}

int main() {
    std::cin >> L >> N;
    trainstops.push_back({0, 0});

    for (int i = 0; i < N; i++) {
        int T, v;
        std::cin >> T >> v;

        totalTime += T;
        totalDistance += v * T;
        trainstops.push_back({totalTime, totalDistance});
        schedule.push_back({v, T});
    }

    double ans = (totalDistance < L) ? totalTime : minimize(0, totalTime, 1e-4);
    std::cout << std::fixed << std::setprecision(3) << ans << std::endl;
}
