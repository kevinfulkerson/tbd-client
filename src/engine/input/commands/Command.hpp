#ifndef _ICOMMAND_H_
#define _ICOMMAND_H_

#include <memory>

#include "src/engine/input/strategies/ICommandStrategy.hpp"

namespace tbd
{
    namespace specialty_commands
    {
        inline void DoNothing() {}
    }

    class Command
    {
      public:
        inline Command(std::unique_ptr<ICommandStrategy> strategySink)
        {
            m_strategy = std::move(strategySink);
        }
        virtual ~Command() {}

        inline void Execute(const SDL_Event &event)
        {
            if (m_strategy->CanExecute(event))
            {
                executeCommand();
            }
        }

      protected:
        virtual void executeCommand() = 0;

        std::unique_ptr<ICommandStrategy> m_strategy;
    };
}

#endif //_ICOMMAND_H_