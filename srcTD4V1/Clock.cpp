// In order to compile this code, you'll need to links it against librt.

#include "Clock.h"

namespace benchmark {

// The tv_sec member corresponds to a number of seconds while tv_nsec
// member corresponds to the number of nanoseconds expired in the
// current second.
timespec timespec_delta(const timespec& t1, const timespec& t2) {
    timespec result;

    if ((t2.tv_nsec - t1.tv_nsec) < 0 /* ns */) {
        result.tv_sec = t2.tv_sec - t1.tv_sec - 1;
        result.tv_nsec = 1000000000 /* ns */ + t2.tv_nsec - t1.tv_nsec;
    } else {
        result.tv_sec = t2.tv_sec - t1.tv_sec;
        result.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }

    return result;
}

timespec timespec_add(const timespec& t1, const timespec& t2) {
    timespec result;

    if ((t1.tv_nsec + t2.tv_nsec) > 1000000000 /* ns */) {
        result.tv_sec = t1.tv_sec + t2.tv_sec + 1;
        result.tv_nsec = t1.tv_nsec + t2.tv_nsec - 1000000000 /* ns */;
    } else {
        result.tv_sec = t1.tv_sec + t2.tv_sec;
        result.tv_nsec = t1.tv_nsec + t2.tv_nsec;
    }

    return result;
}

Chrono::Chrono(): stopped(true),
    clock_id(CLOCK_PROCESS_CPUTIME_ID) {

    total_time.tv_sec = 0;
    total_time.tv_nsec = 0;
}

Chrono::Chrono(Clock::Type clock): stopped(true) {
    if (clock == Clock::Thread) {
        clock_id = CLOCK_THREAD_CPUTIME_ID;
    } else {
        clock_id = CLOCK_PROCESS_CPUTIME_ID;
    }

    total_time.tv_sec = 0;
    total_time.tv_nsec = 0;
}

void Chrono::start() throw(std::runtime_error) {
    if (stopped) {
        if (clock_gettime(clock_id, &start_time) != 0) {
            throw std::runtime_error("Error retrieving clock value.");
        }
        stopped = false;
    }
}

void Chrono::stop() throw(std::runtime_error) {
    if (!stopped) {
        timespec _stop;
        if (clock_gettime(clock_id, &_stop) != 0) {
            throw std::runtime_error("Error retrieving clock value.");
        }
        timespec diff = timespec_delta(start_time, _stop);
        total_time = timespec_add(total_time, diff);
        stopped = true;
    }
}

void Chrono::reset() {
    stopped = true;
    total_time.tv_nsec = 0;
    total_time.tv_sec = 0;
}

long Chrono::nsec() const throw (std::logic_error) {
    if (!stopped)
        throw std::logic_error("Can't retrieve the "
            "nanosecond counter while the chronometer is running.");

    return total_time.tv_nsec;
}

long Chrono::sec() const throw (std::logic_error) {
    if (!stopped)
        throw std::logic_error("Can't retrieve the "
            "second counter while the chronometer is running.");

    return total_time.tv_sec;
}
    
timespec timespec_add_sec(const timespec& t1, long time_ns) //prend un timespec et lui ajoute un temps en nano secondes
{	
	timespec t2;
	if (time_ns > 1000000000 /* ns */) 
	{
        t2.tv_sec = time_ns / 1000000000;
        t2.tv_nsec = time_ns - (time_ns / 1000000000) * 1000000000;
        
    } 
    else 
    {
        t2.tv_sec = 0;
        t2.tv_nsec = time_ns;
    }
	return timespec_add(t1, t2);
}

} // namespace benchmark

