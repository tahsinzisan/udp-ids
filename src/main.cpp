#include "dns_sniffer.hpp"
#include "detector.hpp"

int main() {
    try {
        boost::asio::io_context io;
        IntrusionDetector detector;
        DnsSniffer sniffer(io, detector);
        io.run();
    } catch (std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
    }
    return 0;
}
