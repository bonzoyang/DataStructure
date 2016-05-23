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
        virtual void swap(int, int) = 0;    /**< Swap 2 elements by index. */
        virtual void insert(Type) = 0;      /**< Insert an elements at the end. */
        virtual void insert(Type, int) = 0; /**< Insert an elements by index. */
        virtual void erase(int) = 0;        /**< Erase an element by index. */
        virtual void append(Type) = 0;      /**< Remove element by index. */
        virtual vector<int> find(Type) = 0; /**< Find elements by value, should return a vector of index. */
        
        virtual void reverse() = 0;         /**< Reverse elements by data structure's definition. */
        virtual void print() const = 0;     /**< Print all elements. */
        
        virtual Type operator[](int) const = 0;   /**< Overload operator []. */
    };
    
}
#endif /* basic_op_hpp */
