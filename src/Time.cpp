
#include "Time.h"

CTime::CTime()
{

}

time_t CTime::get_UTC_seconds()
{
    return time(nullptr);
}

long CTime::get_UTC_useconds()
{
    struct timeval tv;
    int ret = gettimeofday(&tv, nullptr);
    if(0 != ret)
        return -1;

    return (tv.tv_sec*1000000 + tv.tv_usec);
}

bool CTime::set_UTC_seconds(long seconds)
{
    struct timespec spec;
    spec.tv_sec = seconds;
    spec.tv_nsec = 0;
    int ret = clock_settime(CLOCK_REALTIME, &spec);
    if (0 == ret)
        return true;
    else
        return false;
}

long CTime::get_UTC_nanoseconds()
{
    struct timespec spec;
    int ret = clock_gettime(CLOCK_REALTIME, &spec);
    if (0 != ret)
    {
        return -1;
    }
    return (spec.tv_sec*1000000000 + spec.tv_nsec);
}

bool CTime::get_local_date(int &year, int &mon, int &day, int &hour, int &min, int &second)
{
    struct tm *tmp;
    time_t T = time(nullptr);

    tmp = localtime(&T);
    year = tmp->tm_year + 1900;
    mon = tmp->tm_mon + 1;
    day = tmp->tm_mday;

    hour = tmp->tm_hour;
    if(tmp->tm_isdst)   // 夏令时调整一个小时
        hour += 1;

    min = tmp->tm_min;
    second = tmp->tm_sec;
}

bool CTime::get_UTC_date(int &year, int &mon, int &day, int &hour, int &min, int &second)
{
    struct tm *tmp;
    time_t T = time(nullptr);

    tmp = gmtime(&T);
    year = tmp->tm_year + 1900;
    mon = tmp->tm_mon + 1;
    day = tmp->tm_mday;

    hour = tmp->tm_hour;
    if(tmp->tm_isdst)   // 夏令时调整一个小时
        hour += 1;

    min = tmp->tm_min;
    second = tmp->tm_sec;
}

time_t CTime::get_local_time_frome_date(struct tm *tmptr)
{
    return mktime(tmptr);
}

long CTime::start()
{
    return startTime = get_UTC_useconds()/1000; // 获取毫秒数
}

long CTime::stop()
{
     return (get_UTC_useconds()/1000 - startTime);
}

CTime::~CTime()
{

}

