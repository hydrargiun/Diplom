
#include "FileLayer.h"
namespace nir {
    Mapping *mapper(LPCTSTR);

    FileLayer::FileLayer(LPCSTR fname) {
        FileMap = mapper(fname);
        if (FileMap) {
            status = TRUE;
        }
    }

    Mapping *mapper(LPCTSTR fname) {
        auto *map = (Mapping *) malloc(sizeof(Mapping));
        map->hFile = CreateFile(fname, GENERIC_READ, 0, nullptr,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL, nullptr);
        if (map->hFile == INVALID_HANDLE_VALUE) {
            return nullptr;
        }
        map->fsize = GetFileSize(map->hFile, nullptr);
        if (map->fsize == INVALID_FILE_SIZE) {
            CloseHandle(map->hFile);
            return nullptr;
        }
        map->hMapping = CreateFileMapping(map->hFile, nullptr, PAGE_READONLY,
                                          0, 0, nullptr);
        if (map->hMapping == nullptr) {
            CloseHandle(map->hFile);
            return nullptr;
        }
        map->dataPtr = (unsigned char *) MapViewOfFile(map->hMapping,
                                                       FILE_MAP_READ,
                                                       0,
                                                       0,
                                                       map->fsize);
        if (map->dataPtr == nullptr) {
            CloseHandle(map->hMapping);
            CloseHandle(map->hFile);
            return nullptr;
        }
        return map;

    }

    FileLayer::~FileLayer() {
        UnmapViewOfFile(FileMap->dataPtr);
        CloseHandle(FileMap->hMapping);
        CloseHandle(FileMap->hFile);
    }
}