#ifndef _COMMANDFORMAT_H_
#define _COMMANDFORMAT_H_

#include "SDL2/SDL.h"

#include "src/engine/input/commands/Command.hpp"

namespace tbd
{
    enum class CommandStyle : int
    {
        Press = 0,
        LongPress = 1,
        Hold = 2
    };

    enum class CommandAttachPoint : int
    {
        Start = 0,
        End = 1,
        Unset = End
    };

    struct CommandScheme
    {
        float longPressDuration;
        float holdDelay;
        float holdPeriod;
        float holdAcceleration;
    };

    struct CommandType
    {
        SDL_Keycode key;
        CommandStyle style;

        bool operator<(const CommandType &other) const
        {
            if (this->key != other.key)
            {
                return this->key < other.key;
            }
            else
            {
                return this->style < other.style;
            }
        }
    };
}

#endif //_COMMANDFORMAT_H_