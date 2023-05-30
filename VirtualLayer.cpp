//
// Created by sasha on 17.12.2022.
//
#include "VirtualLayer.h"

namespace nir {
    listEntry *add(VirtualLayer *layer, PhysicalAddress *ptr);

    VirtualLayer::VirtualLayer(PhysicalAddress *base) : pml4Base(base) {
        this->Vad = nullptr;
        this->Eprocess = nullptr;
    }

    VirtualLayer::VirtualLayer(EPROCESS *eprocess){
        pml4Base = eprocess->base->readAddress(8);
        this->Eprocess = eprocess;
    }

    PhysicalAddress *VirtualLayer::vtop(VirtualAddress addr) const {
        DWORD_PTR PHY_ADDRESS_MASK = 0xFFFFFFFFFF000;
        WORD pml4Offset;
        DWORD_PTR PML4E;
        WORD pdptOffset;
        DWORD_PTR PDPE;
        WORD pdtOffset;
        DWORD_PTR PDE;
        WORD ptOffset;
        DWORD_PTR PTE;
        WORD phyPageOffset;
        DWORD_PTR pAddress;


        pml4Offset = (addr.vaddr >> (12 + 9 + 9 + 9)) & 0x1FF;
        DWORD_PTR PML4_Pointer = ((this->pml4Base->paddr & PHY_ADDRESS_MASK) + (pml4Offset * 8));
        PML4E = this->pml4Base->readPhysicalAddress(sizeof(PML4E), PML4_Pointer);
        if (!PML4E) {
            return nullptr;
        }
        pdptOffset = (addr.vaddr >> (12 + 9 + 9)) & 0x1FF;
        DWORD_PTR PDPE_Pointer = (PML4E & PHY_ADDRESS_MASK) + (pdptOffset * 8);
        PDPE = this->pml4Base->readPhysicalAddress(sizeof(PDPE), PDPE_Pointer);
        if (!PDPE) {
            return nullptr;
        }
        pdtOffset = (addr.vaddr >> (12 + 9)) & 0x1FF;
        DWORD_PTR PDE_Pointer = (PDPE & PHY_ADDRESS_MASK) + (pdtOffset * 8);
        PDE = this->pml4Base->readPhysicalAddress(sizeof(PDE), PDE_Pointer);
        if (!PDE) {
            return nullptr;
        }
        if ((PDE & 0x80) != 0) {
            pAddress = ((PDE & 0xFFFFFFFE00000) + (addr.vaddr & 0x1FFFFF));
            return new PhysicalAddress(pAddress, this->pml4Base->getter());
        }
        ptOffset = (addr.vaddr >> 12) & 0x1FF;
        DWORD_PTR PTE_Pointer = (PDE & PHY_ADDRESS_MASK) + (ptOffset * 8);
        PTE = this->pml4Base->readPhysicalAddress(sizeof(PTE), PTE_Pointer);
        if (!PTE) {
            return nullptr;
        }
        phyPageOffset = addr.vaddr & 0xFFF;
        pAddress = (PTE & PHY_ADDRESS_MASK) + phyPageOffset;
        return new PhysicalAddress(pAddress, this->pml4Base->getter());
    }

    PhysicalAddress *VirtualLayer::vtop(DWORD_PTR addr) const {
        DWORD_PTR PHY_ADDRESS_MASK = 0xFFFFFFFFFF000;
        WORD pml4Offset;
        DWORD_PTR PML4E;
        WORD pdptOffset;
        DWORD_PTR PDPE;
        WORD pdtOffset;
        DWORD_PTR PDE;
        WORD ptOffset;
        DWORD_PTR PTE;
        WORD phyPageOffset;
        DWORD_PTR pAddress;


        pml4Offset = (addr >> (12 + 9 + 9 + 9)) & 0x1FF;

        DWORD_PTR PML4_Pointer = ((this->pml4Base->paddr & PHY_ADDRESS_MASK) + (pml4Offset * 8));
        PML4E = this->pml4Base->readPhysicalAddress(sizeof(PML4E), PML4_Pointer);
        if (!PML4E) {
            return nullptr;
        }
        pdptOffset = (addr >> (12 + 9 + 9)) & 0x1FF;

        DWORD_PTR PDPE_Pointer = (PML4E & PHY_ADDRESS_MASK) + (pdptOffset * 8);
        PDPE = this->pml4Base->readPhysicalAddress(sizeof(PDPE), PDPE_Pointer);
        if (!PDPE) {
            return nullptr;
        }
        pdtOffset = (addr >> (12 + 9)) & 0x1FF;
        DWORD_PTR PDE_Pointer = (PDPE & PHY_ADDRESS_MASK) + (pdtOffset * 8);
        PDE = this->pml4Base->readPhysicalAddress(sizeof(PDE), PDE_Pointer);
        if (!PDE) {
            return nullptr;
        }
        if ((PDE & 0x80) != 0) {

            pAddress = ((PDE & 0xFFFFFFFE00000) + (addr & 0x1FFFFF));
            return new PhysicalAddress(pAddress, this->pml4Base->getter());
        }
        ptOffset = (addr >> 12) & 0x1FF;
        DWORD_PTR PTE_Pointer = (PDE & PHY_ADDRESS_MASK) + (ptOffset * 8);
        PTE = this->pml4Base->readPhysicalAddress(sizeof(PTE), PTE_Pointer);
        if (!PTE) {

            return nullptr;
        }

        phyPageOffset = addr & 0xFFF;
        pAddress = (PTE & PHY_ADDRESS_MASK) + phyPageOffset;
        return new PhysicalAddress(pAddress, this->pml4Base->getter());
    }

    VirtualAddress VirtualLayer::ptov(PhysicalAddress * paddr) {

    }


}