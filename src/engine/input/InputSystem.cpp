#include "src/engine/input/InputSystem.hpp"

namespace tbd
{
    InputSystem::InputSystem(const CommandScheme &scheme) : m_commandScheme(scheme)
    {
    }

    /* virtual */
    InputSystem::~InputSystem()
    {
    }

    bool InputSystem::Init()
    {
        return true;
    }

    int InputSystem::HandleInput()
    {
        int retVal = 0;

        while (SDL_PollEvent(&m_event) == 1)
        {
            // Check if this event directs us to quit the application
            if (m_event.type == SDL_QUIT)
            {
                retVal = -1;
            }
            else if (m_event.type == SDL_KEYDOWN)
            {
                // On initial key down, we assume this input is a hold command
                CommandType type;
                type.key = m_event.key.keysym.sym;
                type.style = CommandStyle::Hold;

                // Try to find this command in the map
                CommandMap::iterator holdIt;
                if ((holdIt = m_commandMap.find(type)) != m_commandMap.end())
                {
                    // The command has been registered, fire it
                    holdIt->second.command->Execute();

                    // Set the meta data so we can track this command's execution
                    holdIt->second.active = true;
                    holdIt->second.previousPoint = CommandAttachPoint::Start;
                }

                // Since it could be possible to do multiple things with a
                // single key press depending on the interaction, we will
                // continue processing for other events

                // First, look for a normal press event
                type.style = CommandStyle::Press;
                CommandMap::iterator pressIt;
                if ((pressIt = m_commandMap.find(type)) != m_commandMap.end())
                {
                    // Check to see if this command should be activated now
                    if (pressIt->second.previousPoint == CommandAttachPoint::End &&
                        pressIt->second.activatePoint == CommandAttachPoint::Start)
                    {
                        pressIt->second.command->Execute();
                    }

                    pressIt->second.active = true;
                    pressIt->second.previousPoint = CommandAttachPoint::Start;
                }

                // Next, look for a long press event
                type.style = CommandStyle::LongPress;
                CommandMap::iterator longIt;
                if ((longIt = m_commandMap.find(type)) != m_commandMap.end())
                {
                    if (longIt->second.timestamp == 0)
                    {
                        longIt->second.active = true;
                        longIt->second.timestamp = m_event.key.timestamp;
                    }
                    else if (longIt->second.activatePoint == CommandAttachPoint::Start &&
                             longIt->second.active)
                    {
                        if (m_event.key.timestamp - longIt->second.timestamp >
                            m_commandScheme.longPressDuration)
                        {
                            longIt->second.active = false;
                            longIt->second.command->Execute();
                        }
                    }

                    longIt->second.previousPoint = CommandAttachPoint::Start;
                }
            }
            else if (m_event.type == SDL_KEYUP)
            {
                // On key up, we mirror key down and start with holds
                CommandType type;
                type.key = m_event.key.keysym.sym;
                type.style = CommandStyle::Hold;

                CommandMap::iterator holdIt;
                if ((holdIt = m_commandMap.find(type)) != m_commandMap.end())
                {
                    holdIt->second.active = false;
                    holdIt->second.previousPoint = CommandAttachPoint::Unset;
                }

                // First, look for a normal press event
                type.style = CommandStyle::Press;
                CommandMap::iterator pressIt;
                if ((pressIt = m_commandMap.find(type)) != m_commandMap.end())
                {
                    if (pressIt->second.previousPoint == CommandAttachPoint::Start &&
                        pressIt->second.activatePoint == CommandAttachPoint::End)
                    {
                        pressIt->second.command->Execute();
                    }

                    pressIt->second.active = false;
                    pressIt->second.previousPoint = CommandAttachPoint::End;
                }

                // Next, look for a long press event
                type.style = CommandStyle::LongPress;
                CommandMap::iterator longIt;
                if ((longIt = m_commandMap.find(type)) != m_commandMap.end())
                {
                    if (longIt->second.timestamp != 0 &&
                        longIt->second.activatePoint == CommandAttachPoint::End)
                    {
                        if (m_event.key.timestamp - longIt->second.timestamp >
                            m_commandScheme.longPressDuration)
                        {
                            longIt->second.command->Execute();
                        }
                    }

                    longIt->second.timestamp = 0;
                    longIt->second.active = false;
                    longIt->second.previousPoint = CommandAttachPoint::End;
                }
            }
        }

        return retVal;
    }

    int InputSystem::RegisterEventHandler(CommandType type,
                                          CommandAttachPoint attachmentPoint,
                                          std::unique_ptr<ICommand> commandSink)
    {
        CommandMetadata meta;
        meta.activatePoint = attachmentPoint;
        meta.active = false;
        meta.timestamp = 0;
        meta.command = std::move(commandSink);
        meta.previousPoint = CommandAttachPoint::Unset;

        // TODO: check return value
        m_commandMap.insert(CommandMap::value_type(type, std::move(meta)));

        return 0;
    }
}