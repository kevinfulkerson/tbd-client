#include "src/engine/input/commands/CommandFunc.hpp"

namespace tbd
{
    CommandFunc::CommandFunc()
    {
        m_handlerFunc = std::bind(specialty_commands::DoNothing);
    }

    CommandFunc::CommandFunc(const std::function<void()> &func)
    {
        m_handlerFunc = func;
    }

    /* virtual */
    CommandFunc::~CommandFunc()
    {
    }

    /* virtual */
    void CommandFunc::Execute()
    {
        m_handlerFunc();
    }
}