//
// Created by ilyas on 24.09.2022.
//

#ifndef HIGHLOAD2DZ_RESPONSES_H
#define HIGHLOAD2DZ_RESPONSES_H

#include <string>

namespace ResponseStatus {
    const std::string DefaultPart = "\r\nServer: nezhibitskiy server\r\nConnection: close\r\n\r\n";
    const std::string MethodNotAllowed = "HTTP/1.1 405 Method Not Allowed" + DefaultPart;
    const std::string HTTPHelloWorld = "HTTP/1.1 200 OK" + DefaultPart + "Hello, world!";
    //    constexpr std::string_view Forbidden = "HTTP/1.1 403 Forbidden\r\nServer: nezhibitskiy server\r\nConnection: close\r\n\r\n";
}

#endif //HIGHLOAD2DZ_RESPONSES_H
