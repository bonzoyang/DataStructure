//
//  main.cpp
//  DataStructure
//
//  Created by Bonzo on 2016/3/18.
//  Copyright © 2016年 Bonzo. All rights reserved.
//
//#include "dynamic_array.hpp"


#include <iostream>
#include <iomanip>
//#include "primitive_node.hpp"
#include "linked_list.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "binary_tree.hpp"

using bonzo::dynamic_array;
using bonzo::primitive_node;
using bonzo::linked_list;
using bonzo::vector;
using bonzo::stack;
using bonzo::queue;
using bonzo::binary_tree;
using std::cout;
using std::cin;
using std::endl;
using std::setiosflags;

int main(int argc, const char * argv[]) {
/*
    cout << "primitive_node<int> a(23) :" << endl;
    primitive_node<int> a(23);
    cout << a.is_left_null()<<endl;
    

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
*/
    
/*
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
    
    
*/

/*
    int BB[10] = {1,2,3,4,5,6,7,8,9,10};
    dynamic_array<int> A;

    dynamic_array<int> B(BB, 10);
    std::cout <<"B: "<<B;
    dynamic_array<int> C(B);
    std::cout <<"C: "<<C;
    
    cout << B << endl;
    B.insert(9,4);
    cout << B <<endl;
*/
/*
    A.push_back(1);
    cout << A << endl;

    A.push_back(2);
    cout << A << endl;
    A.push_back(3);
    cout << A << endl;
    A.push_back(4);
    cout << A << endl;

    A.push_back(5);
    cout << A << endl;
    A.push_back(6);
    cout << A << endl;
    A.push_back(7);
    cout << A << endl;
    A.push_back(8);
    cout << A << endl;

    A.push_back(9);
    cout << A << endl;
    
    A.shrink_to_fit();
    cout << A << endl;
    
    A.push_back(10);
    cout << A << endl;
    
    cout << A+B<<endl;
    
    A.push_back(11);
    cout << A << endl;
    A.push_back(12);
    cout << A << endl;
    A.push_back(13);
    cout << A << endl;
    
    A.shrink_to_fit();
    cout << A << endl;
    
    A.push_back(14);
    cout << A << endl;
    A.push_back(15);
    cout << A << endl;
    A.push_back(16);
    cout << A << endl;
    
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;

    cout << "-----shrink1\n";
    A.shrink_to_fit();
    cout << A << endl;

    
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    A.pop_back();

    cout << "-----shrink2\n";
    A.shrink_to_fit();
    cout << A << endl;

    cout << "-----shrink3\n";
    A.shrink_to_fit();
    cout << A << endl;
    

    A.pop_back();
    cout << A << endl;

    A.pop_back();
    cout << "-----shrink4\n";
    A.shrink_to_fit();
    cout << A << endl;
    
    cout << "A+=A========>\n";
    cout << (A+=A) << endl;

    

    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    
    cout << "A.erase() ======>\n";
    A.erase();
    cout << A << endl;

    cout << "A.erase() ======>\n";
    A.erase();
    cout << A << endl;

    
    cout << "A.erase(10) ======>\n";
    A.erase(10);
    cout << A << endl;

    
    cout << "A.erase(7) ======>\n";
    A.erase(7);
    cout << A << endl;

    cout << "A.erase(-1) ======>\n";
    A.erase(-1);
    cout << A << endl;

    cout << "A.erase(0) ======>\n";
    A.erase(0);
    cout << A << endl;
    
    cout << "A.erase(1) ======>\n";
    A.erase(1);
    cout << A << endl;

    cout << "A.erase(3) ======>\n";
    A.erase(3);
    cout << A << endl;

    cout << "A.erase(2) ======>\n";
    A.erase(2);
    cout << A << endl;

    cout << "A.erase(100) ======>\n";
    A.erase(100);
    cout << A << endl;

    
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;

    A.insert(10, 1);
    cout << A << endl;

    A.insert(11, 3);
    cout << A << endl;

    A.insert(12, 0);
    cout << A << endl;
    
    A.insert(999999);
    cout << A << endl;
    
    A.reverse();
    cout << A << endl;
    
    A.insert(10,-999999);
    cout << A << endl;

    A.reverse();
    cout << A << endl;

    A.reverse();
    cout << A << endl;

    
    
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;
    A.pop_back();
    cout << A << endl;

    A.insert(999);
    cout << A << endl;
*/

/**********
    linked_list<int> BB;
    linked_list<int> BBtmp;
    BB.insert(1);
    cout << BB;
    BB.insert(2);
    cout << BB;
    BB.insert(3, 0);
    cout << BB;
    BB.insert(4, 90);
    cout << BB;
    BB.insert(5, 4);
    cout << BB;
    BB.insert(6, 4);

    cout << BB;
    BB.append(7);
    cout << BB;
    BB.append(8);
    cout << BB;
    cout << "BB.erase(20);" <<endl;
    BB.erase(20);
    cout << BB;
    BB.erase(0);
    cout << BB;
    BB.erase(5);
    cout << BB;


    cout << "BB + BB"<<endl;
    cout << BB*2;
    
    BB.reverse();
    cout << BB;
    BB = BB * 2;
    BB.reverse();
    cout << BB;
    
    //CC.insert(1);
    //CC.insert(90);
    //cout << "BB + CC"<<endl;
    //cout << BB + CC;
    cout << "BB = BB * 3 + BB * 2"<<endl;
    BB = BB * 1 + BB * 2;
    cout << BB;
    
    vector<int> find;
    find = BB.find(5);
    
    for (vector<int>::const_iterator iter = find.begin();
         iter != find.end(); ++iter)
        cout << *iter << " ";
    cout << endl;
    
    cout << BB[1] << endl;
    
    BB.swap(3, 7);
    cout << BB << endl;
    
    BBtmp = BB;
    cout << "bubble sort"<<endl;
    BB.sort(&linked_list<int>::bubble_sort, true);
    cout << BB << endl;
    
    BB = BBtmp;
    cout << "selection sort"<<endl;
    BB.sort(&linked_list<int>::selection_sort, true);
    cout << BB << endl;
    
    BB = BBtmp;
    cout << BB << endl;
    cout << "insertion sort"<<endl;
    BB.sort(&linked_list<int>::insertion_sort, true);
    cout << BB << endl;
    
    BB = BBtmp;
    cout << BB << endl;
    cout << "merge sort"<<endl;
    BB.sort(&linked_list<int>::merge_sort, true );
    cout << BB << endl;


    BB = BBtmp;
    cout << BB << endl;
    cout << "quick sort"<<endl;
    BB.sort(&linked_list<int>::quick_sort, true);
    cout << BB << endl;
*********/    
    

/*
    linked_list<int> CC;
    CC = BB;
    cout << "CC == BB"<<endl;
    cout << (CC == BB)<<endl;
    CC.erase();
    cout << "CC == BB"<<endl;
    cout << (CC == BB)<<endl;
    
    cout << "CC != BB"<<endl;
    cout << (CC != BB)<<endl;
    
    

    
    cout << "BB.clear()"<<endl;
    BB.clear();
    cout << BB;
    
    cout << "BB * 3"<<endl;
    cout << BB * 3;
    
    cout << "BB = BB * 100"<<endl;
    BB = BB * 100;
    cout << BB;
    
    cout << "BB *= 100"<<endl;
    BB *= 100;
    cout << BB;
    
    cout << "BB == BB"<<endl;
    cout << (BB == BB)<<endl;
*/
/*
    stack<int> SA;
    SA.push(1);
    SA.push(2);
    SA.push(3);
    
    stack<int> SB(SA);

    cout << "=======\n";
    cout << SA << endl;
    SA.clear();
    cout << SA <<endl;
    
    cout << "SB"<<endl;
    cout << SB<< endl;
    SB.push(999);
    SB.push(1000);
    cout << SB << endl;
    cout << SB.pop() << endl;
    
    queue<int> QA;
    QA.push(1);
    QA.push(2);
    QA.push(3);
    cout << QA << endl;
    QA.pop();
    cout << QA << endl;
    QA.pop();
    cout << QA << endl;
    QA.pop();
    cout << QA << endl;
*/
//    cout << std::setw(4) <<setiosflags( std::ios::left)<< 4<<std::setw(4) <<setiosflags( std::ios::right)<<9;


    binary_tree<int> BT;
    BT.insert(1, BT.begin());
    BT.insert(3, BT.begin());
    BT.insert(5, BT.begin());
    BT.insert(2, BT.begin()->left);
    BT.insert(4, BT.begin()->left);
    
    BT.insert(6, BT.begin()->right);
    BT.insert(8, BT.begin()->right);
    
    BT.insert(10, BT.begin()->left->right, false);
    BT.insert(20, BT.begin()->left->right->right, false);
    BT.insert(30, BT.begin()->left->right->right->right, false);
    
    cout << BT << endl;

    BT.insert(40, BT.begin()->left->left);
    BT.insert(50, BT.begin()->left->left->left);
    BT.insert(60, BT.begin()->left->left->left->left);
    cout << BT << endl;
    cout << BT << endl;    
    
    cout <<"===== BT2 =====" << endl;
    binary_tree<int> BT2(BT);
    cout << BT2 << endl;
    cout << (BT2 == BT)<<endl;
    
    BT2.insert(999, BT2.begin()->left->right);
    cout << BT2 << endl;
    cout << (BT == BT2)<<endl;
    



    
    return 0;
}
