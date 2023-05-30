//
// Created by sasha on 17.12.2022.
//

#ifndef NIR_VIRTUALLAYER_H
#define NIR_VIRTUALLAYER_H
#include "windows.h"
#include "Structures.h"
#include "VirtualAddress.h"
#include "PhysicalAddress.h"
#include "Structures.h"
#include "TreeForVad.h"
namespace nir {
    class VirtualLayer{
    public:
        PhysicalAddress* pml4Base;
        EPROCESS* Eprocess;
        binary_tree* Vad;
        explicit VirtualLayer(PhysicalAddress* pml4Base);
        PhysicalAddress* vtop(VirtualAddress vaddr) const;
        PhysicalAddress* vtop(DWORD_PTR) const;
        explicit VirtualLayer(EPROCESS *);
        VirtualAddress ptov(PhysicalAddress *);


    };

}
#endif //NIR_VIRTUALLAYER_H
