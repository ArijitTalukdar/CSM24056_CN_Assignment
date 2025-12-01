#include <pcap.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

// Track unique protocols
int seen_eth = 0, seen_ip = 0;
int seen_icmp = 0, seen_tcp = 0, seen_udp = 0;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <capture.pcap>\n", argv[0]);
        return 1;
    }

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_offline(argv[1], errbuf);

    if (!handle) {
        printf("Error opening pcap: %s\n", errbuf);
        return 1;
    }

    struct pcap_pkthdr *header;
    const u_char *data;

    printf("\n====== PACKET TIME DIAGRAM ======\n\n");

    while (pcap_next_ex(handle, &header, &data) > 0) {

        double timestamp = header->ts.tv_sec + header->ts.tv_usec / 1e6;

        struct ether_header *eth = (struct ether_header *)data;
        seen_eth = 1;

        printf("Time %.6f sec | ", timestamp);
        printf("[L2: Ethernet] ");

        if (ntohs(eth->ether_type) == ETHERTYPE_IP) {
            seen_ip = 1;

            struct ip *iph = (struct ip *)(data + sizeof(struct ether_header));
            printf("[L3: IPv4] ");

            switch (iph->ip_p) {
                case IPPROTO_ICMP:
                    seen_icmp = 1;
                    printf("[L4: ICMP]");
                    break;

                case IPPROTO_TCP:
                    seen_tcp = 1;
                    printf("[L4: TCP]");
                    break;

                case IPPROTO_UDP:
                    seen_udp = 1;
                    printf("[L4: UDP]");
                    break;

                default:
                    printf("[L4: OTHER]");
            }
        } else {
            printf("[Non-IP]");
        }

        printf("\n");
    }

    printf("\n====== UNIQUE PROTOCOLS FOUND ======\n");

    if (seen_eth) printf("L2: Ethernet\n");
    if (seen_ip)  printf("L3: IPv4\n");

    printf("L4: ");
    if (seen_icmp) printf("ICMP ");
    if (seen_tcp)  printf("TCP ");
    if (seen_udp)  printf("UDP ");
    printf("\n");

    pcap_close(handle);
    return 0;
}
