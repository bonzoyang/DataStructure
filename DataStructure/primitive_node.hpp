/**
 *  @file primitive_node.hpp
 *  @brief A primitive node class for all data structure.
 *  @version v1.0
 *
 *  @author Created by Bonzo on 2016/3/18.
 *  @author Copyright © 2016 Bonzo. All rights reserved.
 *
 **/

#ifndef primitive_node_hpp
#define primitive_node_hpp

#include <iostream>
#include "debug.hpp"
/**
 * namespace bonzo.
 * @brief Customized namespace for this library.
 **/
namespace bonzo{

using std::ostream;
using std::istream;

template <class Type>
class primitive_node;

template <class Type>
ostream& operator << (ostream&, const primitive_node<Type>&);

template <class Type>
istream& operator >> (istream&, primitive_node<Type>&);
    
/** @defgroup group1 Class Template Declaration
 *  primitive_node class template declaration
 *
 *  @{
 **/
/**
 * @class primitive_node
 * @brief A primitive_node class.
 * A template of primitive node, with 2 pointers pointing to previous / next element.\n
 * Template variable: Type
 **/
template <class Type>
class primitive_node{
public:
    primitive_node* prev;   /**< A primitive_node pointer, point to previous node. */
    primitive_node* next;   /**< A primitive_node pointer, point to next node. */
    primitive_node* parent; /**< A primitive_node pointer, point to parent node. */
    primitive_node*& left;  /**< An alias to prev, point to left child in tree structure. */
    primitive_node*& right; /**< An alias to next, point to right child in tree structure. */

    primitive_node();                      /**< Default constructor. */
    primitive_node(const Type&);           /**< Normal constructor. */
    primitive_node(const primitive_node&); /**< Copy constructor. */
    
    /* unbound friend function template
    template <class T>
        friend ostream& operator << (ostream&, const primitive_node<T>&);
    */
    
    friend ostream& operator << <Type> (ostream&, const primitive_node&); /**< Bound friend operator <<.*/
    friend istream& operator >> <Type> (istream&, primitive_node&);       /**< Bound friend operator >>.*/
    primitive_node& operator = (const primitive_node&);                   /**< Operator =.*/
    bool operator == (const primitive_node&);                             /**< Operator ==.*/
    bool operator != (const primitive_node&);                             /**< Operator !=.*/
    
    ~primitive_node();
    void set_node(Type);         /**< Set node value. */
    Type get_node() const;       /**< Get node value. */
    
