//
// Created by ilyas on 27.09.2022.
//

#ifndef HIGHLOAD2DZ_CONFIG_H
#define HIGHLOAD2DZ_CONFIG_H

#include <fstream>
#include <sstream>

struct Config {
    static std::pair<Config, bool> read_config(const std::string& address) {
        std::ifstream fin(address);
        if (!fin.is_open()) {
            return std::make_pair(Config{cpu: 4, doc_root: "./static"}, false);
        }

        Config config;
        std::stringstream ss;

        std::string line;
        while (!fin.eof()) {
            getline(fin, line);
            ss << line;
        }
        fin.close();

        ss >> config.cpu;
        ss >> config.doc_root;

        return std::make_pair(config, true);
    }

    int cpu;
    std::string doc_root;
};


#endif //HIGHLOAD2DZ_CONFIG_H
