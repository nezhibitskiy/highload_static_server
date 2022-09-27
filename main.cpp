#include <server.h>
#include <string>
#include "staticHander.h"
#include "config.h"

int main(int argc, char **argv)
{
    Config config;
    bool ok;
    std::tie(config, ok) = Config::read_config("/etc/httpd.conf");
    if (!ok) {
        std::cout << "bad config" <<std::endl;
    }

    Server server(config.cpu, config.doc_root, "wikipedia_russia.html");
    server.Run();
    return 0;
}
