/**
 *  @file basic_op.hpp
 *  @brief A basic operation interface virtual class for all data structure.
 *  @version v1.1
 *
 *  @author Created by Bonzo on 2016/3/31.
 *  @author Copyright © 2016 Bonzo. All rights reserved.
 *
 **/


#ifndef basic_op_hpp
#define basic_op_hpp

#include <vector>
#include "primitive_node.hpp"
/**
 * namespace bonzo.
 * @brief Customized namespace for this library.
 **/
namespace bonzo{
    
    using std::vector;
    using bonzo::primitive_node;
    
/**
 * @class basic_op
 * @brief A base class for basic operation.
 * A template of for basic operation. All methods are virtual and not defined.\n
 * Template variable: Type
 **/
template <class Type>
class basic_op{
public:
    virtual void swap(int, int) = 0;    /**< Swap 2 nodes by index. */
    virtual void insert(Type) = 0;      /**< Insert an nodes at the end. */
    virtual void insert(Type, int) = 0; /**< Insert an nodes by index. */
    virtual void erase(int) = 0;        /**< Erase a node by index. */
    virtual void append(Type) = 0;      /**< Insert a node at the end. */
    virtual vector<int> find(Type) = 0; /**< Find nodess by value, should return a vector of index. */
        
    virtual void reverse() = 0;         /**< Reverse nodess by data structure's definition. */
    virtual void print() const = 0;     /**< Print all nodes. */
    
    virtual int size() const = 0;       /**< Return number of nodes. */
    virtual bool empty() const = 0;     /**< Check if size is 0. */
        
    virtual Type operator[](int) const = 0;   /**< Overload operator []. */
};
    
}
#endif /* basic_op_hpp */
