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
#include "dynamic_array.hpp"
#include "debug.hpp"
#include <vector>
/**
 * namespace bonzo.
 * @brief Customized namespace for this library.
 **/
namespace bonzo{
    
using bonzo::primitive_node;
using bonzo::basic_op;
using bonzo::dynamic_array;
using std::cout;
using std::ostream;
using std::vector;
    
template <class Type>
class linked_list;

template <class Type>
ostream& operator << (ostream&, const linked_list<Type>&);

/** @defgroup group1 Class Template Declaration
 *  dynamic_array class template declaration
 *
 *  @{
 **/
/**
 * @class linked_list
 * @brief A linked_list class.
 * A template of linked list, subscripting, push/pop/insert/erase node by index.\n
 * Template variable: Type
 **/    
template <class Type>
class linked_list : public basic_op<Type>{
    typedef void (linked_list::* alg_fp)(bool);
    
public:
    linked_list();
    linked_list(const linked_list&);
    ~linked_list();

    virtual void swap(int, int);            /**< Swap 2 nodes by index. */
    virtual void insert(Type);              /**< Insert a nodes at the end. */
    virtual void insert(Type, int);         /**< Insert a nodes by index. */
    virtual void erase(int = -1);           /**< Erase a node by indx. */
    virtual void append(Type);              /**< Insert a node at the end. */
    virtual vector<int> find(Type);         /**< Find nodes by value, should return a vector of index. */
    virtual void sort(alg_fp, bool = true); /**< Sort nodes, can be implemented with any algorithm. */
    virtual void reverse();                 /**< Reverse nodes by data structure's definition. */
    virtual void print() const;             /**< Print all nodes. */
    virtual Type operator [](int) const;    /**< Overload operator []. */

    linked_list operator + (const linked_list&);   /**< Operator +. */
    linked_list operator * (int);                  /**< Operator *. */
    linked_list& operator = (const linked_list&);  /**< Operator =. */
    linked_list& operator += (const linked_list&); /**< Operator +=. */
    linked_list& operator *= (int);                /**< Operator *=. */
    bool operator == (const linked_list&);         /**< Operator ==. */
    bool operator != (const linked_list&);         /**< Operator !=. */
    friend ostream& operator << <Type> (ostream&, const linked_list<Type>&);  /**< Bound friend Operator <<. */
    void clear(int = 0, int = -1);    /**< Clear whole linked list .*/
 
    void bubble_sort(bool = true);    /**< Sorting algorithm: bubble sort.*/
    void selection_sort(bool = true); /**< Sorting algorithm: selection sort.*/
    void insertion_sort(bool = true); /**< Sorting algorithm: insertion sort.*/
    void merge_sort(bool = true);     /**< Sorting algorithm: merge sort.*/
    void quick_sort(bool = true);     /**< Sorting algorithm: quick sort.*/


    
private:
    primitive_node<Type>* head;
    primitive_node<Type>* tail;
    dynamic_array<primitive_node<Type>*> nptr_a;
    vector<int>* find_v;
    alg_fp sort_alg;
    
    void copy(const linked_list&);   /**< Copy from another linked list.*/
    void connect_neighbor(primitive_node<Type>*, primitive_node<Type>*); /**< Connect 2 unconnected node to be neighbors.*/
    void new_find_v();               /**< Allocate an vector<int> for find() result. */
    void concat(const linked_list&); /**< Concat 2 linked list. */

    Type node(int) const;                                        /**< Get node value by index. */
    void __swap__(primitive_node<Type>*, primitive_node<Type>*); /**< Swap 2 nodes. */
    void __print__(bool = true, bool = true) const;              /**< Print utility. */
    void __merge_sort_recu__(int, int, bool = true);             /**< Merge sort by recusion. */
    void __merge_sort_loop__(int, int, bool = true);             /**< Merge sort by loop. */
    void __merge__(int, int, int, bool = true);                  /**< Merge utility for merge sort. */
    
