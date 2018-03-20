#ifndef _COMMANDFUNC_H_
#define _COMMANDFUNC_H_

#include "src/engine/input/commands/ICommand.hpp"

#include <functional>

namespace tbd
{
    class CommandFunc : public ICommand
    {
      public:
        CommandFunc();
        CommandFunc(const std::function<void()> &func);
        virtual ~CommandFunc();

        virtual bool CanExecute();
        virtual void Execute();

      private:
        std::function<void()> m_handlerFunc;
    };
}

#endif //_COMMANDFUNC_H_