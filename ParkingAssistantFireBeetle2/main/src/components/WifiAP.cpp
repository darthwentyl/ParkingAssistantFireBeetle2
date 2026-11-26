#include "src/components/WifiAP.h"
#include "src/components/WiFiCredential.h"

namespace mw { namespace components {

WifiAP::WifiAP(const int16_t port)
    : socket{port}
{
    WiFi.softAP(SSID, PASSW);
}

bool WifiAP::open() {
    return socket.openConn();
}

bool WifiAP::accept() {
    return socket.acceptConn();
}

bool WifiAP::send(const uint8_t* data, std::size_t len) {
    return socket.sendTo(data, len);
}

void WifiAP::close() {
    socket.closeConn();
}

} } // mw::components