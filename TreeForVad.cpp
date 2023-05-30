//
// Created by sasha on 23.12.2022.
//

#include <iostream>
#include "TreeForVad.h"
namespace nir {
    Node::Node(VirtualAddress addr) {
        this->Addr = addr;
        this->m_left = nullptr;
        this->m_right = nullptr;
    }

    binary_tree::binary_tree(VirtualAddress root) {
        {
            m_root = new Node(root);
            m_size = 1;
        }
    }

    binary_tree::~binary_tree() {
        delete_tree(m_root);
    }

    void binary_tree::delete_tree(Node *curr) {
        if (curr) {
            delete_tree(curr->m_left);
            delete_tree(curr->m_right);
            delete curr;
        }
    }

    void binary_tree::print() {
        print_tree(m_root);
        std::cout << std::endl;
    }

    void binary_tree::print_tree(Node *curr) {
        if (curr && curr->Addr.vaddr) // Проверка на ненулевой указатель
        {
            std::cout<< curr->tag << " ";
            std::cout <<std::hex<< "0x"<<curr->Addr.vaddr<<"  ";
            if(curr->tag != "VadS"){
            std::cout<< "0x"<<curr->FirstPrototypePte.vaddr<<"  " << "0x"<<curr->LastContiguousPte.vaddr <<" "<< curr->filename << curr->FilenameAddr.vaddr<<std::endl;
                } else std::cout<<std::endl;
            print_tree(curr->m_left);
            print_tree(curr->m_right);
        }
    }

    bool binary_tree::findMapped(VirtualAddress addrToSearch) { // find all process, which use the same proto pte for shared files.
        bool res = false;
        find_mapped(addrToSearch, this->m_root, res);
        return res;
    }
    void binary_tree::find_mapped(VirtualAddress addrToSearch, Node *curr, bool &res){
        if (curr && curr->Addr.vaddr)
        {
            if(curr->tag != "VadS") {
                if (curr->FilenameAddr == addrToSearch) {
                    res = true;
                }
            }
            find_mapped(addrToSearch,curr->m_left, res);
            find_mapped(addrToSearch,curr->m_right, res);
        }
    }

    Node *binary_tree::findPtov(VirtualAddress addr) {
        Node * res = nullptr;
        find_ptov(this->m_root, &res, addr);
        return res;

    }

    void binary_tree::find_ptov(Node *curr, Node **res , VirtualAddress addr) {
        if (curr && curr->Addr.vaddr)
        {
            if(curr->tag != "VadS") {
                if (curr->FirstPrototypePte <= addr && curr->LastContiguousPte >= addr){
                    *res = curr;
                    return;
                }
            }
            find_ptov(curr->m_left, res, addr);
            find_ptov(curr->m_right, res, addr);
        }

    }

    void binary_tree::vadtree() {
        printvadtree(this->m_root);
    }

    void binary_tree::printvadtree(Node *curr) {
        if (curr && curr->Addr.vaddr) // Проверка на ненулевой указатель
        {
            std::cout<< curr->tag << " ";
            std::cout <<std::hex<< "0x"<<curr->Addr.vaddr<<"  ";
            std::cout<< "0x"<<curr->start.vaddr<<"  " << "0x"<<curr->end.vaddr << "Size " <<"0x"<<curr->end.vaddr-curr->start.vaddr<<std::endl;
            printvadtree(curr->m_left);
            printvadtree(curr->m_right);
        }
    }


}