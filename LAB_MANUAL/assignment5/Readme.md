CN Lab - Assignment 5
Objective

To gain knowledge of more packet capturing tools.
Exercise

Learn and use maximum number of packet generation tools.
Steps to Perform the Exercise

Install Iperf in your Mininet environment:

sudo apt-get update
sudo apt-get install iperf

Install D-ITG (Direct Internet Traffic Generator):

# Download D-ITG from SourceForge
wget https://sourceforge.net/projects/ditg/files/D-ITG-2.8.1-r1023-src.zip
unzip D-ITG-2.8.1-r1023-src.zip
cd D-ITG-2.8.1-r1023/src
make
sudo make install

Using Iperf for TCP traffic generation:

    Start iperf server on one host:

    iperf -s

Generate TCP traffic from another host:

iperf -c <server_ip> -t 10

Using Iperf for UDP traffic generation:

    Start iperf server on one host:

    iperf -s -u

Generate UDP traffic from another host:

iperf -c <server_ip> -u -b 1M

Using D-ITG for traffic generation:

    Start D-ITG receiver on one host:

    ITGRecv

Generate traffic from another host:

ITGSend -a <receiver_ip> -T UDP -c 100 -C 10 -t 10000

    Other packet generation tools:
        hping3: Advanced TCP/IP packet assembler/analyzer
        tcpreplay: Replay network traffic stored in pcap files
        netperf: Network performance measurement
        nuttcp: Network performance measurement tool

Learning Outcomes

    Knowledge of packet generation and capturing tools.

CSM24056
