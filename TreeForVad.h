//
// Created by sasha on 23.12.2022.
//

#ifndef NIR_TREEFORVAD_H
#define NIR_TREEFORVAD_H
#include "Vad.h"
#include "VirtualAddress.h"
#include "PhysicalAddress.h"

namespace nir {
    class Node {
    public:
        VirtualAddress Addr;
        VirtualAddress FirstPrototypePte;
        VirtualAddress LastContiguousPte;
        VirtualAddress FilenameAddr;
        VirtualAddress start;
        VirtualAddress end;
        std::string filename;
        std::string tag;
        Node *m_left;
        Node *m_right;

        explicit Node(VirtualAddress);
    };

    class binary_tree {
    private:
        void print_tree(Node *);
        void printvadtree(Node *);
        void delete_tree(Node *);
        void find_mapped(VirtualAddress,Node *,bool &);
        void find_ptov(Node*, Node**, VirtualAddress addr);

    public:
        int m_size;
        Node *m_root;
        explicit binary_tree(VirtualAddress);
        ~binary_tree();
        void print();
        void vadtree();
        bool findMapped(VirtualAddress);
        Node * findPtov(VirtualAddress);
//        void insert(int);
//        void erase(int);
    };
}
#endif //NIR_TREEFORVAD_H
