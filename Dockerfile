FROM ubuntu:latest AS release

RUN apt-get update && \
    apt-get -y install --no-install-recommends \
    make \
    g++ \
    cmake \
    libevent-dev \
    curl \
    libcurl4-openssl-dev \
    zlib1g-dev

COPY httpd.conf /etc/httpd.conf

WORKDIR /etc

COPY  . /etc

RUN mkdir build && \
    cd build && \
    cmake .. && \
    make

ENTRYPOINT ["/etc/build/tp_highload_static_server"]