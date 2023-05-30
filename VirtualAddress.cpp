
#include <cstdio>
#include "VirtualAddress.h"

namespace nir {
    VirtualAddress::VirtualAddress(DWORD_PTR addr) :
            vaddr(addr) {
    }

    VirtualAddress::VirtualAddress() {
        vaddr = 0;
    }

    bool VirtualAddress::operator==(const VirtualAddress &right) {
        if (vaddr == right.vaddr) {
            return true;
        } else return false;
    }

    bool operator<=(const VirtualAddress &lh, const VirtualAddress &rh) {
        if(lh.vaddr<= rh.vaddr){
            return true;
        } else return false;
    }
    bool operator>=(const VirtualAddress &lh, const VirtualAddress &rh) {
        if(lh.vaddr>= rh.vaddr){
            return true;
        } else return false;
    }
    bool operator<(const VirtualAddress &lh, const VirtualAddress &rh) {
        if(lh.vaddr< rh.vaddr){
            return true;
        } else return false;
    }
    bool operator>(const VirtualAddress &lh, const VirtualAddress &rh) {
        if(lh.vaddr> rh.vaddr){
            return true;
        } else return false;
    }


}