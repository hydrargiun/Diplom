//
// Created by sasha on 17.12.2022.
//

#ifndef NIR_PHYSICALADDRESS_H
#define NIR_PHYSICALADDRESS_H
#include "windows.h"
#include "PhysicalLayer.h"
#include <string>
#include "VirtualAddress.h"
namespace nir {
    class PhysicalAddress : public PhysicalLayer{
    public:
        DWORD_PTR paddr;
        PhysicalAddress();
        explicit PhysicalAddress(PhysicalLayer*);
        PhysicalAddress(DWORD_PTR,PhysicalLayer*);
        PhysicalAddress(PhysicalAddress*, DWORD_PTR);
        unsigned char* readBytes(size_t size);
        std::string  ReadStr(size_t size, size_t offset);
        std::string  ReadStr(size_t size);
        std::string  ReadUnclearStr(size_t size);
        int isVad();
        PhysicalAddress * readAddress(size_t size);
        VirtualAddress ReadVirtFromMemory(size_t size);
        VirtualAddress ReadVirtFromMemory(size_t size,size_t offset);
        PhysicalAddress* operator +(int val);
        PhysicalAddress* operator -(int val);

    };
}

#endif //NIR_PHYSICALADDRESS_H
