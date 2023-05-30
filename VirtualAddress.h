
#ifndef NIR_VIRTUALADDRESS_H
#define NIR_VIRTUALADDRESS_H

#include "windows.h"

namespace nir {
    class VirtualAddress {
    public:
        DWORD_PTR vaddr;
        VirtualAddress();
        explicit VirtualAddress(DWORD_PTR vaddr);
        bool operator==(const VirtualAddress&);
        friend bool operator<=(const VirtualAddress& lh, const VirtualAddress& rh);
        friend bool operator>=(const VirtualAddress& lh, const VirtualAddress& rh);
        friend bool operator<(const VirtualAddress& lh, const VirtualAddress& rh);
        friend bool operator>(const VirtualAddress& lh, const VirtualAddress& rh);
    };
}

#endif //NIR_VIRTUALADDRESS_H
