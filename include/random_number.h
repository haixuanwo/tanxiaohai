
#ifndef __RANDOM_NUMMBER_H
#define __RANDOM_NUMMBER_H

class CRand
{
public:
    CRand();
    int get_rand_num(); // 返回0 ~ RAND_MAX[2147483647]之间的随机数
    int get_rand_num_from_range(int start, int end);       // 获取[start, end]范围内的随机数
    int get_rand_float_num_from_range(int start, int end);        // 获取[start, end]范围内的随机数
    ~CRand();
private:

};

#endif

