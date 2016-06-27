//
//  Tricomp.h
//
//  Created by Chenyang Huang on 2015-08-26.
//  Copyright (c) 2015 Chenyang Huang. All rights reserved.
//

#ifndef _Tricomp_h
#define _Tricomp_h


#include "Tools.h"
using namespace std;

class graph
{
public:
    ~graph();
    graph(int number_of_vertices);
    void read_edges_from_file(string path_of_file);
    
    void dfs_1();
    void dfs_1_recur(int);
    
    void dfs_2();
    void dfs_2_recur(int w, int u);
    
    void adjust_adjacency_list(int root);
    
    void gen_split_comp();
    
    void coalesce();
    
    void print_adjacency_list();
    
private:
    
    // bool is_graph_start_from_zero = false;  // it depends on how your input file is.
    enum EDGE_TYPE
    {
        TREE_EDGE,
        FROND_EDGE,
        NOT_ASSIGNED
    };
    
    
    struct vertex // data structure for saving information of vertices
    {
        int vertex_id = -1;
        //bool is_visited = false;
        EDGE_TYPE edge_type = NOT_ASSIGNED; // the vertex only used for adjacency list thus the ( head node -> linked vertex )  can also reprensts a edge, where only need to put it on the linked vertex )
        vertex* in_frond_list = nullptr;
        //vertex * previous;
        vertex* next = nullptr; // i.e. the adjacency list of certain vertex.
    };
    
    struct vertex_info_struct
    {
        int dfs_number = -1;
        int low1 = -1;
        int low2 = -1;
        int low3 = -1;
        int parent = -1;
        bool is_visited;
        //bool is_tree_edge = false;
    };
    
    vertex** adjacency_list;
    vertex_info_struct* vertex_info;
    //int max_edges_size = 2; // doulbe when needed. reallocate.
    int max_vertices_size = 2;
    //int current_edges_size = 0; //
    int current_vertices_size = 0;
    int time; // used by DFS1

    int count; // used by DFS2
    vertex** out_list;
    vertex** in_frond_list;
};

#endif