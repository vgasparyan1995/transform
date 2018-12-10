#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "transform.h"

int main()
{
    std::vector<int> vec = { 1, 2, 3 };
    my::transform(
                  vec.begin(), vec.end(), // 1st range
                  vec.begin(),            // 2nd range
                  vec.begin(),            // 3rd range
                  vec.begin(),            // 4th range
                  vec.begin(),            // 5th range
                  vec.begin(),            // output range
                  [] (auto p1, auto p2, auto p3, auto p4, auto p5) { return p1 + p2 + p3 + p4 + p5; });
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " ")); // must be { 5, 10, 15 }
}
