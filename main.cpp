//
//  main.cpp
//  499_brand_new
//
//  Created by Chenyang Huang on 2015-08-26.
//  Copyright (c) 2015 Chenyang Huang. All rights reserved.
//

#include <iostream>
#include "Tricomp.h"
int main(int argc, const char * argv[]) {

    std::cout << argv[0];
    graph * graph_instance = new graph(13);
    graph_instance->read_edges_from_file("/home/chenyang/ClionProjects/"
                                                 "TriconnectedComponent/test.txt");
    // FIRST STEP, CHECK IF THE GRAPH IS SIMPLE GRAPH

    // SECOND STEP, PERFORM THE FIRST DFS,,, ? NOT IMPLEMENTED
    graph_instance->dfs_1();
    
    graph_instance->print_adjacency_list();
    
    // adjust the adjacency list
    graph_instance->adjust_adjacency_list(1);
    
    
    // THIRD STEP,
    graph_instance->dfs_2();


    
    return 0;
}
