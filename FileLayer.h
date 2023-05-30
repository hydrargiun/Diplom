
#ifndef NIR_FILELAYER_H
#define NIR_FILELAYER_H
#include "windows.h"
namespace nir {
    struct Mapping {
        HANDLE hFile;
        HANDLE hMapping;
        size_t fsize;
        unsigned char *dataPtr;
    };

    class FileLayer {
    public:
        bool status;
        Mapping *FileMap;
        explicit FileLayer(LPCSTR);
        ~FileLayer();


    };
}
#endif //NIR_FILELAYER_H
