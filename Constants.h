//
// Created by sasha on 19.12.2022.
//

#ifndef NIR_CONSTANTS_H
#define NIR_CONSTANTS_H


enum {
    _offsetAddr = 0x2f0, //_LIST_ENTRY
    _offsetBase = 0x28,
    _offsetFilename = 0x450,
    _offsetPeb = 0x3f8,
    _fileNameLen = 16,
    _magic = 0x1c5654,
    _offsetVad = 0x658, //that addr belongs to SystemAS, windows moment, update - logical
    _offsetVadTag = -0xc,
    _physiscalPageSize = 0x1000,
    _mmpfnStructSize = 0x30

};

#endif //NIR_CONSTANTS_H

