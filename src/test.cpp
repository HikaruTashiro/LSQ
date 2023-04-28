#include "lsq.h"
#include <utility>
#include <vector>
#include <iostream>

int main()
{
    std::vector<std::pair<float, float>> pog = {{2.0f,5.0f},{4.0f,4.0f},{6.0f,8.0f},{8.0f,6.0f},{10.0f,12.0f}};
    lsq based(pog);
    std::cout << based.line[0] << " * " << 'x' << " + " << based.line[1] << '\n';

    return 0;
}
