#pragma once
#include "BinarySearchNode.h"
namespace sca {
    struct Compare {
        using is_transparent = void;
        bool operator() (BinarySearchNode const* l, BinarySearchNode const* r) const {
            if (l->getFrequency() == r->getFrequency()) return l < r;
            return (*l < *r);
        }
    };
}