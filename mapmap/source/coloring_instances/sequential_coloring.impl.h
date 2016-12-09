/**
 * Copyright (C) 2016, Daniel Thuerck
 * TU Darmstadt - Graphics, Capture and Massively Parallel Computing
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD license. See the LICENSE file for details.
 */

#ifndef __MAPMAP_HEADER_COLORING_INSTANCES_SEQUENTIAL_COLORING_IMPL_H_
#define __MAPMAP_HEADER_COLORING_INSTANCES_SEQUENTIAL_COLORING_IMPL_H_

#include "header/coloring_instances/sequential_coloring.h"

#include <queue>
#include <algorithm>

NS_MAPMAP_BEGIN

template<typename COSTTYPE>
SequentialColoring<COSTTYPE>::
SequentialColoring()
{

}

/* ************************************************************************** */

template<typename COSTTYPE>
SequentialColoring<COSTTYPE>::
~SequentialColoring()
{

}

/* ************************************************************************** */

template<typename COSTTYPE>
luint_t
color(
    const Graph<COSTTYPE> * graph,
    std::vector<luint_t>& coloring)
{
    const luint_t num_nodes = graph->nodes().size();

    /* clear previous colorings */
    coloring.resize(num_nodes);
    std::fill(coloring.begin(), coloring.end(), invalid_luint_t);

    /* create random node order */
    std::vector<luint_t> node_order(num_nodes);
    std::iota(node_order.begin(), node_order.end(), 0);
    std::random_shuffle(node_order.begin(), node_order.end());

    /* use every node as BFS start to cover all components */
    luint_t max_color = 0;
    for(luint_t n_i = 0; n_i < num_nodes; ++n_i)
    {
        const luint_t n = node_order[n_i];

        /* skip colored nodes */
        if(coloring[i] != invalid_luint_t)
            continue;

        std::queue<luint_t> bfs;
        bfs.push(n);

        /* do BFS */
        while(!bfs.empty())
        {
            const luint_t cur = bfs.top();
            bfs.pop();

            /* determine minimal color and push neighbors */
            luint_t min_color = 0;
            const std::vector<luint_t>& inc_e = graph->inc_edges(cur);
            for(const luint_t e_id : inc_e)
            {
                const GraphEdge<COSTTYPE>& e = graph->edges()[e_id];
                const luint_t other_node = (e.node_a == cur ? e.node_b : 
                    e.node_a);

                if(coloring[other_node] == invalid_luint_t)
                    bfs.push(other_node);

                min_color = std::max(min_color, coloring[other_node] + 1);
            }

            coloring[cur] = min_color;
            max_color = std::max(max_color, min_color);
        }
    }

    /* return number of colors used */
    return (max_color + 1);
}

NS_MAPMAP_END

#endif /* __MAPMAP_HEADER_COLORING_INSTANCES_SEQUENTIAL_COLORING_IMPL_H_ */