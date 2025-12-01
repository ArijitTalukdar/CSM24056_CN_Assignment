#include <pcap.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    printf("\n--- Packet captured ---\n");
    printf("Packet length: %d bytes\n", header->len);

    // L2: Ethernet header
    struct ethhdr *eth = (struct ethhdr *)packet;
    printf("Ethernet: Src MAC %02x:%02x:%02x:%02x:%02x:%02x, ",
           eth->h_source[0], eth->h_source[1], eth->h_source[2],
           eth->h_source[3], eth->h_source[4], eth->h_source[5]);
    printf("Dst MAC %02x:%02x:%02x:%02x:%02x:%02x\n",
           eth->h_dest[0], eth->h_dest[1], eth->h_dest[2],
           eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);

    // L3: IP header
    struct iphdr *ip = (struct iphdr *)(packet + sizeof(struct ethhdr));
    struct in_addr src, dst;
    src.s_addr = ip->saddr;
    dst.s_addr = ip->daddr;
    printf("IP: Src %s, Dst %s, Protocol %d\n",
           inet_ntoa(src), inet_ntoa(dst), ip->protocol);

    // L4: TCP/UDP headers
    if(ip->protocol == IPPROTO_TCP) {
        struct tcphdr *tcp = (struct tcphdr *)(packet + sizeof(struct ethhdr) + ip->ihl*4);
        printf("TCP: Src port %d, Dst port %d\n", ntohs(tcp->source), ntohs(tcp->dest));
    } else if(ip->protocol == IPPROTO_UDP) {
        struct udphdr *udp = (struct udphdr *)(packet + sizeof(struct ethhdr) + ip->ihl*4);
        printf("UDP: Src port %d, Dst port %d\n", ntohs(udp->source), ntohs(udp->dest));
    }
}

int main() {
    char *dev;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    // Get the default interface
    dev = pcap_lookupdev(errbuf);
    if (dev == NULL) { printf("Error: %s\n", errbuf); return 1; }
    printf("Listening on device: %s\n", dev);

    // Open the interface for packet capture
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if(handle == NULL) { printf("Couldn't open device %s: %s\n", dev, errbuf); return 1; }

    // Capture 10 packets
    pcap_loop(handle, 10, packet_handler, NULL);

    pcap_close(handle);
    return 0;
}
