//
// Created by sasha on 17.12.2022.
//

#include <string>
#include "PhysicalAddress.h"

namespace nir {

    PhysicalAddress::PhysicalAddress(PhysicalLayer *layer) : PhysicalLayer(layer) {
        this->paddr = 0;

    }

    PhysicalAddress::PhysicalAddress(DWORD_PTR addr, PhysicalLayer *layer) : PhysicalLayer(layer), paddr(addr) {
    }

    PhysicalAddress::PhysicalAddress() {
        paddr = 0;
    }

    PhysicalAddress::PhysicalAddress(PhysicalAddress *addr, DWORD_PTR offset) : PhysicalLayer(addr->getter()) {
        this->paddr = addr->paddr + offset;

    }
    unsigned char *PhysicalAddress::readBytes(size_t size) {
        return this->readNBytes(size, this->paddr);
    }
    std::string PhysicalAddress::ReadStr(size_t size, size_t offset) {
        auto m = reinterpret_cast< char  * >(this->readNBytes(size + 1, this->paddr + offset));
        m[size] = '\0';
        std::string res(m);
        return res;
    }

    int PhysicalAddress::isVad() {
        auto m = reinterpret_cast< char  * >(this->readNBytes(4, this->paddr - 0xc));
        m[3] = '\0';
        if(strcmp(m,"Vad")==0){
            return 1;
        }
        return 0;
    }

    std::string PhysicalAddress::ReadStr(size_t size) {
        auto tmp = reinterpret_cast< char  * >(this->readNBytes(size + 1, this->paddr));
        tmp[size] = '\0';
        std::string res(tmp);
        return res;
    }
    std::string PhysicalAddress::ReadUnclearStr(size_t size)  {
        auto tmp = reinterpret_cast< char  * >(this->readNBytes(size, this->paddr));
        std::string res;
        if(tmp) {
            for (int i = 0; i < size; ++i) {
                if (tmp[i]) {
                    res.append(&tmp[i]);
                }
            }
            return res;
        }
        res="UNCLEAR";
        return res;
    }

    PhysicalAddress *PhysicalAddress::readAddress(size_t size) {
        return new PhysicalAddress(this->readPhysicalAddress(size, this->paddr), this->getter());
    }


    VirtualAddress PhysicalAddress::ReadVirtFromMemory(size_t size) {
        return VirtualAddress(this->readPhysicalAddress(size, this->paddr));
    }

    PhysicalAddress *PhysicalAddress::operator+(int val){
        return new PhysicalAddress(this->paddr + val, this->getter());
    }

    PhysicalAddress *PhysicalAddress::operator-(int val) {
        return new PhysicalAddress(this->paddr - val, this->getter());
    }

    VirtualAddress PhysicalAddress::ReadVirtFromMemory(size_t size, size_t offset) {
        return VirtualAddress(this->readPhysicalAddress(size, this->paddr + offset));
    }


}
