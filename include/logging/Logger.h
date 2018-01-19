#include <ostream>
#include <string>
#include <include/logging/LoggingPriority.h>

namespace TBD
{
    class Logger
    {
        private:
            void logMessage(std::ostream &output, const std::string &msg);

            Priority priorities_;

        public:
            Logger(Priority priority);
            void log(std::ostream &output, Priority prio, const std::string &msg);
    };
}