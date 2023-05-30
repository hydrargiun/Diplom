
#ifndef NIR_PHYSICALLAYER_H
#define NIR_PHYSICALLAYER_H
#include "windows.h"
#include "FileLayer.h"
namespace nir {
    class PhysicalLayer{
    public:
        FileLayer* file;
        PhysicalLayer();
        explicit PhysicalLayer(LPCSTR fname);
        explicit PhysicalLayer(PhysicalLayer*);
        DWORD_PTR readPhysicalAddress(size_t size, DWORD_PTR) const;
        unsigned char* readNBytes(size_t size,  DWORD_PTR paddr) const;

        PhysicalLayer * getter();
    };

}
#endif //NIR_PHYSICALLAYER_H