    void __quick_sort_recu__(int, int, bool = true);             /**< Quick sort by recusion. */
    void __quick_sort_loop__(int, int, bool = true);             /**< Quick sort by loop. */
    int __partition__(int, int, bool);                           /**< Partition utility for quick sort. */

};
/** @} */ // end of group1

using bonzo::print_dbg_msg;
using bonzo::_DEBUG_ON;

/**
 * @fn linked_list<Type>::linked_list()
 * @brief Default constructor.
 * @see linked_list(const linked_list& rhs)
 **/
template <class Type>
linked_list<Type>::linked_list():head(nullptr), tail(nullptr), find_v(nullptr), sort_alg(&linked_list<Type>::selection_sort){
    return;
}

/**
 * @fn linked_list<Type>::linked_list()
 * @brief Copy constructor.
 * @see linked_list()
 **/
template <class Type>
linked_list<Type>::linked_list(const linked_list& rhs){
    copy(rhs);
    return;
}

/**
 * @fn linked_list<Type>::linked_list()
 * @brief Destructor.
 * @see ~linked_list()
 **/
template <class Type>
linked_list<Type>::~linked_list(){
    print_dbg_msg(_DEBUG_ON, "~linked_list() is called");
    clear();
    return;
}

    
// virtual definition
/**
 * @fn void linked_list<Type>::swap(int i, int j)
 * @brief Swap 2 nodes by index.
 * @param i Index of one node to swap.
 * @param j Index of another node to swap.
 **/
template <class Type>
void linked_list<Type>::swap(int i, int j){
    __swap__(nptr_a[i], nptr_a[j]);
    return;
}

/**
 * @fn void linked_list<Type>::insert(Type e)
 * @brief Swap 2 nodes by index.
 * @param e An element to be inserted.
 **/
template <class Type>
void linked_list<Type>::insert(Type e){
    insert(e, nptr_a.get_size());
    return;
}

/**
 * @fn void linked_list<Type>::insert(Type e, int indx)
 * @brief Insert a node by index.
 * @param e A node to be inserted.
 * @param indx The index where e will be inserted.
 **/
template <class Type>
void linked_list<Type>::insert(Type e, int indx){

    int tindx = nptr_a.trans_index(indx, true);
    primitive_node<Type>* curr = new primitive_node<Type>(e);
    if(nptr_a.get_size() == 0){
        nptr_a.push_back(curr);
        head = curr;
        tail = curr;
        return;
    }
    
    if(indx >= nptr_a.get_size()){
        connect_neighbor(tail, curr);
        tail = curr;
    }else if(tindx == 0){
        connect_neighbor(curr, head);
        head = curr;
    }else{
        connect_neighbor(curr, nptr_a[tindx]);
        connect_neighbor(nptr_a[tindx - 1], curr);
    }
    nptr_a.insert(curr, indx);
    return;
}

/**
 * @fn linked_list<Type>::erase(int indx)
 * @brief Erase a node by index.
 * @param indx The index of the node which will be erased.
 **/
template<class Type>
void linked_list<Type>::erase(int indx){
    if(nptr_a.get_size() == 0)
        return;

    int tindx = nptr_a.trans_index(indx, true);
    primitive_node<Type>* to_erase = nptr_a[tindx];
    
    if(nptr_a.get_size() == 1){
        head = nullptr;
        tail = nullptr;
    }else{
        if(tindx == 0)
            connect_neighbor(nullptr, nptr_a[tindx + 1]);
        else if(tindx == nptr_a.get_size() - 1)
            connect_neighbor(nptr_a[tindx - 1], nullptr);
        else
            connect_neighbor(nptr_a[tindx - 1], nptr_a[tindx + 1]);
    }
    
    delete to_erase;
    nptr_a.erase(tindx);
    
    return;
}
 
/**
 * @fn void linked_list<Type>::append(Type e)
 * @brief Insert a node at the end.
 * @param e An element to be inserted.
 **/
template<class Type>
void linked_list<Type>::append(Type e){
    insert(e);
    return;
}

/**
 * @fn vector<int> linked_list<Type>::find(Type e)
 * @brief Find nodes by value, should return a vector of index.
 * @param e The node value to be find.
 * @return find_v A vector<int> of index of the found nodes.
 **/
template<class Type>
vector<int> linked_list<Type>::find(Type e){
    new_find_v();
    
    for(int i = 0; nptr_a.in_range(i); i++)
        if(node(i) == e)
            find_v -> push_back(i);
    
    return *find_v;
}

/**
 * @fn void linked_list<Type>::sort(alg_fp alg, bool ascend)
 * @brief Sort nodes, can be implemented with any algorithm.
 * @param alg The function pointer of sorting algorithm implementation.
 * @param ascend Sorting by ascend or descend.
 **/
template<class Type>
void linked_list<Type>::sort(alg_fp alg, bool ascend){
    sort_alg = alg;
    
    (this->*sort_alg)(ascend);
    return;
}
    
/**
 * @fn void linked_list<Type>::reverse()
 * @brief Reverse nodes by data structure's definition.
 **/
template<class Type>
void linked_list<Type>::reverse(){
    primitive_node<Type>* tmp = nullptr;
    
    for(int i = 0; i < nptr_a.get_size(); i++){
        if(i == 0)
            tail = nptr_a[i];
        
        if(i == nptr_a.get_size() - 1)
            head = nptr_a[i];
        
        tmp = nptr_a[i] -> prev;
        nptr_a[i] -> prev = nptr_a[i] -> next;
        nptr_a[i] -> next = tmp;
    }
    
    nptr_a.reverse();
    return;
}

/**
 * @fn void linked_list<Type>::print() const
 * @brief Print all nodes.
 **/
template <class Type>
void linked_list<Type>::print() const{
    __print__(false, true);
    return;
}

/**
 * @fn Type linked_list<Type>::operator [](int indx) const
 * @brief Overload operator [].\n
 * Allowed to use negative index.
 * @param indx A subscript index of linked list, can be negative.
 * @return node(indx) An node value at index indx.
 **/
template<class Type>
Type linked_list<Type>::operator [](int indx) const{
    return node(indx);
}

// public method
    
//concate 2 linked_list.
template<class Type>
linked_list<Type> linked_list<Type>::operator + (const linked_list& rhs){
    linked_list<Type> tmp(*this);
    tmp.concat(rhs);
    return tmp;
}
    
//, repeat linked_list.
template<class Type>
linked_list<Type> linked_list<Type>::operator * (int n){
    linked_list<Type> tmp;
    for(int i = 0; i < n; i++){
        tmp.concat(*this);
    }
    
    return tmp;
}

template<class Type>
linked_list<Type>& linked_list<Type>::operator = (const linked_list& rhs){
    if(&rhs != this)
        copy(rhs);
    return *this;
}

template<class Type>
linked_list<Type>& linked_list<Type>::operator += (const linked_list& rhs){
    *this = *this + rhs;
    return *this;
}

template<class Type>
linked_list<Type>& linked_list<Type>::operator *= (int n){
    *this = *this * n;
    return *this;
    
}

template<class Type>
bool linked_list<Type>::operator == (const linked_list& rhs){
    if(&rhs == this)
        return true;
    else if(nptr_a.get_size() != rhs.nptr_a.get_size())
        return false;
    else{
        for(int i = 0; i < nptr_a.get_size(); i++){
            if(/*nptr_a[i] -> get_node()*/node(i) != /*rhs.nptr_a[i] -> get_node()*/rhs[i])
                return false;
        }
        
        return true;
    }
}
    
template<class Type>
bool linked_list<Type>::operator != (const linked_list& rhs){
    return !(*this == rhs);
}
    
    
template <class Type>
ostream& operator << (ostream& os, const linked_list<Type>& rhs){
    rhs.print();
    return os;
}

//Removes all nodes from the vector (which are destroyed), leaving the container with a size of 0.
template <class Type>
void linked_list<Type>::clear(int start, int end){
    start = nptr_a.trans_index(start);
    end = nptr_a.trans_index(end);
    
    if(start <= end && nptr_a.get_size() > 0)
        for(int i = end; i >= start; i--)
            if(i >= 0 && i < nptr_a.get_size()){
                erase(i);
            }
    return;
}
    
    
template <class Type>
void  linked_list<Type>::bubble_sort(bool ascend){
    // O(n^2)
    int sorted = nptr_a.get_size();
    for(int i = 0; i < nptr_a.get_size(); i++){
        for(int j = 0; j < sorted; j++)
            if(ascend && node(j) > node(j + 1))
                swap(j, j + 1);
            else if(!ascend && node(j) < node(j + 1))
                swap(j, j + 1);
        
        sorted--;
    }
    
    return;
}

template <class Type>
void  linked_list<Type>::selection_sort(bool ascend){
    // O(n^2)
    int sorted = nptr_a.get_size();
    for(int i = 0; i < nptr_a.get_size(); i++){
        int m = 0;
        for(int j = 0; j < sorted; j++)
            if(ascend && node(j) > node(m))
                m = j;
            else if(!ascend && node(j) < node(m))
                m = j;
        swap(m, sorted - 1);
        sorted--;
    }
    return;
}

template <class Type>
void  linked_list<Type>::insertion_sort(bool ascend){
    // O(n^2)
    int sorted = 0;
    for(int i = 0; i < nptr_a.get_size(); i++){
        for(int j = 0; j < sorted ; j++)
            if(ascend && node(i) < node(j)){
                insert(node(i), j);
                erase(i + 1);
                break;
            }
            else if(!ascend && node(i) > node(j)){
                insert(node(i), j);
                erase(i + 1);
                break;
            }
        
        sorted++;
    }
    return;
}

    
template <class Type>
void  linked_list<Type>::merge_sort(bool ascend){
    //__merge_sort_recu__(0, nptr_a.get_size() - 1, ascend);
    __merge_sort_loop__(0, nptr_a.get_size() - 1, ascend);
    return;
}

template <class Type>
void  linked_list<Type>::quick_sort(bool ascend){
    __quick_sort_loop__(0, nptr_a.get_size()-1, ascend);
    //__quick_sort_recu__(0, nptr_a.get_size()-1, ascend);
    return;
}

    
// private method
    
template <class Type>
void linked_list<Type>::copy(const linked_list& rhs){
    primitive_node<Type>* curr = nullptr;
    
    for(int i = 0; i < rhs.nptr_a.get_size(); i ++){
        if(i  >= nptr_a.get_size()){
            curr = new primitive_node<Type>();
            nptr_a.push_back(curr);
        }
        
        curr = nptr_a[i];
        curr -> set_node(rhs[i]);
    
        if(i == 0){
            head = curr;
            head -> prev = nullptr;
            continue;
        }
        else if(i == rhs.nptr_a.get_size() - 1){
            tail = curr;
            tail -> next = nullptr;
        }
        
        curr -> prev = nptr_a[i - 1];
        nptr_a[i - 1] -> next = curr;
        
    }
    
    clear(rhs.nptr_a.get_size(), nptr_a.get_size());
    
    return;
}

template <class Type>
void linked_list<Type>::connect_neighbor(primitive_node<Type>* front, primitive_node<Type>* back){
    if(front == nullptr){
        head = back;
        back -> prev = nullptr;
    }else if(back == nullptr){
        tail = front;
        front -> next = nullptr;
    }else{
        front -> next = back;
        back -> prev = front;
    }
    return;
}

template <class Type>
void linked_list<Type>::new_find_v(){
    if(find_v == nullptr)
        find_v = new vector<int>();
    else
        find_v -> clear();
    return;
}

template <class Type>
void  linked_list<Type>::concat(const linked_list& rhs){
    int rhs_size = rhs.nptr_a.get_size();
    for(int i = 0; i < rhs_size; i++)
        insert(/*rhs.nptr_a[i] -> get_node()*/ rhs[i]);
    return;
}

template <class Type>
Type linked_list<Type>::node(int indx) const{
    return nptr_a[indx] -> get_node();
}
    
template <class Type>
void linked_list<Type>::__swap__(primitive_node<Type>* node_a, primitive_node<Type>* node_b){
    /*
     * list                : n1 -> a -> n2 -> b -> n3 -> n4
     * node_a              : n1 <- a -> n2
     * node_b              :            n2 <- b -> n3
     *
     * swap                : n1 -> b -> n2 -> a -> n3 -> n4
     * node_a              :            n2 <- a -> n3
     * node_b              : n1 <- b -> n2
     */
    
    primitive_node<Type>* node_tmp1 = new primitive_node<Type>(*node_a);
    primitive_node<Type>* node_tmp2 = new primitive_node<Type>(*node_b);
    
    *node_a = *node_b;
    connect_neighbor(node_a, node_tmp1 -> next);
    connect_neighbor(node_tmp1 -> prev, node_a);
    
    *node_b = *node_tmp1;
    connect_neighbor(node_b, node_tmp2 -> next);
    connect_neighbor(node_tmp2 -> prev, node_b);
    
    delete node_tmp1;
    delete node_tmp2;
    return;
}
    
template <class Type>
void linked_list<Type>::__print__(bool by_indx, bool ascend) const{
    cout << (ascend ? "HEAD->" : "TAIL->");
    if(nptr_a.get_size() == 0){
        cout << "[]<-";
        cout << (ascend ? "TAIL" : "HEAD") << endl;
        return;
    }
    
    if(by_indx){
        int start = ascend ? 0 : -1;
        
        for(int i = start; nptr_a.in_range(i); ascend ? i++ : i--){
            cout << "[" << node(i)/*nptr_a[i] -> get_node()*/ << "]";
            cout << (ascend ? (nptr_a[i] -> next == nullptr ? "<-" : "->" ) : (nptr_a[i] -> prev == nullptr ? "<-" : "->" ));
            //i = ascend ? i + 1 : i - 1;
        }
    }else{
        primitive_node<Type>* curr = ascend ? head : tail;
        
        while (curr != nullptr){
            cout << "[" << curr -> get_node() << "]";
            cout << (ascend ? (curr == tail? "<-" : "->" ) : (curr == head ? "<-" : "->" ));
            curr = ascend ? (curr -> next) : (curr -> prev);
        }
    }

    cout << (ascend ? "TAIL" : "HEAD") << endl;
    return;
}
    
template <class Type>
void linked_list<Type>::__merge_sort_recu__(int p, int r, bool ascend){
    if (p >= r)
        return;
    
    int q = (p + r) / 2;
    __merge_sort_recu__(p, q, ascend);
    __merge_sort_recu__(q+1, r, ascend);
    __merge__(p, q, r, ascend);
}

template <class Type>
void linked_list<Type>::__merge_sort_loop__(int p, int r, bool ascend){
    if (p >= r)
        return;
    
    int n = nptr_a.get_size();
    int step = 2;
    
    while (n >= 1) {
        for(int i = 0; i <= n / 2 ; i ++){
            int p = i * step;
            int r = (p + step - 1);
            int q = (p + r) / 2;
            __merge__(p, q, r, ascend);
        }
        n /= 2;
        step *= 2;
    }
    return;
}
    
template <class Type>
void linked_list<Type>::__merge__(int p, int q, int r, bool ascend){
    int pqi = p;
    int qri = q+1;
    if(ascend){
        while(pqi <= q && qri <= r){
            if(node(pqi) <= node(qri))
                pqi += 1;
            else{
                insert(node(qri), pqi);
                erase(qri+1);
                pqi += 1;
                qri += 1;
                q += 1;
            }
        }
    }
    else{
        while(pqi <= q && qri <= r){
            if(node(pqi) >= node(qri))
                pqi += 1;
            else{
                insert(node(qri), pqi);
                erase(qri+1);
                pqi += 1;
                qri += 1;
                q += 1;
            }
        }
    }
    
    return;
    
}
    
template <class Type>
void linked_list<Type>::__quick_sort_recu__(int p, int r, bool ascend){
    if(p >= r)
        return;
    
    int m = __partition__(p, r, ascend);
    __quick_sort_recu__(p, m, ascend);
    __quick_sort_recu__(m + 1, r, ascend);
    return;
}

template <class Type>
void linked_list<Type>::__quick_sort_loop__(int p, int r, bool ascend){
    vector<int> q_vector;
    
    int leaves = 0;
    int pp = p;
    int pr = r;
    int t = 0;
    int q = 0;
    
    q = __partition__(pp, pr, ascend);
    cout << q << endl;
    cout << *this << endl;
    
    if(pp < q){
        q_vector.push_back(pp);
        q_vector.insert(q_vector.begin(), q);
    }
    else
        leaves += 1;
    
    if(q+1 < pr){
        q_vector.insert(q_vector.begin(), q+1);
        q_vector.insert(q_vector.begin(), pr);
    }
    else
        leaves += 1;
    
    vector<int>::iterator pit ;
    for(pit= q_vector.begin(); pit != q_vector.end(); pit++)
        cout << *pit << " ";
    cout << endl;
    
    t = int(q_vector.size());
    
    while (leaves < r){
        while(t != 0){
            pp = q_vector[q_vector.size() - 1];
            q_vector.pop_back();
            
            pr = q_vector[q_vector.size() - 1];
            q_vector.pop_back();
            t -= 2;
            
            
            q = __partition__(pp, pr, ascend);
            
            if(pp < q){
                q_vector.insert(q_vector.begin(), pp);
                q_vector.insert(q_vector.begin(), q);
            }
            else
                leaves += 1;
            
            if(q + 1 < pr){
                q_vector.insert(q_vector.begin(), q+1);
                q_vector.insert(q_vector.begin(), pr);
            }
            else
                leaves += 1;
            
            vector<int>::iterator pit ;
            for(pit= q_vector.begin(); pit != q_vector.end(); pit++)
                cout << *pit << " ";
            cout << endl;


        }
        t = int(q_vector.size());
    }
    
    
    return;
}

template <class Type>
int linked_list<Type>::linked_list<Type>::__partition__(int p, int r, bool ascend){
    int pivot = node(p);
    int pi = p;
    int qi = p;
    int ri = r;
    
    while(pi <= ri){
        if(ascend){
            if(node(pi) == pivot)
                pi += 1;
            else if(node(pi) < pivot){
                swap(qi, pi);
                qi += 1;
                pi += 1;
            }
            
            if(pi > ri)
                break;
            
            if(node(ri) > pivot)
                ri -= 1;
            else if(node(pi) > node(ri))
                swap(pi, ri);
        }
        else{
            if(node(pi) == pivot)
                pi += 1;
            else if(node(pi) > pivot){
                swap(qi, pi);
                qi += 1;
                pi += 1;
            }

            if(pi > ri)
                break;
            
            if(node(ri) < pivot)
                ri -= 1;
            else if(node(pi) < node(ri))
                swap(pi, ri);
            
        }
    }
    
    if(pi - 1 == r)
        return (p + r) / 2;
    else
        return pi - 1;
}

}



#endif /* linked_list_hpp */
