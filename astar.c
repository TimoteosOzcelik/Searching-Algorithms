//
//  graph.c
//  graph
//
//  Created by Timoteos Onur Ozcelik on 30.10.2018.
//  Copyright © 2018 Timoteos Onur Ozcelik. All rights reserved.
//

#include "astar.h"

// Construct graph heads - nodes ...
Graph* init_graph(int edges, int squares_per_row) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));

    int i;
    for (i = 0; i < edges; i++) {
        graph->heads[i] = (struct node*) malloc(sizeof(struct node));
        graph->heads[i]->next = NULL;
        graph->heads[i]->node_id = i;
        graph->heads[i]->x = 0.5 + i % squares_per_row;
        graph->heads[i]->y = 0.5 + (int)(i / squares_per_row);
    }
    return graph;
}

// Graph with edges ...
void add_edge(Graph* graph, int from, int to, int boolean) {
    struct node* temp = graph->heads[from];
    struct node* next = (struct node*) malloc(sizeof(struct node));

    while(temp->next != NULL) {
        temp = temp->next;
    }

    next->node_id = graph->heads[to]->node_id;
    next->x = graph->heads[to]->x;
    next->y = graph->heads[to]->y;
    next->next = NULL;

    temp->next = next;
    
    // For bidirectional graphs
    if (boolean) {
        boolean = 0;
        add_edge(graph, to, from, boolean);
    }

}

void print_graph(Graph* graph) {
    int i;
    for (i = 0; i < nodes; i++) {
        struct node* temp = graph->heads[i];
        while(temp->next != NULL) {
            printf("%d --> ", temp->node_id);
            temp = temp->next;
        }
        printf("%d \n",temp->node_id);
    }
}

// Initialization of path with from vertice.
void init_path(int from, struct traveled_node** pth) {
    struct traveled_node* temp = (struct traveled_node*) malloc(sizeof(struct traveled_node));
    temp->node_id = from;
    temp->from = -1;
    temp->g_cost = 0.0;
    temp->next = NULL;
    temp->previous = NULL;
    *pth = temp;
}

// Update path with new node
int update_path(struct traveled_node* pth, Graph* graph, int to) {
    struct traveled_node* tmp = pth;
    struct traveled_node* last;
    struct node* nod;
    
    float total_cost = FLT_MAX;
    float g_cost = FLT_MAX;
    int from = -2;
    int node_id = -1;
    float g_cost_btw;
    float h_cost;
    
    while (tmp != NULL) {
        nod = graph->heads[tmp->node_id]->next;
        while (nod != NULL) {
            if (is_not_node_in_path(tmp, nod)) {
                g_cost_btw = sqrtf(pow(graph->heads[tmp->node_id]->x - nod->x, 2) + pow(graph->heads[tmp->node_id]->y - nod->y, 2));
                h_cost = sqrtf(pow(graph->heads[to]->x - nod->x, 2) + pow(graph->heads[to]->y - nod->y, 2));
                if (tmp->g_cost + g_cost_btw + h_cost < total_cost) {
                    g_cost = tmp->g_cost + g_cost_btw;
                    total_cost = tmp->g_cost + g_cost_btw + h_cost;
                    from = graph->heads[tmp->node_id]->node_id;
                    node_id = nod->node_id;
                }
            }
            nod = nod->next;
        }
        last = tmp;
        tmp = tmp->next;
    }
    
    if (total_cost == FLT_MAX) {
        printf("No path found!\n");
        return 0;
    }
    else {
        tmp = pth;
        struct traveled_node* new_node = (struct traveled_node*) malloc(sizeof(struct traveled_node));
        new_node->node_id = node_id;
        new_node->from = from;
        new_node->g_cost = g_cost;
        new_node->next = NULL;
        new_node->previous = last;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = new_node;
        return 1;
    }
    
}

// Check if node is im path or not
int is_not_node_in_path(struct traveled_node* pth, struct node* nod) {
    struct traveled_node* temp = pth;
    while(temp != NULL) {
        if (temp->node_id == nod->node_id) {
            return 0;
        }
        temp = temp->next;
    }
    return 1;
}

int is_path_found(struct traveled_node* pth, int to) {
    struct traveled_node* temp = pth;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    if (temp->node_id == to)
        return 1;
    else
        return 0;
}

void print_path(struct traveled_node* pth) {
    struct traveled_node* temp = pth;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    int from = temp->from;
    printf("%d <-- ", temp->node_id);
    temp = temp->previous;

    while (temp->previous != NULL) {
        if (temp->node_id == from) {
            printf("%d <-- ", temp->node_id);
            from = temp->from;
        }
        temp = temp->previous;
    }
    printf("%d \n", temp->node_id);
}

void print_all_path(struct traveled_node* pth) {
    struct traveled_node* temp = pth;
    while (temp->next != NULL) {
        printf("%d --> ", temp->node_id);
        temp = temp->next;
    }
    printf("%d \n", temp->node_id);
}

void a_star_algorithm(Graph* graph, int from, int to) {
    struct traveled_node* pth;
    init_path(from, &pth);
    while (update_path(pth, graph, to)) {
        if (is_path_found(pth, to)) {
                printf("\n");
                printf("The found path from square %d to square %d: ", from, to);
                print_path(pth);
                break;
        }
    }
}
