FROM alpine:latest AS release

RUN apk upgrade --update-cache --available && \
    apk add cmake && apk add g++ && apk add openssl && apk add make && apk add zlib-dev && \
    rm -rf /var/cache/apk/*

RUN apk update

COPY httpd.conf /etc/httpd.conf

WORKDIR /etc

COPY  . /etc

RUN mkdir build && \
    cd build && \
    cmake .. && \
    make

ENTRYPOINT ["/etc/build/tp_highload_static_server"]