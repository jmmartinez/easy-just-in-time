// issue https://github.com/jmmartinez/easy-just-in-time/issues/43 reported by mame
// RUN: %clangxx %cxxflags %include_flags %ld_flags %s -Xclang -load -Xclang %lib_pass -o %t
// RUN: %t

#include <iostream>
#include <easy/jit.h>

using namespace std;

static void EASY_JIT_EXPOSE kernel(const int a, const int b, int  * const res)
{
    for(int x = 1; x < a; x++)
    {
        for(int y = 1; y < b; y++)
        {
            *res += a*b - b;
        }
    }
}

int main(int argc, char **argv)
{
    int res = 0;
    kernel(1000, 250000, &res);

    using namespace std::placeholders;
    auto kernel_opt = easy::jit(kernel, 1000, 250000, _1);
    kernel_opt(&res);
   
    cout << res << endl;
    return 0;
}
