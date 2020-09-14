
#ifndef __CLOCK_H
#define __CLOCK_H

#include <time.h>
#include <sys/time.h>

class CTime
{
public:
   	CTime();

    // 获取UTC秒数
    time_t get_UTC_seconds();
    bool set_UTC_seconds(long seconds);

    // 获取UTC纳秒数
    long get_UTC_nanoseconds();

    // 获取UTC毫秒数
    long get_UTC_useconds();

    bool get_local_date(int &year, int &mon, int &day, int &hour, int &min, int &second);
    bool get_UTC_date(int &year, int &mon, int &day, int &hour, int &min, int &second);
    time_t get_local_time_frome_date(struct tm *tmptr);
    // asctime、ctime已弃用，易受到缓冲区溢出问题

    long start();
    long stop();

    ~CTime();
private:
    long startTime;
};

#endif

