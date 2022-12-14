//
// Created by ilyas on 25.09.2022.
//

#include "staticHander.h"
#include <fstream>

std::map<std::string, std::string> cachedData;

http::Response StaticHandler::handle(const http::Request &request) const {
    if (request.method() != http::method::HEAD && request.method() != http::method::GET) {
        return http::Response(http::status::MethodNotAllowed);
    }

    std::string path = request.path();
    if (path.find("../") != std::string::npos) {
        std::cout << "Forbidden error. Found '../'. Request path: " << request.path() << std::endl;
        return http::Response(http::status::Forbidden);
    }

    std::filesystem::path filepath = _rootDir;
    filepath.append(path.substr(1));

    if (!std::filesystem::exists(filepath)) {
        return http::Response(http::status::NotFound);
    }

    if (!filepath.has_filename()) {
        filepath.replace_filename(_defaultFile);
    }

    if (std::filesystem::is_directory(filepath)) {
        std::cout << "Forbidden error. Is not dir. Request path: " << request.path() << std::endl;
        return http::Response(http::status::Forbidden);
    }

    if (!std::filesystem::exists(filepath)) {
        std::cout << "Forbidden error. Doesn't exists. Request path: " << request.path() << std::endl;
        return http::Response(http::status::Forbidden);
    }

    auto dataType = contentType(filepath.extension());
    auto contentLength = std::filesystem::file_size(filepath);

    if (request.method() == http::method::HEAD) {
        auto response = http::Response();
        response.setHeader("Content-Type", dataType);
        response.setHeader("Content-Length", std::to_string(contentLength));
        return response;
    }

    std::string read;

    auto search = cachedData.find(filepath.string());
    if (search != cachedData.end()) {
        read += cachedData[filepath.string()];
        return http::Response(
                read,
                read.length(),
                dataType, filepath.string(), contentLength);
    } else {
        std::ifstream input( filepath.string(), std::ios::binary);
        std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
        std::string str(buffer.begin(), buffer.end());
        cachedData[filepath.string()] = str;
        read += str;
        return http::Response(
                read,
                read.length(),
                dataType, filepath.string(), contentLength);
    }

}

std::string StaticHandler::contentType(const std::string &extension) const {
    if (extension == ".html") {
        return "text/html";
    } else if (extension == ".js") {
        return "application/javascript";
    } else if (extension == ".css") {
        return "text/css";
    } else if (extension == ".jpg" || extension == ".jpeg") {
        return "image/jpeg";
    } else if (extension == ".png") {
        return "image/png";
    } else if (extension == ".gif") {
        return "image/gif";
    } else if (extension == ".svg") {
        return "image/svg+xml";
    } else if (extension == ".swf") {
        return "application/x-shockwave-flash";
    }
    return "text/plain";
}