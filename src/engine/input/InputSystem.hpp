#ifndef _INPUTSYSTEM_H_
#define _INPUTSYSTEM_H_

#include <functional>
#include <map>
#include <memory>

#include "SDL2/SDL.h"

#include "src/engine/input/commands/CommandFormat.hpp"

namespace tbd
{
    struct CommandMetadata
    {
        bool active;
        CommandAttachPoint previousPoint;

        // TODO: add timing for long/short press distinction
        //double timestamp;

        CommandAttachPoint activatePoint;
        std::unique_ptr<ICommand> command;
    };

    class InputSystem
    {
      public:
        InputSystem();
        virtual ~InputSystem();

        bool Init();
        int HandleInput();
        int RegisterEventHandler(CommandType type,
                                 CommandAttachPoint attachmentPoint,
                                 std::unique_ptr<ICommand> commandSink);

      private:
        SDL_Event m_event;

        typedef std::map<CommandType, CommandMetadata> CommandMap;
        CommandMap m_commandMap;
    };
}

#endif //_INPUTSYSTEM_H_