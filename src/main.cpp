#include "app.hpp"
#include "paths.hpp"
#include <windows.h>


int main(int argc, char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    src::Paths::initialize();

    src::App app;
    return app.run(argc, argv);
}