#pragma once
#include <string>
#include <unordered_map>
#include <chrono>

class IntrusionDetector {
public:
    void analyze_packet(const std::string& source_ip, const char* data, std::size_t length);

private:
    struct Stats {
        int count = 0;
        std::chrono::steady_clock::time_point last_seen;
    };

    std::unordered_map<std::string, Stats> ip_stats_;

    void detect_ddos(const std::string& ip);
    void detect_amplification(const std::string& ip, const char* data, std::size_t length);
    void detect_payload_anomalies(const char* data, std::size_t length);
};
