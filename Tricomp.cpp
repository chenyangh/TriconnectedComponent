//
//  Tricomp.cpp
//  499_brand_new
//
//  Created by Chenyang Huang on 2015-08-26.
//  Copyright (c) 2015 Chenyang Huang. All rights reserved.
//

#include "Tricomp.h"
#include <iostream>
#include <fstream>
using namespace std;
// code can be improved by given size of the graph
graph::graph(int number_of_vertices)
{
    
}
graph::~graph()
{
    // must clean
}

void graph::print_adjacency_list()
{
    cout << "The current adjacency list is(starting from one):" << endl;
    for ( int i = 0 ; i <= current_vertices_size  ; i ++)
    {
        vertex* current_vertex = adjacency_list[i];
        
        if ( current_vertex->next != nullptr)
        {
            cout << current_vertex->vertex_id  << "->" ;
            while ( current_vertex->next != nullptr )
            {
                current_vertex = current_vertex->next;
                cout << current_vertex->vertex_id << "(" << ( current_vertex->edge_type == TREE_EDGE ? "T" : ( current_vertex->edge_type == FROND_EDGE ? "F" : "NOT ASSIGNED")) << ")"  ;
                if (current_vertex->next != nullptr)
                    cout << "->" ;
                
            }
            cout << endl;
        }
    }
    cout << " =============END==============" << endl;
    
//    // print out vertex info here. 
//    cout << "low1, low2, dfs_number are:" << endl;
//    for ( int i = 1 ; i <= current_vertices_size ; i ++ )
//    {
//        cout << "vertex " << i  << ": dfs_number = " << vertex_info[i].dfs_number <<  "; low 1 = " << vertex_info[i].low1 <<
//        "; low 2 = " << vertex_info[i].low2 << "; father = " << vertex_info[i].father << endl;
//    }
}



// =====================================================
// This function automaticall detected size of graph whith dynamically allocation of memory
// NOTE that the vertices ID start from 0
// Current stratage is double the maximum size when needed, this could be improved.
// =====================================================
void graph::read_edges_from_file(string path_of_file)
{
    try {
        std::ifstream in_file(path_of_file);
        int first, second;
        adjacency_list = ( vertex ** ) malloc( sizeof(vertex** ) * max_vertices_size );
        for ( int i = 0 ; i < max_vertices_size ; i ++ )
        {
            adjacency_list[i] =  new vertex;
            adjacency_list[i]->vertex_id = i;
        }
        while( in_file>>first>>second )
        {
            // NOTE: Follwing - 1 depends on the input file
            int from  = first ;
            int to = second ;
            
            // updating edge and vertices size
            current_vertices_size = from > current_vertices_size ? from  : current_vertices_size ;
            
            if ( current_vertices_size >= max_vertices_size ) // dealling with maximum vertex size
            {
                adjacency_list = (vertex ** ) realloc(adjacency_list, sizeof(vertex** ) * max_vertices_size * 2 );
                for ( int i = max_vertices_size ; i < max_vertices_size * 2 ; i ++ )
                {
                    adjacency_list[i] =  new vertex;
                    adjacency_list[i]->vertex_id = i;
                }
                max_vertices_size *= 2;
            }
            
            vertex* new_vertex = new vertex;
            new_vertex->vertex_id = to;
            
            // appending new adges, insert after head node
            if (adjacency_list[from]->next != nullptr)
            {
                new_vertex->next = adjacency_list[from]->next;
                adjacency_list[from]->next = new_vertex;
            }
            else
            {
                adjacency_list[from]->next = new_vertex;
            }
        }
        
    } catch ( std::exception &exc ) {
        cerr << exc.what();
    }
}

//=============================================
// Perform a first DFS to calcuate LOW1 LOW2 and adjust the adjacancy list
// to make the first child be the fist entry in the list
// refered to Tarjan(1973) and changed
// recursion to iteration
// first implement the recursion virsion
//=============================================
void graph::dfs_1()
{
    // initial variabels
    vertex_info  = (vertex_info_struct * ) malloc( ( current_vertices_size + 1) * sizeof(vertex_info_struct) );
    if ( vertex_info == nullptr)
    {
        cerr << " NO ENOUGH MEMORY!";
        exit(1);
    }
    for ( int i = 0 ; i < ( current_vertices_size + 1)  ; i ++ )
    {
        vertex_info[i].low1 = vertex_info[i].low2 = 0;
        vertex_info[i].dfs_number = vertex_info[i].parent = 0;
    }
    time = 0;
    int root = 1;
    dfs_1_recur(root);
    
    // has to adjust the adjacency list
    
}

