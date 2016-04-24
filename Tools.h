//
//  Tools.h
//  499_brand_new
//
//  Created by Chenyang Huang on 2015-08-30.
//  Copyright (c) 2015 Chenyang Huang. All rights reserved.
//  

#include <iostream>
using namespace std;

#ifndef _99_brand_new_Tools_h
#define _99_brand_new_Tools_h


// ============================================================
// a generic class which implemented stack of any types of data
// ============================================================
template <class T>
class Stack {
private:
    
    struct data_container
    {
        T this_data;
        data_container* next;
    };
    data_container* top_elem;
    data_container* elems_list;     // elements
    int number_of_elems = 0;
    data_container* container_to_push = new data_container;
    
public:
    
    void push(T to_push)
    {
        try {
            container_to_push->this_data = to_push;
            if ( number_of_elems > 0)
                container_to_push->next = top_elem;
            top_elem = container_to_push;
            number_of_elems ++;
        } catch (...)
        {
            //sthrow out_of_range("Stack<>::pop(): Push error");
        }
        
        
    };  // push element
    T pop()
    {
        if (number_of_elems == 0)
        {
            //throw out_of_range("Stack<>::pop(): empty stack");
        }
        
        try {
            T data_to_pop = top_elem->this_data;
            data_container* top_to_free = top_elem;
            top_elem = top_elem->next;
            free(top_to_free);
            number_of_elems --;
            return data_to_pop;
        } catch (...)
        {
            //throw out_of_range("Stack<>::pop(): Pop error");
        }
        
    };  // pop element
    
    
    bool is_empty() const
    {       // return true if empty.
        return ( number_of_elems == 0 );
    }
    
    
};

// NOTE: TO BE DONE
// ============================================================
// an self defined integer vector for fast access and saving memory
// By default the size of the vector is 512 integers, while not enough the
// memeory will be doubled. etc.
// ============================================================

//NOTE specifially for pointers , sizeof (void *);


#endif
