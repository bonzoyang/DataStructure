/**
 *  @file iterator.hpp
 *  @brief A basic operation interface virtual class for all data structure.
 *  @version v1.2
 *
 *  @author Created by Bonzo on 2016/6/9.
 *  @author Copyright © 2016 Bonzo. All rights reserved.
 *
 **/

#ifndef iterator_hpp
#define iterator_hpp

#include "primitive_node.hpp"
/**
 * namespace bonzo.
 * @brief Customized namespace for this library.
 **/
namespace bonzo{
    using bonzo::primitive_node;
    
/**
 * @class iterator
 * @brief A base class for basic operation.
 * A template of for basic operation. All methods are virtual and not defined.\n
 * Template variable: Type
 **/
template <class Type>
class iterator{
    typedef primitive_node<Type>* pnode_ptr;
    typedef pnode_ptr (iterator::* move_fp)(pnode_ptr);
    
public:
    iterator();
    virtual pnode_ptr begin() const = 0;
    virtual pnode_ptr end() const = 0;
    virtual pnode_ptr next(move_fp, pnode_ptr) const = 0;
    virtual pnode_ptr travers1(pnode_ptr) = 0;
    virtual pnode_ptr travers2(pnode_ptr) = 0;
    virtual pnode_ptr travers3(pnode_ptr) = 0;
    virtual pnode_ptr travers4(pnode_ptr) = 0;
//private:
    pnode_ptr iter;
    move_fp move_next;
};
    
template <class Type>
iterator<Type>::iterator():iter(nullptr), move_next(nullptr){
    return;
}
}
#endif /* iterator_hpp */
