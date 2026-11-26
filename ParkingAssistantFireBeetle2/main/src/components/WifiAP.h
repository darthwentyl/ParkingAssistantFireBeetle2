#ifndef __COMPONENTS_WIFI_H__
#define __COMPONENTS_WIFI_H__

#include <WiFi.h>

#include "src/helpers/TcpSocket.h"

namespace mw { namespace components {

class WifiAP {
public:
    WifiAP(const int16_t port);
    ~WifiAP() = default;

    WifiAP(const WifiAP&) = delete;
    WifiAP& operator = (const WifiAP&) = delete;
    WifiAP(WifiAP&&) = delete;
    WifiAP& operator = (WifiAP&&) = delete;

    bool open();
    bool accept();
    bool send(const uint8_t* data, std::size_t len);
    void close();

private:
    helpers::TcpSocket socket;
};

} } // mw::components

#endif // __COMPONENTS_WIFI_H__