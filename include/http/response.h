//
// Created by ilyas on 25.09.2022.
//

#ifndef HIGHLOAD2DZ_RESPONSE_H
#define HIGHLOAD2DZ_RESPONSE_H

#include <unordered_map>
#include <vector>
#include <string>
#include "http/http.h"

#define HTTP_VERSION "HTTP/1.1"

namespace http {
    class Response {
    public:
        explicit Response(const int &status = status::OK);
        Response(std::string body, size_t size, const std::string& contentType, int status = status::OK);
        ~Response();
        std::string str() const;
        void setHeader(const std::string &key, const std::string &value);
    private:
        void setDate();
        std::string statusToStr() const;
        void startLineToStream(std::stringstream & ss) const;
        void headersToStream(std::stringstream & ss) const;

        std::unordered_multimap<std::string, std::string> headers;
        std::string body;
        int statusCode;
    };
}

#endif //HIGHLOAD2DZ_RESPONSE_H
