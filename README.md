DNS UDP Intrusion Detection System (IDS)

This is a high-performance DNS UDP Intrusion Detection System (IDS) written in C++ using Boost.Asio. The IDS monitors and analyzes DNS-related UDP traffic to detect abnormal patterns like DDoS attacks, DNS amplification, and malformed DNS packets.

Features

- Real-time DNS UDP traffic monitoring
- Detects DNS-based DDoS (UDP flood) attacks
- Detects DNS amplification attacks
- Detects malformed DNS packets

Requirements

- Boost C++ Libraries (Boost.Asio)
- CMake for building the project
- g++ or any other C++14-compatible compiler

Installing Boost

- Ubuntu/Debian:
  sudo apt-get install libboost-all-dev

- MacOS (using Homebrew):
  brew install boost

Building the Project

1. Clone the repository:
   git clone https://github.com/your-username/dns_udp_ids.git
   cd dns_udp_ids

2. Create a build directory:
   mkdir build
   cd build

3. Run CMake to configure the build:
   cmake ..

4. Build the project:
   make

Running the IDS

Once built, you can run the DNS UDP IDS on the target machine (replace 192.168.1.100 with your target machine's IP):

sudo ./dns_udp_ids

Running the Tester

To simulate attacks and test the IDS, run the tester (replace 192.168.1.100 with your target machine's IP):

sudo ./dns_udp_ids_tester

The tester will simulate:
1. A UDP flood attack (DDoS)
2. A DNS amplification attack
3. Malformed DNS packets

Testing the IDS

After building and running the IDS, you can use the tester to generate traffic. Here’s how to test:

1. Start the IDS:
   sudo ./dns_udp_ids

2. Run the tester in another terminal:
   sudo ./dns_udp_ids_tester

3. Observe the IDS output to verify if it detects the generated attacks (UDP flood, DNS amplification, malformed DNS packets).

Notes

- Ensure you have root privileges to run the IDS and send traffic on low ports (e.g., port 53 for DNS).
- The tester simulates common DNS attack scenarios to validate that your IDS works as expected.
- Customize the source IPs and attack types in the tester as needed.
