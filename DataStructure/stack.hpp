/**
 *  @file stack.hpp
 *  @brief A stack class template for user specified Type.
 *  @version v1.0
 *
 *  @author Created by Bonzo on 2016/6/08.
 *  @author Copyright © 2016 Bonzo. All rights reserved.
 *
 **/

#ifndef stack_hpp
#define stack_hpp

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
class stack;

template <class Type>
ostream& operator << (ostream&, const stack<Type>&);

/** @defgroup group1 Class Template Declaration
 *  stack class template declaration
 *
 *  @{
 **/
/**
 * @class stack
 * @brief A stack class.
 * A template of stack, support subscripting.\n
 * Template variable: Type
 **/
template <class Type>
class stack: private linked_list<Type>{
    typedef primitive_node<Type>* pnode_ptr;
    
public:
    stack();
    stack(const stack&);
    int size() const;
    bool empty() const;
    void clear();
    void push(Type);
    Type pop();
    Type top();
    void print() const;
    
    Type operator [](int) const;    /**< Overload operator []. */
    friend ostream& operator << <Type> (ostream&, const stack<Type>&);  /**< Bound friend Operator <<. */
    
private:
    pnode_ptr& top_ptr;
};
/** @} */ // end of group1

/**
 * @fn linked_list<Type>::stack()
 * @brief Default constructor.
 * @see (const linked_list& rhs)
 **/
template <class Type>
stack<Type>::stack():top_ptr(linked_list<Type>::head){
    return;
}
    
/**
 * @fn linked_list<Type>::stack(const stack& rhs)
 * @brief Default constructor.
 * @see (const linked_list& rhs)
 **/
template<class Type>
stack<Type>::stack(const stack& rhs): linked_list<Type>(rhs), top_ptr(linked_list<Type>::head){
    return;
}
    
template<class Type>
int stack<Type>::size() const{
    return linked_list<Type>::size();
}

template<class Type>
bool stack<Type>::empty() const{
    return linked_list<Type>::empty();
}

template<class Type>
void stack<Type>::clear(){
    linked_list<Type>::clear();
}

template<class Type>
void stack<Type>::push(Type e){
    linked_list<Type>::insert(e, 0);
    return;
}
    
template<class Type>
Type stack<Type>::pop(){
    Type top_node = top();
    linked_list<Type>::erase(0);
    return top_node;
}

template<class Type>
Type stack<Type>::top(){
    return linked_list<Type>::node(0);
}

template<class Type>
void stack<Type>::print() const{
    if(empty())
        cout << "TOP -> []" << endl;
    else
        for(int i = 0; i < size(); i++){
            cout << (i ==  0 ? "TOP -> " : "       ");
            cout << '[' << linked_list<Type>::node(i) << ']' << endl;
        }
    
    return;
}

template<class Type>
Type stack<Type>::operator [](int indx) const{
    return linked_list<Type>::operator[](indx);
}

    
template <class Type>
ostream& operator << (ostream& os, const stack<Type>& rhs){
    rhs.print();
    return os;
}
}

#endif /* stack_hpp */
