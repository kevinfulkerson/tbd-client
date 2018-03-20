#ifndef _ICOMMANDSTRATEGY_H_
#define _ICOMMANDSTRATEGY_H_

#include "SDL2/SDL.h"

namespace tbd
{
    class ICommandStrategy
    {
        public:
        virtual ~ICommandStrategy(){}
        virtual bool CanExecute(const SDL_Event &event) = 0;
    };
}

#endif //_ICOMMANDSTRATEGY_H_