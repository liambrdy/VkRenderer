#include <iostream>

#include "Application.h"

int main()
{
    try
    {
        Application* app = new Application(800, 600);
        app->Run();
        delete app;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}