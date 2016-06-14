/**
 *  @file queue.hpp
 *  @brief A queue class template for user specified Type.
 *  @version v1.0
 *
 *  @author Created by Bonzo on 2016/6/09.
 *  @author Copyright © 2016 Bonzo. All rights reserved.
 *
 **/

#ifndef queue_hpp
#define queue_hpp

#include "linked_list.hpp"

/**
 * namespace bonzo.
 * @brief Customized namespace for this library.
 **/
namespace bonzo{
using bonzo::primitive_node;
using bonzo::linked_list;
using std::cout;
using std::ostream;

template <class Type>
class queue;

template <class Type>
ostream& operator << (ostream&, const queue<Type>&);

/** @defgroup group1 Class Template Declaration
 *  queue class template declaration
 *
 *  @{
 **/
/**
 * @class queue
 * @brief A queue class.
 * A template of queue, support subscripting.\n
 * Template variable: Type
 **/
template <class Type>
class queue: private linked_list<Type>{
    typedef primitive_node<Type>* pnode_ptr;

public:
    queue();
    queue(const queue&);
    int size() const;
    bool empty() const;
    void clear();
    void push(Type);
    Type pop();
    Type top();
    Type bottom();
    void print() const;
    
    Type operator [](int) const;    /**< Overload operator []. */
    friend ostream& operator << <Type> (ostream&, const queue<Type>&);  /**< Bound friend Operator <<. */
    
private:
    pnode_ptr& top_ptr;
    pnode_ptr& bottom_ptr;
};
/** @} */ // end of group1

/**
 * @fn linked_list<Type>::queue()
 * @brief Default constructor.
 * @see (const linked_list& rhs)
 **/
template <class Type>
queue<Type>::queue():top_ptr(linked_list<Type>::head), bottom_ptr(linked_list<Type>::tail){
    return;
}
    
/**
 * @fn linked_list<Type>::queue(const queue& rhs)
 * @brief Default constructor.
 * @see (const linked_list& rhs)
 **/
template<class Type>
queue<Type>::queue(const queue& rhs): linked_list<Type>(rhs), top_ptr(linked_list<Type>::head), bottom_ptr(linked_list<Type>::tail){
    return;
}
    
template<class Type>
int queue<Type>::size() const{
    return linked_list<Type>::size();
}

template<class Type>
bool queue<Type>::empty() const{
    return linked_list<Type>::empty();
}

template<class Type>
void queue<Type>::clear(){
    linked_list<Type>::clear();
}

template<class Type>
void queue<Type>::push(Type e){
    linked_list<Type>::insert(e);
    return;
}
    
template<class Type>
Type queue<Type>::pop(){
    Type top_node = top();
    linked_list<Type>::erase(0);
    return top_node;
}

template<class Type>
Type queue<Type>::top(){
    return linked_list<Type>::node(0);
}

template<class Type>
Type queue<Type>::bottom(){
    return linked_list<Type>::node(-1);
}

template<class Type>
void queue<Type>::print() const{
    
    if(empty())
        cout << "TOP -> [] <- BOTTOM" << endl;
    else if(size() == 1)
        cout << "TOP -> [" << linked_list<Type>::node(0) << "] <- BOTTOM" << endl;
    else
        for(int i = 0; i < size(); i++){
            cout << (i ==  0 ? "TOP    -> "
                             : (i == size() - 1 ? "BOTTOM -> "
                                                : "          "));
            cout << '[' << linked_list<Type>::node(i) << ']' << endl;
        }
    
    return;
}

template<class Type>
Type queue<Type>::operator [](int indx) const{
    return linked_list<Type>::operator[](indx);
}

    
template <class Type>
ostream& operator << (ostream& os, const queue<Type>& rhs){
    rhs.print();
    return os;
}
}

#endif /* queue_hpp */

