//
// Created by sasha on 17.12.2022.
//

#include "Structures.h"
namespace nir{

    Structures_ListEntry::Structures_ListEntry(VirtualAddress vaddr) {
        this->PsActiveProcessHead = vaddr;
        this->PhisPsActiveProcessHead = nullptr;
        this->listEntry64 = nullptr;
    }

    std::vector<EPROCESS *> Structures_ListEntry::GetEprocess() {
        std::vector<EPROCESS *> eprocessVector;
        listEntry * ptr = this->listEntry64;
        while (ptr){
            auto * eprocess = new EPROCESS;
            eprocess->list_node = ptr->Links->Flink;
            eprocess->addr = *eprocess->list_node - eprocess->offsetAddr;
            eprocess->base = *eprocess->addr + eprocess->offsetBase;
            eprocess->name= *eprocess->addr + eprocess->offsetName;
            eprocess->vadRoot= *eprocess->addr + eprocess->offsetVad;
            eprocessVector.push_back(eprocess);
            ptr=ptr->Next;
        }
        return eprocessVector;
    }

}