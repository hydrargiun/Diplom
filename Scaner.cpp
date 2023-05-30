//
// Created by sasha on 04.01.2023.
//
#include <iostream>
#include <vector>
#include "Scaner.h"

namespace nir {

    int bytes_to_read(const unsigned char *page, int ptr, int type) {
        int eth2 = 14;
        int Payload = int(page[ptr + 17]) + (int(page[ptr + 16]) << 8);
        return eth2 + Payload;
    }

    int validator(const unsigned char *page, int ptr) {
        int len = 4 * int(page[ptr] & 15);
        int sum = 0;
        int count = 0;
        for (int i = ptr; i < ptr + len; i += 2) {
            sum += ((unsigned char) page[i] << 8) | (unsigned char) page[i + 1];
            count++;
        }
        while (sum >> 16) {
            sum = (sum & 0xffff) + (sum >> 16);
        }
        sum = ~sum;
        return ((unsigned short) sum);
    }

    int typeDetermine(const unsigned char *pageBuf, int ptr) {
        int type = int(pageBuf[ptr + 23]);
        if (type == 6 || type == 17) {
            return type;
        } else return 0;
    }

    int sanity(const unsigned char *pageBuf, int ptr) {
        if (pageBuf[ptr] == 8 && pageBuf[ptr + 1] == 0 &&
            int(pageBuf[ptr + 2] >> 4) == 4 && (int) pageBuf[ptr + 2] >= 69) {
            return true;
        }
        return false;

    }

    void IPv4::init(unsigned char *pageBuf) {
        for (int i = 0; i < pageSize; ++i) {
            if (sanity(pageBuf, i)) {
                int ptr = i - 12; // moving to Ethernet start
                int type = typeDetermine(pageBuf, ptr);
                if (type) {
                    if (!validator(pageBuf, ptr + 14)) {
                        int bytesToRead = bytes_to_read(pageBuf, ptr, type);
                        toParse hitInfo;
                        hitInfo.addr = pageBuf;
                        hitInfo.offset = ptr;
                        hitInfo.len = bytesToRead;
                        hit.emplace_back(hitInfo);
                    }
                }
            }

        }
    }

    IPv4::IPv4(const std::string& name, int pSize) {
        pcap_hdr_s pcap;
        this->fileOut.open(name, std::ios::out | std::ios::binary);
        this->fileOut.write(reinterpret_cast<const char *>(&pcap), sizeof(pcap_hdr_s));
        this->pageSize = pSize;


    }

    void IPv4::writeOut(unsigned char *payload, int size) {
        this->packet = new packet_pcap;
        this->packet->header.orig_len = size;
        this->packet->header.incl_len = size;
        this->packet->header.ts_usec = 0;
        this->packet->header.ts_sec = 0;
        this->fileOut.write(reinterpret_cast<const char *>(&this->packet->header), sizeof(this->packet->header));
        this->fileOut.write(reinterpret_cast<const char *>(payload), size);
    }
}