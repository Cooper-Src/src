#include "app.hpp"
#include "paths.hpp"

#include <iostream>
#include <windows.h>
#include <curl/curl.h>

int main(int argc, char **argv)
{
    CURLcode res = curl_global_init(CURL_GLOBAL_DEFAULT);

    if (res != CURLE_OK)
    {
        std::cout << curl_easy_strerror(res) << '\n';
        return 1;
    }

    if (res != CURLE_OK)
    {
        std::cerr
            << "curl_global_init failed: "
            << curl_easy_strerror(res)
            << '\n';
        return 1;
    }

    SetConsoleOutputCP(CP_UTF8);
    src::Paths::initialize();

    src::App app;

    int result = app.run(argc, argv);

    curl_global_cleanup();

    return result;
}