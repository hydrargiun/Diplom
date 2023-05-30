//
// Created by sasha on 17.12.2022.
//

#ifndef NIR_STRUCTURES_H
#define NIR_STRUCTURES_H

#include "windows.h"
#include "VirtualAddress.h"
#include "PhysicalAddress.h"
#include "PhysicalLayer.h"
#include "Constants.h"
#include <vector>
namespace nir {
    typedef struct EPROCESS {
        PhysicalAddress *list_node;
        int offsetAddr = _offsetAddr;
        PhysicalAddress *addr;
        int offsetBase = _offsetBase;
        PhysicalAddress *base;
        int offsetName = _offsetFilename;
        PhysicalAddress *name;
        int offsetVad = _offsetVad;
        PhysicalAddress* vadRoot;


    } EPROCESS;


    typedef struct LINKS {   //FLINK And PLINK in mem
        PhysicalAddress *Flink;
        PhysicalAddress *Plink;
    } LINKS;

    typedef struct listEntry {
        PhysicalAddress *paddr; // pointer to LIST_ENTRY in mem points where FLINK And PLINK in mem
        LINKS *Links;
        listEntry *Next, *Prev;
    } listEntry;

    class Structures_ListEntry {
    public:
        VirtualAddress PsActiveProcessHead; //that address points where pointer to LIST_ENTRY in mem
        PhysicalAddress *PhisPsActiveProcessHead; //that address points where pointer to LIST_ENTRY in mem
        listEntry *listEntry64;

        std::vector<EPROCESS *> GetEprocess();

        explicit Structures_ListEntry(VirtualAddress);


    };



}

#endif //NIR_STRUCTURES_H
