#ifndef _MOUSE_CODE_H_
#define _MOUSE_CODE_H_

#include <cstdint>

namespace xxd
{
namespace Mouse
{
enum MouseCode : uint16_t
{
    Button0 = 0,
    Button1 = 1,
    Button2 = 2,
    Button3 = 3,
    Button4 = 4,

    ButtonLeft = Button0,
    ButtonRight = Button1,
    ButtonMiddle = Button2,
    ButtonLast = Button4
};
}
}


#endif