    inline bool is_prev_null();  /**< Check if prev is a nullptr. */
    inline bool is_next_null();  /**< Check if next is a nullptr. */
    inline bool is_left_null();  /**< Alias to is_prev_null. */
    inline bool is_right_null(); /**< Alias to is_next_null. */
    
//    bool (primitive_node::* is_left_null) ();  // usage: (x.*x.is_left_null)()
//    bool (primitive_node::* is_right_null) (); // usage: (x.*x.is_right_null)()
    
private:
    Type node; /**< Data node. */
};
/** @} */ // end of group1

/** @defgroup group2 Template Definition
 *  Class template must be defined in .hpp to avoid link error.
 *
 *  @{
 **/
using bonzo::print_dbg_msg;
using bonzo::_DEBUG_ON;

/**
 * @fn primitive_node<Type>::primitive_node()
 * @brief Default constructor.
 * @see primitive_node(const Type&)
 * @see primitive_node(const primitive_node&)
 **/
template <class Type>
primitive_node<Type>::primitive_node() : prev(nullptr), next(nullptr), parent(nullptr), left(prev), right(next)/*, is_left_null(&primitive_node::is_prev_null), is_right_null(&primitive_node::is_next_null)*/{
    print_dbg_msg(_DEBUG_ON, "primitive_node() is called");
    return;
};
    
/**
 * @fn primitive_node<Type>::primitive_node(const Type& rhs)
 * @brief Normal constructor.
 * @param rhs Initialize node from rhs.
 * @see primitive_node()
 * @see primitive_node(const primitive_node&)
 **/
template <class Type>
primitive_node<Type>::primitive_node(const Type& rhs) : prev(nullptr), next(nullptr), parent(nullptr), left(prev), right(next)/*, is_left_null(&primitive_node::is_prev_null), is_right_null(&primitive_node::is_next_null)*/{
    node = rhs;
    print_dbg_msg(_DEBUG_ON, "primitive_node(const Type&) is called");
    return;
};

/**
 * @fn primitive_node<Type>::primitive_node(const primitive_node& rhs)
 * @brief Copy constructor.
 * @param rhs A reference to another primitive_node. Memberwisely initialize from rhs.
 * @see primitive_node()
 * @see primitive_node(const Type&)
 **/
template <class Type>
primitive_node<Type>::primitive_node(const primitive_node<Type>& rhs) : left(prev), right(next)/*, is_left_null(&primitive_node::is_prev_null), is_right_null(&primitive_node::is_next_null)*/{
    node = rhs.node;
    prev = rhs.prev;
    next = rhs.next;
    parent = rhs.next;
    print_dbg_msg(_DEBUG_ON, "primitive_node(const primitive_node&) is called");
    return;
};

template <class Type>
primitive_node<Type>::~primitive_node(){
    print_dbg_msg(_DEBUG_ON, "~primitive_node() is called");
    return;
}

/**
 * @fn primitive_node<Type>::set_node(Type rhs)
 * @brief Set node value by rhs.
 * @param rhs The value being assigned to node. Call by value.
 **/
template <class Type>
void primitive_node<Type>::set_node(Type rhs){
    node = rhs;
    return;
}

/**
 * @fn primitive_node<Type>::get_node()
 * @brief Get node value.
 * @return node value. Return by copy.
 **/
template <class Type>
Type primitive_node<Type>::get_node() const{
    return node;
}

/**
 * @fn bool primitive_node<Type>::is_prev_null()
 * @brief Check if prev is nullptr.
 * @retval true prev is a nullptr.
 * @retval false prev is not a nullptr.
 **/
template <class Type>
inline bool primitive_node<Type>::is_prev_null(){
    return prev == nullptr;
}

/**
 * @fn bool primitive_node<Type>::is_next_null()
 * @brief Check if next is nullptr.
 * @retval true next is a nullptr.
 * @retval false next is not a nullptr.
 **/
template <class Type>
inline bool primitive_node<Type>::is_next_null(){
    return next == nullptr;
}

/**
 * @fn bool primitive_node<Type>::is_left_null()
 * @brief Alias to is_prev_null.
 * @retval true prev is a nullptr.
 * @retval false prev is not a nullptr.
**/
template <class Type>
inline bool primitive_node<Type>::is_left_null(){
    return is_prev_null();
}
    
/**
 * @fn bool primitive_node<Type>::is_next_null()
 * @brief Alias to is_next_null.
 * @retval true next is a nullptr.
 * @retval false next is not a nullptr.
 **/
template <class Type>
inline bool primitive_node<Type>::is_right_null(){
    return is_next_null();
}

    
/**
 * @fn ostream& operator << (ostream& os, const primitive_node<Type>& rhs)
 * @brief Bound friend function template. Overload operator <<.
 * @param os An ostream instance to stream output, usually cout.
 * @param rhs A reference to primitive_node, which will be print out.
 * @return os An ostream instance.
 **/
template <class Type>
ostream& operator << (ostream& os, const primitive_node<Type>& rhs){
    os << rhs.node;
    return os;
}

/**
 * @fn istream& operator >> (istream& is, primitive_node<Type>& lhs)
 * @brief Bound friend function template. Overload operator >>.
 * @param is An istream instance to input stream, usually cin.
 * @param lhs A reference to primitive_node, which will be written by input.
 * @return is An istream instance.
 **/
template <typename Type>
istream& operator >> (istream& is, primitive_node<Type>& lhs){
    is >> lhs.node;
    return is;
}
 
/**
 * @fn primitive_node<Type> primitive_node<Type>::operator = (const primitive_node<Type>& rhs)
 * @brief Overload operator =.
 * @param rhs A reference to primitive_node, will be assigned to *this.
 * @return *this for cascading assignment.
 **/
template <typename Type>
primitive_node<Type>& primitive_node<Type>::operator = (const primitive_node<Type>& rhs){
    node = rhs.node;
    prev = rhs.prev;
    next = rhs.next;
    parent = rhs.parent;
    return *this;
};
   
/**
 * @fn primitive_node<Type>::operator == (const primitive_node& rhs)
 * @brief Overload operator ==.
 * @param rhs A reference to primitive_node, will be compare to *this.
 * @retval true If rhs has same node value as *this.
 * @retval false If rhs has different node value as *this.
 **/
template <typename Type>
bool primitive_node<Type>::operator == (const primitive_node& rhs){
    return node == rhs.node;
}                             /**< Operator ==.*/

/**
 * @fn primitive_node<Type>::operator != (const primitive_node& rhs)
 * @brief Overload operator !=.
 * @param rhs A reference to primitive_node, will be compare to *this.
 * @retval true If rhs has different node value as *this.
 * @retval false If rhs has same node value as *this.
 **/
template <typename Type>
bool primitive_node<Type>::operator != (const primitive_node& rhs){
    return node != rhs.node;
}                             /**< Operator !=.*/

/** @} */ // end of group2

}// end of namespace bonzo



#endif /* primitive_node_hpp */
