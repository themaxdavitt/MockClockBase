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

class Clock {
public:
    virtual std::time_t start() const = 0;
    virtual std::time_t now() const = 0;
};

class MockClock : public Clock {
public:
    MockClock(std::time_t amount)
        : length(amount) {}

    virtual std::time_t start() const {
        return 0;
    }

    virtual std::time_t now() const {
        return length;
    }
private:
    std::time_t length;
};

// class TenSecondClock : public Clock {
// public:
//     virtual std::time_t start() const {
//         return 0;
//     }
// 
//     virtual std::time_t now() const {
//         return 10;
//     }
// };

// class TenMinuteClock : public Clock {
// public:
//     virtual std::time_t start() const {
//         return 0;
//     }
// 
//     virtual std::time_t now() const {
//         return 10 * 60;
//     }
// };

// class TenHourClock : public Clock {
// public:
//     virtual std::time_t start() const {
//         return 0;
//     }
// 
//     virtual std::time_t now() const {
//         return 10 * 60 * 60;
//     }
// };

class TimeClock : public Clock {
public:
    virtual std::time_t start() const {
        return now();
    }

    virtual std::time_t now() const {
        return std::time(nullptr);
    }
};

class Session {
public:
    // constructor
    Session(const Clock& clock = TimeClock())
        : clock(clock), start_time(clock.start())
    {}

    // stop the session
    void stop() {
        end_time = clock.now();
    }

    // elapsed time of the stopped session in seconds
    std::time_t seconds() {
        return end_time - start_time;
    }

private:
    const Clock& clock;
    std::time_t start_time;
    std::time_t end_time;
};

int main() {

    // 2-second session
    {
        Session s;
        sleep(2);
        s.stop();
        assert(s.seconds() == 2);
    }

    // 10-second session
    {
        MockClock clock(10);
        Session s(clock);
        // ...
        s.stop();
        assert(s.seconds() == 10);
    }

    // 10-second session
    {
        MockClock clock(10 * 60);
        Session s(clock);
        // ...
        s.stop();
        assert(s.seconds() == 10 * 60);
    }

    // 10-hour session
    {
        MockClock clock(10 * 60 * 60);
        Session s(clock);
        // ...
        s.stop();
        assert(s.seconds() == 10 * 60 * 60);
    }

    return 0;
}
