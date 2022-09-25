//
// Created by ilyas on 25.09.2022.
//

#ifndef HIGHLOAD2DZ_STATICHANDER_H
#define HIGHLOAD2DZ_STATICHANDER_H

#include <utility>
#include "http/response.h"
#include "http/request.h"
#include <filesystem>

class StaticHandler {
public:
    StaticHandler(std::string rootDir, std::string defaultFile):_rootDir(std::move(rootDir)),
                                                                _defaultFile(std::move(defaultFile)) {}
    http::Response handle(const http::Request &request) const;

private:
    std::string contentType(const std::string& extension) const;

    std::filesystem::path _rootDir;
    std::string _defaultFile;
};

#endif //HIGHLOAD2DZ_STATICHANDER_H
