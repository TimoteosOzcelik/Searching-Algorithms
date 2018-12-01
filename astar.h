//
//  graph.h
//  graph
//
//  Created by Timoteos Onur Ozcelik on 30.10.2018.
//  Copyright © 2018 Timoteos Onur Ozcelik. All rights reserved.
//

#ifndef graph_h
#define graph_h

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define nodes 25

struct node {
    int node_id;
    float x;
    float y;
    struct node* next;
};

typedef struct graph {
    struct node* heads[nodes];
}Graph;

struct traveled_node {
    int node_id;
    int from;
    float g_cost;
    struct traveled_node* next;
    struct traveled_node* previous;
};

Graph* init_graph(int edges, int squares_per_row);
void add_edge(Graph* graph, int from, int to, int boolean);
void print_graph(Graph* graph);

void init_path(int from, struct traveled_node** pth);
int update_path(struct traveled_node* pth, Graph* graph, int to);
int is_not_node_in_path(struct traveled_node* pth, struct node* nod);
int is_path_found(struct traveled_node* pth, int to) ;
void print_path(struct traveled_node* pth);
void print_all_path(struct traveled_node* pth);
void a_star_algorithm(Graph* graph, int from, int to);
#endif /* graph_h */
