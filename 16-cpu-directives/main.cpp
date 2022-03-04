#include <iostream>

#define my_cos(x)  _mcos(x) 
#define cos         __builtin_cos
#define fabs        __builtin_fabs
#define pow         __builtin_pow
#define get_cos_sum(x, y, z) \
    (x*x + y*y - z*z) / (2.f*x*y) + \
    (y*y + z*z - x*x) / (2.f*y*z) + \
    (z*z + x*x - y*y) / (2.f*z*x)

int _mfactor(int i)
{
    int j = i;
    i = 1;
    for (int k = 1; k <= j; k++)
        i *= k;
    return i;
}

float _mcos(float rad)
{
    float cos = 1;
    float add = 0;
    for (int i = 1; true; i++)
    {
        add = pow(-1, (float) i) * (pow(rad,  (float) 2*i) / _mfactor(2*i));
        if (fabs(add) < 0.000'000'1)
            break;
        cos += add;
    }
    return cos;
}

int main(void)
{
    std::cout << "As we need to get the largest sum of cosines of angles of triangles, than:" << std::endl;
    std::cout << "1) we need to count all possible lengths of triangle sides;" << std::endl;
    std::cout << "2) we will count sum of triangles each time and save max result, that we got;" << std::endl;
    float max_sum = 0;
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 5; j++)
        {
            int max = i > j ? i : j;
            int min = i > j ? j : i;
            for (int k = max; k < max + min; k++)
            {
                float m = get_cos_sum(i, j, k);
                printf("[log]: Triangle sides ABC are: %d, %d, %d. Sum of cosines is: %.2f\n", 
                    i, j, k, m); 
                if (m > max_sum)
                    max_sum = m; 
            }
        }
    std::cout << "Result: max cos sum of angles of triangle is: " << max_sum << std::endl;
}