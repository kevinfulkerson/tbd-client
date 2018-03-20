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
        uint32_t timestamp;

        CommandAttachPoint activatePoint;
        std::unique_ptr<Command> command;
    };

    typedef std::map<CommandType, CommandMetadata> CommandMap;

    class InputSystem
    {
      public:
        InputSystem(const CommandScheme &scheme);
        virtual ~InputSystem();

        bool Init();
        int HandleInput();
        int RegisterEventHandler(CommandType type,
                                 CommandAttachPoint attachmentPoint,
                                 std::unique_ptr<Command> commandSink);

      private:
        SDL_Event m_event;
        CommandScheme m_commandScheme;

        CommandMap m_commandMap;
    };
}

#endif //_INPUTSYSTEM_H_