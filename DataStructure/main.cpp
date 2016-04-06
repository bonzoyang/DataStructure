//
//  main.cpp
//  DataStructure
//
//  Created by Bonzo on 2016/3/18.
//  Copyright © 2016年 Bonzo. All rights reserved.
//

#include <iostream>
#include "primitive_node.hpp"

using bonzo::primitive_node;
using std::cout;
using std::cin;
using std::endl;

int main(int argc, const char * argv[]) {
    cout << "primitive_node<int> a(1) :" << endl;
    primitive_node<int> a(1);
    cout << a;
    
    cout << "primitive_node<int> b(x) :" << endl;
    int x = 123;
    primitive_node<int> b(x);
    cout << b;
    
    cout << "primitive_node<int> c(a) :" << endl;
    primitive_node<int> c(a);
    cout << c;
    
    cout << "primitive_node<int> d :" << endl;
    primitive_node<int> d;
    cout << d;
    
    
    
    cin >> a >> b >> c >> d;
    cout << a << b << c << d;
    
    a.next = &b; b.prev = &a;
    b.next = &c; c.prev = &b;
    c.next = &d; d.prev = &c;
    
    primitive_node<int> * now_ptr = &a;
    cout << *now_ptr;
    cout << *(now_ptr->next);
    cout << *((now_ptr->next)->next);
    cout << *(((now_ptr->next)->next)->next);
    
    d = a;
    cout << d << a;
    cout << *d.next << *a.next;
    return 0;
}
