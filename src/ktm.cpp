#include "../ktm/ktm.h"

using namespace ktm;
using namespace std;

int main(int argv, char* argc[])
{
    cout << "hello kutori math" << endl;
    cout << "rsqrt approximation of 4 is " << fast::rsqrt<float>(4.f) << endl;
    return 0;
}