#include <include/logging/Logger.h>
#include "SDL.h"

using namespace TBD;

Logger::Logger(Priority priority) :
    priorities_(priority)
{
    // Currently does nothing
}

void Logger::logMessage(std::ostream &output, const std::string &msg)
{
    // std::endl flushes buffer, so use it to get this output out NOW
    output << msg << " error: " << SDL_GetError() << std::endl;
}

void Logger::log(std::ostream &output, Priority prio, const std::string &msg)
{
    if ((int)prio & (int)this->priorities_)
    {
        logMessage(output, msg);
    }
}