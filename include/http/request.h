//
// Created by ilyas on 25.09.2022.
//

#ifndef HIGHLOAD2DZ_REQUEST_H
#define HIGHLOAD2DZ_REQUEST_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <regex>

namespace http {
    inline std::regex startLine(R"((PUT|GET|POST|HEAD|OPTIONS|PATCH)\s(/[^\n\s\r\t\0]*)\sHTTP/([\d.]+)\r\n)");

    class Request {
    public:
        explicit Request(const std::string &request);
        std::string method() const;
        std::string path() const;
        std::string url() const;

    private:
        std::string _method;
        std::string _url;

        void parseStartLine(const std::string::const_iterator &begin, const std::string::const_iterator &end);
        std::string urlDecode(const std::string &url);

        static void replacePlusToSpace(std::string &str);
    };
}

#endif //HIGHLOAD2DZ_REQUEST_H
