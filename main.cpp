#include <server.h>
#include <string>
#include "staticHander.h"

int main(int argc, char **argv)
{
    std::string rootDirectory = "./static";
    std::string defaultFile = "index.html";
    auto handler = StaticHandler(rootDirectory, defaultFile);

    Server server(1, "./static", "index.html");
    server.Run();

    return 0;
}
