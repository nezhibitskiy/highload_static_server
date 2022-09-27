//
// Created by ilyas on 25.09.2022.
//

#include "http/response.h"
#include <chrono>
#include <sstream>
#include <unistd.h>

void http::Response::setDate() {
    char time[1000];
    time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm tm = *gmtime(&now);
    strftime(time, sizeof time, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    setHeader("Date", std::string(time));
}

http::Response::Response(const int &status) : statusCode(status) {
    setDate();
    setHeader("Server", "nezhibitskiy");
    setHeader("Connection", "close");
}

void http::Response::startLineToStream(std::stringstream & ss) const {
    ss << HTTP_VERSION << " " << statusCode << " " << statusToStr() << "\r\n";
}

std::string http::Response::str() const {
    std::stringstream response;
    startLineToStream(response);
    headersToStream(response);
    response << "\r\n";
    response << body;
    return response.str();
}

http::Response::Response(std::string body, size_t size, const std::string &contentType, int status) : statusCode(status) {
    setDate();
    setHeader("Content-Type", contentType);
    setHeader("Server", "nezhibitskiy");
    this->body = body;
    setHeader("Content-Length", std::to_string(size));
    setHeader("Connection", "close");
}

http::Response::~Response() {
}

void http::Response::headersToStream(std::stringstream & ss) const {
    for (auto &pair : headers) {
        ss << pair.first << ": " << pair.second << "\r\n";
    }
}

void http::Response::setHeader(const std::string &key, const std::string &value) {
    headers.insert({key, value});
}

std::string http::Response::statusToStr() const {
    switch(statusCode) {
        case (100): return "Continue";
        case (101): return "Switching Protocol";
        case (102): return "Processing";
        case (103): return "Early Hints";
        case (200): return "OK";
        case (201): return "Created";
        case (202): return "Accepted";
        case (204): return "No Content";
        case (300): return "Multiple Choice";
        case (301): return "Moved Permanently ";
        case (302): return "Found";
        case (304): return "Not Modified";
        case (400): return "Bad Request";
        case (401): return "Unauthorized ";
        case (403): return "Forbidden";
        case (404): return "NotFound";
        case (405): return "Method Not Allowed";
        case (408): return "Request Timeout";
        case (500): return "Internal Server Error";
        case (501): return "Not Implemented";
        case (502): return "Bad Gateway";
        default: return "undefined";
    }
}
