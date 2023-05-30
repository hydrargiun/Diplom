
#include <cstdio> // should remove
#include "PhysicalLayer.h"

namespace nir {
    PhysicalLayer::PhysicalLayer(LPCSTR fname) {
        this->file = new FileLayer(fname);
    }

    DWORD_PTR PhysicalLayer::readPhysicalAddress(size_t size, DWORD_PTR paddr) const {
        if (paddr + size < file->FileMap->fsize) {
            auto *buf = new unsigned char[size];
            memcpy(buf, file->FileMap->dataPtr + paddr, size);
            DWORD_PTR result =
                    static_cast<DWORD_PTR>(buf[0]) |
                    static_cast<DWORD_PTR>(buf[1]) << 8 |
                    static_cast<DWORD_PTR>(buf[2]) << 16 |
                    static_cast<DWORD_PTR>(buf[3]) << 24 |
                    static_cast<DWORD_PTR>(buf[4]) << 32 |
                    static_cast<DWORD_PTR>(buf[5]) << 40 |
                    static_cast<DWORD_PTR>(buf[6]) << 48 |
                    static_cast<DWORD_PTR>(buf[7]) << 56;
            return result;
        }
        return 0;
    }

    unsigned char *PhysicalLayer::readNBytes(size_t size, DWORD_PTR paddr) const {
        if (paddr + size < file->FileMap->fsize) {
            auto buf = new unsigned char[size];
            memcpy(buf, this->file->FileMap->dataPtr + paddr, size);
            return buf;
        }
        return nullptr;
    }


    PhysicalLayer::PhysicalLayer(PhysicalLayer *layer) {
        this->file = layer->file;
    }

    PhysicalLayer *PhysicalLayer::getter() {
        return this;
    }

    PhysicalLayer::PhysicalLayer() {
        this->file = nullptr;
    }

}