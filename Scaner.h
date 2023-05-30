//
// Created by sasha on 04.01.2023.
//

#ifndef NIR_SCANER_H
#define NIR_SCANER_H

#include <fstream>

typedef struct AddressSize{
    unsigned char * addr;
    int size;
}addressAndSize;


typedef struct pcap_hdr_s {
    unsigned int magic_number = 0xa1b2c3d4;
    short int version_major =2;
    short int version_minor = 4;
    short int  thiszone = 0;
    unsigned int sigfigs = 0;
    unsigned int snaplen = 65535 ;
    unsigned int network = 1;
} pcap_hdr_t;
typedef struct pcaprec_hdr_s {
    unsigned int ts_sec;
    unsigned int ts_usec;
    unsigned int incl_len;
    unsigned int orig_len;
} pcaprec_hdr_t;

typedef struct packet_pcap{
    pcaprec_hdr_t header;
    unsigned char *buff;

}packet;
typedef struct toParse{
    unsigned char * addr;
    int offset;
    int len;

}toParse;
namespace nir {
    class Scaner {
    public:
        std::vector<toParse> hit;
        int pageSize =0;
        int amountClear =0;
        int amountUnclear =0;
        virtual void init(unsigned char*) = 0;
        virtual void writeOut(unsigned char* payload, int size) = 0;

    };
    class IPv4: public Scaner {
    public:
        pcap_hdr_s pcapHeader;
        packet_pcap* packet;
        std::fstream fileOut;
        IPv4(const std::string&, int);
        void  init(unsigned char *) override;
        void writeOut(unsigned char* payload, int size) override;
    };

}

#endif //NIR_SCANER_H
