cmake_minimum_required(VERSION 3.10)
project(DNS_UDP_IDS)

set(CMAKE_CXX_STANDARD 14)


add_executable(dns_udp_ids
    src/main.cpp
    src/dns_sniffer.cpp
    src/detector.cpp
    src/tester.cpp  
)


find_package(Boost REQUIRED)
target_link_libraries(dns_udp_ids Boost::Boost)
