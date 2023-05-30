//
// Created by sasha on 18.12.2022.
//

#ifndef NIR_VIRTUALLAYERSYSTEM_H
#define NIR_VIRTUALLAYERSYSTEM_H

#include <vector>
#include "VirtualLayer.h"
#include "TreeForVad.h"
namespace nir {
    class VirtualLayerSystem : public VirtualLayer {
    public:
        explicit VirtualLayerSystem(PhysicalAddress *pml4Base);
        Structures_ListEntry *List;
        void genList(VirtualAddress PsActiveProcessHead);
        std::vector<VirtualLayer *> ProcessVirtualLayers() const;
        binary_tree *GenVadForLayer(VirtualLayer *);

    private:
        void walk( nir_vad::RTL_BALANCED_NODE *, Node *, int &);
    };
}
#endif //NIR_VIRTUALLAYERSYSTEM_H
