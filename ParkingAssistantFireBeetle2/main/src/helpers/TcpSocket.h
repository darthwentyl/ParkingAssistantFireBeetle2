#ifndef __HELPERS_TCPSOCKET_H__
#define __HELPERS_TCPSOCKET_H__

#include <lwip/sockets.h>
#include <netinet/in.h>

namespace mw { namespace helpers {

class TcpSocket {
public:
    TcpSocket(const int16_t port);
    ~TcpSocket() = default;

    TcpSocket(const TcpSocket&) = delete;
    TcpSocket& operator = (const TcpSocket&) = delete;
    TcpSocket(TcpSocket&&) = delete;
    TcpSocket& operator = (TcpSocket&&) = delete;

    bool openConn();
    bool acceptConn();
    bool sendTo(const uint8_t* data, std::size_t len);
    void closeConn();

private:
    sockaddr_in addr;
    sockaddr_in clientAddr;
    int32_t socketFd;
    int32_t clientSocketFd;
    int16_t port;
};

} } // mw::helpers

#endif // __HELPERS_TCPSOCKET_H__