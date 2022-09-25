//
// Created by ilyas on 25.09.2022.
//

#ifndef HIGHLOAD2DZ_HTTP_H
#define HIGHLOAD2DZ_HTTP_H

namespace http::method {
    const std::string GET = "GET";
    const std::string POST = "POST";
    const std::string PATCH = "PATCH";
    const std::string PUT = "PUT";
    const std::string DELETE = "DELETE";
    const std::string HEAD = "HEAD";
}

namespace http::status {
    enum {
        Continue = 100,
        SwitchingProtocol = 101,
        Processing = 102,
        EarlyHints = 103,
        OK = 200,
        Created = 201,
        Accepted = 202,
        NonAuthoritativeInformation = 203,
        NoContent = 204,
        ResetContent = 205,
        PartialContent = 206,
        MultipleChoice = 300,
        MovedPermanently = 301,
        Found = 302,
        SeeOther = 303,
        NotModified = 304,
        BadRequest = 400,
        Unauthorized = 401,
        Forbidden = 403,
        NotFound = 404,
        MethodNotAllowed = 405,
        RequestTimeout = 408,
        InternalServerError = 500,
        NotImplemented = 501,
        BadGateway = 502
    };
}

#endif //HIGHLOAD2DZ_HTTP_H
