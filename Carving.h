//
// Created by sasha on 04.01.2023.
//

#ifndef NIR_CARVING_H
#define NIR_CARVING_H
#include <vector>
#include "PhysicalLayer.h"
#include "Constants.h"
#include "Scaner.h"
#include "Mmpfn.h"
#include "VirtualLayer.h"
#include "VirtualAddress.h"
#include "TreeForVad.h"
namespace nir {

    class Carving : public PhysicalLayer {
    private:
        int block_size = _physiscalPageSize;
        static unsigned char* readClearData(unsigned char*  begin, int);
        std::vector<std::pair<Node *,VirtualLayer*>> searchInProcess(VirtualAddress);
        std::vector<VirtualLayer*>* process;
        Mmpfn * mmpfn;

    public:
        std::vector<unsigned char *>* pages;
        Carving(PhysicalLayer * , std::vector<VirtualLayer*>*, Mmpfn*);
        void scan(Scaner*);
        ~Carving();


    };

} // nir

#endif //NIR_CARVING_H
