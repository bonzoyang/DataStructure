/**
 *  @file basic_op.hpp
 *  @brief A primitive node class for all data structure.
 *  @version v1.0
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
    protected:
        virtual void swap(primitive_node<Type>&, primitive_node<Type>&); /**< Swap 2 elements. */
        
        virtual void sort() = 0;            /**< Sort elements, can be implemented with any algorithm. */
        virtual void reverse() = 0;         /**< Reverse elements by data structure's definition. */
        
        virtual vector<int> find(Type) = 0; /**< Find elements by value, should return a vector of index. */
        virtual void insert(Type) = 0;      /**< Insert an elements by index. */
        virtual void remove(Type, int) = 0; /**< Remove element by value. */
        virtual void append(Type) = 0;      /**< Remove element by value. */
        
        virtual Type operator[](int) = 0;   /**< Subscript operator overload. */
        virtual void print() = 0;           /**< Print all elements. */
        
    };
    
}
#endif /* basic_op_hpp */
