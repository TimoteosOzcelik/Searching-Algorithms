//
//  main.c
//  graph
//
//  Created by Timoteos Onur Ozcelik on 30.10.2018.
//  Copyright © 2018 Timoteos Onur Ozcelik. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "astar.h"

#define edges 25
#define squares_per_row 5

int main(int argc, const char * argv[]) {
    // CONSTRUCTION OF GRAPH, IT DEPENDS ON THE FLOOR
    Graph* sch_floor = init_graph(edges, squares_per_row);
    // ADD EDGE CONFIGURATION
    int i;
    for (i = 0; i < edges - 1; i++){
        if (i >= edges - squares_per_row) {
            add_edge(sch_floor, i, i+1, 1);
        }
        else if(!(i % squares_per_row)) {
            add_edge(sch_floor, i, i+1, 1);
            add_edge(sch_floor, i, i+squares_per_row, 1);
            add_edge(sch_floor, i, i+squares_per_row+1, 1);
        }
        else if(!((i+1) % squares_per_row)) {
            add_edge(sch_floor, i, i+squares_per_row-1, 1);
            add_edge(sch_floor, i, i+squares_per_row, 1);
        }
        else {
            add_edge(sch_floor, i, i+1, 1);
            add_edge(sch_floor, i, i+squares_per_row-1, 1);
            add_edge(sch_floor, i, i+squares_per_row, 1);
            add_edge(sch_floor, i, i+squares_per_row+1, 1);
        }
    }
    print_graph(sch_floor);
    
    a_star_algorithm(sch_floor, 10, 19);
    
    return 0;
}
