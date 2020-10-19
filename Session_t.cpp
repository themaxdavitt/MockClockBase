/*
    session_t.cpp

    Test the class Session

    * All classes are implemented directly to focus on
      dependency injection and mock objects. In production code,
      all classes would be in separate .hpp and .cpp files.
    * The code uses the C library time.h (ctime). In production
      code, use std::chrono.
*/

#include <ctime>
#include <cassert>
#include <unistd.h>

class Session {
public:
    // constructor
    Session()
        : start_time(std::time(nullptr))
    {}

    // stop the session
    void stop() {
        stop_time = std::time(nullptr);
    }

    // elapsed time of the stopped session in seconds
    std::time_t seconds() {
        return stop_time - start_time;
    }

private:
    std::time_t start_time;
    std::time_t stop_time;
};

int main() {

    // 2-second session
    {
        Session s;
        sleep(2);
        s.stop();
        assert(s.seconds() == 2);
    }

    return 0;
}
