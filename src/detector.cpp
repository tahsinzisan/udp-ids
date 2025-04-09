#include "detector.hpp"
#include <iostream>
#include <chrono>

void IntrusionDetector::analyze_packet(const std::string& source_ip, const char* data, std::size_t length) {
    detect_ddos(source_ip);
    detect_amplification(source_ip, data, length);
    detect_payload_anomalies(data, length);
}

void IntrusionDetector::detect_ddos(const std::string& ip) {
    auto now = std::chrono::steady_clock::now();
    auto& stats = ip_stats_[ip];

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - stats.last_seen).count();
    stats.last_seen = now;
    stats.count++;

    if (duration < 1 && stats.count > 100) {
        std::cerr << "[ALERT] Potential UDP flood detected from: " << ip << "\n";
        stats.count = 0;  
    }
}

void IntrusionDetector::detect_amplification(const std::string& ip, const char* data, std::size_t length) {
    if (length > 512) {
        std::cerr << "[ALERT] Possible amplification attempt from: " << ip << " (Payload size: " << length << " bytes)\n";
    }
}

void IntrusionDetector::detect_payload_anomalies(const char* data, std::size_t length) {
    for (size_t i = 0; i < length; ++i) {
        if ((unsigned char)data[i] < 0x20 && data[i] != '\n' && data[i] != '\r' && data[i] != '\t') {
            std::cerr << "[ALERT] Suspicious payload detected: non-printable character at offset " << i << "\n";
            return;
        }
    }
}
