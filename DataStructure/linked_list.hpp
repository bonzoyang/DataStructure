//
//  linked_list.hpp
//  DataStructure
//
//  Created by Bonzo on 2016/3/31.
//  Copyright © 2016年 Bonzo. All rights reserved.
//

#ifndef linked_list_hpp
#define linked_list_hpp

#include "primitive_node.hpp"
#include "basic_op.hpp"

namespace bonzo{
    
using bonzo::primitive_node;
using bonzo::basic_op;
using std::cout;
using std::cin;
using std::ostream;
using std::istream;
    
template <class Type>
    class linked_list;
    
template <class Type>
    ostream& operator << (ostream&, const linked_list<Type>&);
    
template <class Type>
    istream& operator >> (istream&, linked_list<Type>&);
    
template <class Type>
class linked_list : public basic_op<Type>{
public:
    linked_list();
    linked_list(const linked_list&);
    ~linked_list();
    
    linked_list operator = (const linked_list&);
    linked_list operator + (const linked_list&);
    linked_list operator * (int);
    linked_list operator += (const linked_list&);
    linked_list operator *= (int);
    bool operator == (const linked_list&);

    friend ostream& operator << (ostream&, const linked_list<Type>&);
    friend istream& operator >> (istream&, linked_list<Type>&);
    
private:
    static const int init_sz = 16;
    primitive_node<Type>* head;
    primitive_node<Type>* tail;
    
    int* index_a;
    primitive_node<Type>** pnptr_a;
    int curr_sz;
};

// constructor definition
template <class Type>
linked_list<Type>::linked_list():head(nullptr), tail(nullptr), index_a(nullptr), pnptr_a(nullptr), curr_sz(0){
    head = new primitive_node<Type>;
    tail = head;
    
    index_a = new int[init_sz];
    pnptr_a = new primitive_node<Type>*[init_sz];
}

template <class Type>
linked_list<Type>::linked_list(const linked_list& rhs){
    *this = rhs;
}

template <class Type>
linked_list<Type>::~linked_list(){
    for(int i = 0; i < curr_sz; i ++)
        delete pnptr_a[i];
    
    delete [] index_a;
    delete [] pnptr_a;
}

// virtual definition
/*template <class Type>
void linked_list<Type>::swap(primitive_node<Type>& node_a, primitive_node<Type>& node_b){
    
}*/

    
}



#endif /* linked_list_hpp */
