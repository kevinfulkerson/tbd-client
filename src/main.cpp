#include "engine/core/Engine.hpp"

int main(int, char *[])
{
    Engine eng;
    if (eng.Init())
    {
        eng.Start();
    }

    return 0;
}