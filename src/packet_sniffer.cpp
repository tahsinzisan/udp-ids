#include "dns_sniffer.hpp"
#include <iostream>

using boost::asio::ip::udp;

DnsSniffer::DnsSniffer(boost::asio::io_context& io, IntrusionDetector& detector)
    : socket_(io, udp::endpoint(udp::v4(), 53)),
      detector_(detector) {
    receive();
}

void DnsSniffer::receive() {
    socket_.async_receive_from(
        boost::asio::buffer(buffer_), remote_endpoint_,
        [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
            handle_receive(error, bytes_transferred);
        });
}

void DnsSniffer::handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred) {
    if (!error && bytes_transferred > 0) {
        detector_.analyze_packet(remote_endpoint_.address().to_string(), buffer_.data(), bytes_transferred);
    }
    receive();  
}
