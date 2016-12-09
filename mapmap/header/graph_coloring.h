/**
 * Copyright (C) 2016, Daniel Thuerck
 * TU Darmstadt - Graphics, Capture and Massively Parallel Computing
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license. See the LICENSE file for details.
 */

#ifndef __MAPMAP_HEADER_GRAPH_H_
#define __MAPMAP_HEADER_GRAPH_H_

#include "header/defines.h"
#include "header/graph.h" 

NS_MAPMAP_BEGIN

template<typename COSTTYPE>
class GraphColoring
{
public:
    GraphColoring();
    ~GraphColoring();

    virtual luint_t color(const Graph<COSTTYPE> * graph,
        std::vector<luint_t>& coloring) = 0;
};

NS_MAPMAP_END

#endif /* __MAPMAP_HEADER_GRAPH_H_ */