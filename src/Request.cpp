//
// Created by ilyas on 25.09.2022.
//

#include <http/request.h>
#include <regex>
#include <curl/curl.h>

http::Request::Request(const std::string &request) {
    parseStartLine(request.cbegin(), request.cend());
}

void http::Request::parseStartLine(const std::string::const_iterator &begin, const std::string::const_iterator &end){
    std::sregex_iterator match(begin, end, startLine);
    _method = match->format("$1");
    _url = urlDecode(match->format("$2"));
}

std::string http::Request::method() const {
    return _method;
}

std::string http::Request::url() const {
    return _url;
}

std::string http::Request::path() const {
    int startQuery = _url.find('?');
    if (startQuery == -1) {
        return _url;
    }
    return _url.substr(0, startQuery);
}

std::string http::Request::urlDecode(const std::string& url) {
    CURL *curl = curl_easy_init();
    int outlength;
    char *output = curl_easy_unescape(curl, url.c_str(), url.size(), &outlength);
    auto temp_body = std::string(output);
    curl_free(output);
    curl_easy_cleanup(curl);
    replacePlusToSpace(temp_body);
    return temp_body;
}

void http::Request::replacePlusToSpace(std::string &str) {
    auto it = str.begin();
    auto end = str.end();
    while (it != end) {
        if (*it == '+') {
            *it = ' ';
        }
        it++;
    }
}