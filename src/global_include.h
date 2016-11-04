#pragma once

#define UNUSED(x) (void)(x)

#include <sstream>
#include <chrono>

#if ANDROID
#include <android/log.h>
#else
#include <iostream>
#endif

namespace dronelink {

class Debug
{
#ifdef DEBUG
public:
    Debug() : _s() {}

    template <typename T>
    Debug &operator << (const T &x)
    {
        _s << x;
        return *this;
    }

    ~Debug()
    {
#if ANDROID
        __android_log_print(ANDROID_LOG_DEBUG, "DroneLink", "%s", _s.str().c_str());
#else
        std::cout << _s.str() << std::endl;
#endif
    }

private:
    std::stringstream _s;

#else
public:
    template <typename T>
    Debug &operator << (const T &x)
    {
        UNUSED(x);
        return *this;
    }
#endif
};

typedef std::chrono::time_point<std::chrono::steady_clock> dl_time_t;

dl_time_t steady_time();
dl_time_t steady_time_in_future(double duration_s);

double elapsed_s(dl_time_t &since);


} // namespace dronelink
