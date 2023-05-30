//
// Created by sasha on 03.01.2023.
//

#include <iostream>
#include "Mmpfn.h"
namespace nir {
    nir::Mmpfn::Mmpfn(VirtualLayerSystem* sys, VirtualAddress addr): system(sys) {
        this->vaddrBase = system->vtop(addr)->ReadVirtFromMemory(sizeof(DWORD_PTR));
    }

    VirtualAddress Mmpfn::PteAddrFromPfn(PhysicalAddress *physAddr) const {
        auto offset = (physAddr->paddr / _physiscalPageSize)* _mmpfnStructSize;
        auto mmpfnStructPhAddr = system->vtop(vaddrBase.vaddr + offset);
        return mmpfnStructPhAddr->ReadVirtFromMemory(sizeof(DWORD_PTR), 0x8);

    }

    VirtualAddress Mmpfn::PteAddrFromPfn(DWORD_PTR paddr) const {
        std::cout << paddr<< " ";
        auto offset = (paddr / _physiscalPageSize)* _mmpfnStructSize;
        auto mmpfnStructPhAddr = system->vtop(vaddrBase.vaddr + offset);
        std::cout << std::hex<<mmpfnStructPhAddr->ReadVirtFromMemory(sizeof(DWORD_PTR), 0x8).vaddr<<std::endl;
        return mmpfnStructPhAddr->ReadVirtFromMemory(sizeof(DWORD_PTR), 0x8);
    }
}