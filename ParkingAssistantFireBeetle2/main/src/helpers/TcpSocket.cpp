#include "src/helpers/TcpSocket.h"
#include "src/helpers/SerialLogger.h"

#include <unistd.h>

namespace mw { namespace helpers {

TcpSocket::TcpSocket(const int16_t port)
    : addr{}
    , clientAddr{}
    , socketFd{-1}
    , clientSocketFd{-1}
    , port{port}
{}

bool TcpSocket::openConn() {
    if (socketFd != -1) {
        ERR("Socket has already opened");
        return true;
    }

    socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (socketFd < 0) {
        ERR("socket() failed");
        return false;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(socketFd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        ERR("bind() failed");
        closeConn();
        return false;
    }

    if (listen(socketFd, 1) < 0) {
        ERR("listen() failed");
        closeConn();
        return false;
    }

    return true;
}

bool TcpSocket::acceptConn() {
    clientAddr = {};
    socklen_t clientAddrLen = sizeof(clientAddr);
    clientSocketFd = accept(socketFd, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);
    if (clientSocketFd < 0) {
        ERR("accept() client failed");
        return false;
    }

    int enable = 1;
    if (setsockopt(clientSocketFd, IPPROTO_TCP, TCP_NODELAY, &enable, sizeof(enable)) < 0) {
        ERR("setsockopt(TCP_NODELAY) failed");
        return false;
    }

    return true;
}

bool TcpSocket::sendTo(const uint8_t* data, std::size_t len) {
    DBG("len: %zu", len);
    if (send(clientSocketFd, data, len, 0) < 0) {
        DBG("Client disconnected");
        return false;
    }
    return true;
}

void TcpSocket::closeConn() {
    if (clientSocketFd != 0) {
        close(clientSocketFd);
        clientSocketFd = -1;
    }
    if (socketFd != 0) {
        close(socketFd);
        socketFd = -1;
    }
}

} } // mw::helpers