void graph::dfs_1_recur(int v)
{
    vertex_info[v].dfs_number = time = time + 1;
    vertex_info[v].low1 = vertex_info[v].low2 = vertex_info[v].dfs_number;
    
    vertex * cur_ver = adjacency_list[v]->next;
    while (cur_ver != nullptr) // FOR w in the adjacency list of v DO
    {
        int w = cur_ver->vertex_id;
        if ( vertex_info[w].dfs_number == 0 )
        {
           // NOTE  mark vw as a tree edge in P;
            cur_ver->edge_type = TREE_EDGE;
            vertex_info[w].parent = v;
            dfs_1_recur(w);
            if ( vertex_info[w].low1 < vertex_info[v].low1 )
            {
                vertex_info[v].low2 =  vertex_info[v].low1 < vertex_info[w].low2  ? vertex_info[v].low1 : vertex_info[w].low2; //LOWPT2(v) = MIN{LOWPT1(v), LOWPT2(w)};
                vertex_info[v].low1 = vertex_info[w].low1;
            }
            else if ( vertex_info[w].low1 == vertex_info[v].low1 ){
                //vertex_info[v].low2 = vertex_info[w].low1;
                vertex_info[v].low2 = vertex_info[v].low2 < vertex_info[w].low2  ? vertex_info[v].low2 : vertex_info[w].low2;
            }
            
            else
                vertex_info[v].low2 = vertex_info[v].low2 < vertex_info[w].low1  ? vertex_info[v].low2 : vertex_info[w].low1; //LOWPT2(v) = MIN{LOWPT2(v), LOWPT1(w)};
        }
        else
        {
            // NOTE mark vw as a frond in P;
            cur_ver->edge_type = FROND_EDGE;
            if ( vertex_info[w].dfs_number < vertex_info[v].low1 )
            {
                vertex_info[v].low2 = vertex_info[v].low1;
                vertex_info[v].low1 = vertex_info[w].dfs_number;
            }
            else if ( vertex_info[w].dfs_number > vertex_info[v].low1 )
                vertex_info[v].low2 =  vertex_info[v].low2 < vertex_info[w].dfs_number ? vertex_info[v].low2 : vertex_info[w].dfs_number; //LOWPT2(v) = MIN{LOWPT2(v), NUMBER(w)};
        }
        cur_ver = cur_ver->next;
    }
}


// =======================================================
// As descripted in Tsin 's paper(Decomposing a Multigraph into Split Components (2012)),
// first child or first frond has to be moved forward to the first place of a adjacency list
// My implementation to do so has a a worst case of 2|E| which might not be good.
// NOTE: this can be improved to |E| if the adjacency list is doulbe linked
// =======================================================
void graph::adjust_adjacency_list(int u_input)
{
    for ( int u = u_input ; u <= current_vertices_size ; u ++) // travse the adjacency list.  o(|V|+|E|);
    {
        // FIRST SCAN
        vertex * cur_ver = adjacency_list[u];
        vertex * prev_ver = cur_ver; // the adjacency list is stored as single linked, when doing adjust, a previous vertex is needed.
        cur_ver = cur_ver->next;
        
        
        bool is_first_child_exist = false;
        
        while ( cur_ver != nullptr) {
            // should check first child FIRST, if no such child, go for frond
            int v = cur_ver->vertex_id;
            if ( vertex_info[u].low1 == vertex_info[v].low1 && cur_ver->edge_type == TREE_EDGE ) // first child
            {
                prev_ver->next = cur_ver->next;
                cur_ver->next = adjacency_list[u]->next;
                adjacency_list[u]->next = cur_ver;
                is_first_child_exist = true;
                break; // once found, quit loop
            }             prev_ver = cur_ver;
            cur_ver = cur_ver->next;
        }
        
        // SCOND SCAN
        if ( is_first_child_exist == true )
            continue;
        
        cur_ver = adjacency_list[u];
        prev_ver = cur_ver; // the adjacency list is stored as single linked, when doing adjust, a previous vertex is needed.
        cur_ver = cur_ver->next;
        
        while ( cur_ver != nullptr) {
            int v = cur_ver->vertex_id;
            if ( vertex_info[u].low1 == vertex_info[v].dfs_number && cur_ver->edge_type == FROND_EDGE )
            {
                prev_ver->next = cur_ver->next;
                cur_ver->next = adjacency_list[u]->next;
                adjacency_list[u]->next = cur_ver;
                break; // once found, quit loop
            }
            cur_ver = cur_ver->next;
        }
    }
}

// ==================================================
// Corresponds to the DFS algorithm shown on Tsin's (2012) Thesis.
//


void graph::dfs_2()
{
    count = 1;
    for ( int i = 1 ; i <= current_vertices_size ; i ++) // make every vertex as unvisited
        vertex_info[i].is_visited = false;
    dfs_2_recur(1, 0);
    
    out_frond_list = (vertex **) malloc( ( current_vertices_size + 1) * sizeof(vertex*));
    in_frond_list = (vertex **) malloc( ( current_vertices_size + 1) * sizeof(vertex*));
    
}


void graph::dfs_2_recur(int w, int v)
{
    vertex_info[w].is_visited = true;
    vertex_info[w].dfs_number = count;
    count ++;
    vertex_info[w].parent = v;
    vertex_info[w].low2 = vertex_info[w].low3 = vertex_info[w].dfs_number;
    
    // Pw = w; // NOT DONE // conserdering design of data structure
    
    in_frond_list[w] = new vertex;
    out_frond_list[w] = new vertex;
    
    vertex* cur_ver = adjacency_list[w]->next;
    
    while (cur_ver != nullptr)
    {
        int u = cur_ver->vertex_id;
        
        if ( cur_ver->edge_type == TREE_EDGE )
        {
            // REPRESENT EDGES
        }
        
        dfs_2_recur(u, w);
        
        // P = gen_split_comp();
        
        // ...
        
        cur_ver = cur_ver->next;
    }
    
    
}

void graph::gen_split_comp()
{
       
    
    
}

void graph::coalesce()
{
    
}





