#include "src/engine/core/Engine.hpp"

int main(int, char *[])
{
    tbd::Engine eng;
    if (eng.Init())
    {
        eng.Start();
    }

    return 0;
}