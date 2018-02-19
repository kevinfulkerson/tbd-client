#ifndef _ICOMMAND_H_
#define _ICOMMAND_H_

namespace tbd
{
    namespace specialty_commands
    {
        inline void DoNothing() {}
    }

    class ICommand
    {
      public:
        virtual ~ICommand() {}
        virtual void Execute() = 0;
    };
}

#endif //_ICOMMAND_H_