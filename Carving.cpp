//
// Created by sasha on 04.01.2023.
//

#include <fstream>
#include <iostream>
#include "Carving.h"

namespace nir {
    Carving::Carving(PhysicalLayer *layer, std::vector<VirtualLayer *> *vecProcesses, Mmpfn *table) : PhysicalLayer(
            layer), process(vecProcesses), mmpfn(table) {
        this->pages = new std::vector<unsigned char *>;
        unsigned char *tmpPtr = this->file->FileMap->dataPtr;
        auto stop = tmpPtr + this->file->FileMap->fsize;
        while (tmpPtr != stop) {
            this->pages->emplace_back(tmpPtr);
            tmpPtr = tmpPtr + this->block_size;
        }
    }

    Carving::~Carving() {
        delete pages;
    }

    void Carving::scan(Scaner *scaner) {
        for (auto page: *pages) {
            scaner->init(page);
        }
        for (auto hit: scaner->hit) {
            if (hit.offset + hit.len <= this->block_size) {
                auto buf = readClearData(hit.addr + hit.offset, hit.len);
                scaner->writeOut(buf, hit.len);
                delete buf;
            } else {
                DWORD_PTR fileOffset = hit.addr - this->file->FileMap->dataPtr;
                auto pteFromPfn = mmpfn->PteAddrFromPfn(fileOffset);
                pteFromPfn.vaddr += hit.offset;
                auto found = searchInProcess(pteFromPfn); //:(
            }
        }
    }

    unsigned char *Carving::readClearData(unsigned char *begin, int len) {
        auto buf = new unsigned char[len];
        memcpy(buf, begin, len);
        return buf;
    }

    std::vector<std::pair<Node *, VirtualLayer*>> Carving::searchInProcess(VirtualAddress addr) {
        std::vector<std::pair<Node *, VirtualLayer*>> resFound;
        for (auto proc: *process) {
            auto node = proc->Vad->findPtov(addr);
            if (node) {
                resFound.emplace_back(std::make_pair(node,proc));
                std::cout << resFound.end()->second->Eprocess->name->ReadStr(_fileNameLen)<<std::endl;
                std::cout << std::hex<< resFound.end()->first->FirstPrototypePte.vaddr <<" "<< 0xffffb68e1a602050 <<"  "<<resFound.end()->first->LastContiguousPte.vaddr<<std::endl;
            }
        }
        return resFound;

    }


} // nir