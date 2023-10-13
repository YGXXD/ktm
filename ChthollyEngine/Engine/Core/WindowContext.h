#ifndef _WINDOW_CONTEXT_H_
#define _WINDOW_CONTEXT_H_

#include "Basic/SetupBase.h"

namespace keg
{
class CHTHOLLY_ENGINE_API WindowContext final
{
public:
    static void Init();
    static void Quit();
    static void PollEvent();
};
}

#endif