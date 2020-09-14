
#include "random_number.h"
#include <time.h>
#include <stdlib.h>

CRand::CRand()
{

}

int CRand::get_rand_num()
{
    srand(time(nullptr));
 	return rand();
}

int CRand::get_rand_num_from_range(int start, int end)
{
    if (start > end)
        return -1;
    else if (start == end)
        return start;

    int num = get_rand_num();
    return ((num % (end-start+1)) + start);
}

double CRand::get_rand_float_num_from_range(int start, int end)
{
    //int num = get_rand_num();
    //return num / (double)(RAND_MAX);
}

CRand::~CRand()
{

}


