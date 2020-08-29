/**
 * @author clark
 * @email haixuanwo_clark@hotmail.com
 * @date 2020-08-03
 */

#include "common_include.h"
#include "log.h"

int continuous_run()
{
    char buf[] = {"fpx is rabish"};
	while(1)
	{
        TRACE_INFO("cao ni daye [%d]:%s", 2025, buf);
		sleep(1);
	}
}

int main(int argc, char *argv[])
{
    //log_init();

	continuous_run();

	return 0;
}

