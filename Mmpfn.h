//
// Created by sasha on 03.01.2023.
//

#ifndef NIR_MMPFN_H
#define NIR_MMPFN_H
#include "VirtualAddress.h"
#include "VirtualLayerSystem.h"
#include "PhysicalAddress.h"
#include "Constants.h"
namespace nir {


    class Mmpfn {
    public:
        VirtualLayerSystem* system;
        VirtualAddress vaddrBase;
        Mmpfn(VirtualLayerSystem*, VirtualAddress );
        VirtualAddress PteAddrFromPfn(PhysicalAddress*) const;
        VirtualAddress PteAddrFromPfn(DWORD_PTR) const;


    };

}
#endif //NIR_MMPFN_H
