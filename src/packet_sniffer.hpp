#pragma once
#include <boost/asio.hpp>
#include "detector.hpp"

class DnsSniffer {
public:
    DnsSniffer(boost::asio::io_context& io, IntrusionDetector& detector);

private:
    void receive();
    void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);

    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    std::array<char, 2048> buffer_;
    IntrusionDetector& detector_;
};
