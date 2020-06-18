#include <iostream>
#include <chrono>
#include <unistd.h>
#include <numeric>
#include <vector>

class Timer {
    using clock_t = std::chrono::steady_clock;
    using timepoint_t = clock_t::time_point;
    using duration_t = clock_t::duration;

public:
    Timer() {
        begin_period = clock_t::now();
        ticking = true;

    }

    void pause() {
        add_time_period();
        ticking = false;
    }

    void resume() {
        begin_period = clock_t::now();
        ticking = true;
    }

    ~Timer() noexcept {
        add_time_period();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(result).count() << std::endl;
    }

private:
    timepoint_t begin_period;
    duration_t result;
    bool ticking;

    void add_time_period() {
        if (ticking) {
            result += (clock_t::now() - begin_period);
        }
    }
};

int main() {
    Timer tm;
    usleep(100000);
    tm.pause();
    tm.pause();
    usleep(100000);
    tm.resume();
    usleep(100000);
    return 0;
}