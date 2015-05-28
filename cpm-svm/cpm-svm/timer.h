#ifndef TIMER_HR_H
#define TIMER_HR_H

#ifdef _WIN32

// Windows time query

#include <windows.h>
#undef max // to call std::max

inline long long gettimeus()
{
    static LARGE_INTEGER ClockPerSecond = { 0 };
    if( ClockPerSecond.QuadPart == 0 ) QueryPerformanceFrequency( &ClockPerSecond );
    LARGE_INTEGER li;
    QueryPerformanceCounter( &li );
    return li.QuadPart * 1000000LL / ClockPerSecond.QuadPart;
}

#else // _WIN32

// UNIX time query

#include <sys/time.h>

inline long long gettimeus()
{
    struct timeval tv;

    gettimeofday( &tv, 0 );
    return (long long) tv.tv_sec * 1000000LL + (long long) tv.tv_usec;
}

#endif // _WIN32

#endif // TIMER_HR_H

