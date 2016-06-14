/**
 *  @file dynamic_array.hpp
 *  @brief A dynamic array class template for user specified Type.
 *  @version v1.0
 *
 *  @author Created by Bonzo on 2016/4/6.
 *  @author Copyright © 2016 Bonzo. All rights reserved.
 *
 **/

#ifndef dynamic_array_hpp
#define dynamic_array_hpp

#include "debug.hpp"
#include <iostream>
#include <math.h>
/**
 * namespace bonzo.
 * @brief Customized namespace for this library.
 **/
namespace bonzo{

using std::ostream;

template <class Type>
class dynamic_array;

template <class Type>
ostream& operator << (ostream&, const dynamic_array<Type>&);

/** @defgroup group1 Class Template Declaration
 *  dynamic_array class template declaration
 *
 *  @{
 **/
/**
 * @class dynamic_array
 * @brief A dynamic_array class.
 * A template of dynamic array, support push/pop node by specified index.\n
 * Default is from the end of array.\n
 * Template variable: Type
 **/
template <class Type>
class dynamic_array{
public:
    dynamic_array();                     /**< Default constructor. */
    dynamic_array(Type*, int);           /**< Normal constructor. */
    dynamic_array(const dynamic_array&); /**< Copy constructor. */
    
    Type operator [](int) const;                      /**< Operator []. Allowed to use negative index. */
    dynamic_array operator + (const dynamic_array&);  /**< Operator +. */
    dynamic_array& operator = (const dynamic_array&); /**< Operator =. */
    dynamic_array operator += (dynamic_array&);       /**< Operator +=. */
    bool operator == (const dynamic_array&);          /**< Operator ==. */
    friend ostream& operator << <Type> (ostream&, const dynamic_array<Type>&); /**< Bound friend Operator <<. */

    int get_capacity() const; /**< Get capacity value. */
    int get_size() const;     /**< Get size value. */
    
    void insert(Type);        /**< Insert an element at the end. */
    void insert(Type, int);   /**< Insert an element by index. */
    void erase(int = -1);     /**< Erase an element by index. */
    void push_back(Type);     /**< Insert an element at the end. */
    void pop_back();          /**< Erase an element at the end. */
    void reverse();           /**< Reverse the array.*/
    void clear();             /**< Clear whole array .*/
    void shrink_to_fit();     /**< Shrink array to fit size. */
    int trans_index(int, bool = false) const; /**< Translate negative index to positive index. */
    bool in_range(int) const; /**< Chekc if index in the range. */
    
    
//    void (dynamic_array::* const push_back)(Type);   /**< Alias to insert(Type). */
//    void (dynamic_array::* const pop_back)();        /**< Alias to erase(). */

    
private:
    static const int init_capacity = 0; /**< Initial capacity of array. */
    int capacity;                       /**< Capacity of array. */
    int size;                           /**< Size of array. */
    Type* array;                        /**< Array to keep value. */
    
    void copy_from_array(Type* );               /**< Copy to new array and release old array. */
    void insert_e_capacity_fixed(Type& , int&); /**< Insert an element by index, with fixed capacity. */
    void erase_e_capacity_fixed(int&);          /**< Erase an element by index, with fixed capacity. */
    
    void estimate(int);                 /**< Estimate input index to nearest power of 2. */
    void check_expand();                /**< Check if it needs to expand, if so, double array size. */
    void check_shrink();                /**< Check if it needs to shrink, if so, half array size. */
    void release_array(Type*);          /**< Release memory for array by it's pointer. */
};
/** @} */ // end of group1

/**
 * @fn dynamic_array<Type>::dynamic_array()
 * @brief Default constructor.
 * @see dynamic_array(Type*, int)
 * @see dynamic_array(const dynamic_array&)
 **/
template <class Type>
dynamic_array<Type>::dynamic_array():capacity(init_capacity), size(0), array(nullptr)/*, push_back(&dynamic_array<Type>::insert), pop_back(&dynamic_array<Type>::erase)*/{
    return;
}

/**
 * @fn dynamic_array<Type>::dynamic_array(Type* in_array, int in_array_size)
 * @brief Normal constructor.
 * @param in_array Initialize array with in_array.
 * @param in_array_size Size of in_array.
 * @seedynamic_array()
 * @see dynamic_array(const dynamic_array&)
 **/
template <class Type>
dynamic_array<Type>::dynamic_array(Type* in_array, int in_array_size):capacity(init_capacity), size(0), array(nullptr)/*, push_back(&dynamic_array<Type>::insert), pop_back(&dynamic_array<Type>::erase)*/{
    estimate(in_array_size);
    copy_from_array(in_array);
    return;
}

/**
 * @fn dynamic_array<Type>::dynamic_array(const dynamic_array& rhs):array(nullptr)
 * @brief Copy constructor.
 * @param rhs A reference to another dynamic_array. Memberwisely initialize from rhs.
 * @see primitive_node()
 * @see primitive_node(const Type&)
 **/
template <class Type>
dynamic_array<Type>::dynamic_array(const dynamic_array& rhs):array(nullptr)/*, push_back(&dynamic_array<Type>::insert), pop_back(&dynamic_array<Type>::erase)*/{
    release_array(array);
    capacity = rhs.capacity;
    size = rhs.size;
    copy_from_array(rhs.array);
    return;
}

/**
 * @fn Type dynamic_array<Type>::operator [](int indx)
 * @brief Overload operator [].\n
 * Allowed to use negative index.
 * @param indx A subscript index of array, can be negative.
 * @return array[trans_index(indx)] An element at index indx.
 **/
template <class Type>
Type dynamic_array<Type>::operator [](int indx) const{
    return array[trans_index(indx, true)];
}

    
/**
 * @fn dynamic_array<Type> dynamic_array<Type>::operator + (const dynamic_array& rhs)
 * @brief Overload operator +.
 * @param rhs Another dynamice array to be cascaded.
 * @return temp A new allocated dynamic array to hold itself cascade with rhs.
 **/
template <class Type>
dynamic_array<Type> dynamic_array<Type>::operator + (const dynamic_array& rhs){
    dynamic_array temp(*this);
    
    for(int i = 0; i < rhs.size; i++){
        temp.push_back(rhs.array[i]);
    }
    return temp;
}

/**
 * @fn dynamic_array<Type> dynamic_array<Type>::operator = (const dynamic_array& rhs)
 * @brief Overload operator =.
 * @param rhs Another dynamice array to be assigned to.
 * @return *this Deep(element-wisely) copied from rhs to instance itself.
 **/
template <class Type>
dynamic_array<Type>& dynamic_array<Type>::operator = (const dynamic_array& rhs){
    capacity = rhs.capacity;
    size = rhs.size;
    copy_from_array(rhs.array);
    return *this;
}

/**
 * @fn dynamic_array<Type> dynamic_array<Type>::operator += (dynamic_array& rhs)
 * @brief Overload operator +=.
 * @param rhs Another dynamice array to be concatenated and assigned to.
 * @return *this Deep copied from concatenation of rhs and itself.
 **/
template <class Type>
dynamic_array<Type> dynamic_array<Type>::operator += (dynamic_array& rhs){
    *this = *this + rhs;
    return *this;
}

/**
 * @fn bool dynamic_array<Type>::operator == (const dynamic_array<Type>& rhs)
 * @brief Overload operator ==.
 * @param rhs Another dynamice array to be compared with.
 * @retval true next is a nullptr.
 * @retval false next is not a nullptr.
 **/
template <class Type>
bool dynamic_array<Type>::operator == (const dynamic_array<Type>& rhs){
    if(size != rhs.size){
        return false;
    }
    else{
        for(int i = 0; i < size; i++ ){
            if(array[i] != rhs.array[i])
                return false;
        }
        return true;
    }
}

/**
 * @fn ostream& operator << (ostream& os, const dynamic_array<Type>& rhs)
 * @brief Bound friend function template. Overload operator <<.
 * @param os An ostream instance to stream output, usually cout.
 * @param rhs A reference to dynamic_array, which will be print out.
 * @return os An ostream instance.
 **/
template <class Type>
ostream& operator << (ostream& os, const dynamic_array<Type>& rhs){
    os << "capacity: " << rhs.capacity << endl;
    os << "size: " << rhs.size << endl;
    os << "array: [";
    for(int i = 0; i < rhs.size; i++){
        os << rhs.array[i];
        if(i != rhs.size - 1)
            os << ", ";
    }
    os << "]" << endl;
    return os;
}

/**
 * @fn int dynamic_array<Type>::get_capacity()
 * @brief Access private member capacity.
 * @return Value of private member capacity.
 **/
template <class Type>
int dynamic_array<Type>::get_capacity() const{
    return capacity;
}
    
/**
 * @fn int dynamic_array<Type>::get_size()
 * @brief Access private member size.
 * @return size The size of the array.
 **/
template <class Type>
int dynamic_array<Type>::get_size() const{
    return size;
}

/**
 * @fn void dynamic_array<Type>::insert(Type e)
 * @brief Insert element at the end of array.
 * @param e An element to be inserted.
 **/
template <class Type>
void dynamic_array<Type>::insert(Type e){
    insert(e, size);
    return;
}

/**
 * @fn void dynamic_array<Type>::insert(Type e, int indx)
 * @brief Insert element into specified index of array.
 * @param e An element to be inserted.
 * @param indx The index where e will be inserted.
 **/
template <class Type>
void dynamic_array<Type>::insert(Type e, int indx){
    if(capacity == 0){
        array = new Type[1];
        capacity += 1;
    }
    
    if(size == capacity){
        estimate(size);
        copy_from_array(array);
    }
    
    if(size < capacity){
        insert_e_capacity_fixed(e, indx);
        size += 1;
        check_expand();
    }
    return;
}

/**
 * @fn void dynamic_array<Type>::erase(int indx)
 * @brief Erase the element at specified index.
 * @param indx The index of the element which will be erased.
 **/
template <class Type>
void dynamic_array<Type>::erase(int indx){
    if(size == capacity && size != 0){
        estimate(size);
        copy_from_array(array);
    }
    
    if(size >= 1){
        erase_e_capacity_fixed(indx);
        size -= 1;
        check_shrink();
    }
    return;
}    

/**
 * @fn void dynamic_array<Type>::push_back(Type e)
 * @brief Insert an element at the end.
 * @param e An element to be inserted at the end.
 **/
template <class Type>
void dynamic_array<Type>::push_back(Type e){
    insert(e);
    return;
}

/**
 * @fn void dynamic_array<Type>::pop_back()
 * @brief Erase an element at the end.
 **/
template <class Type>
void dynamic_array<Type>::pop_back(){
    erase();
    return;
}

/**
 * @fn void dynamic_array<Type>::reverse()
 * @brief Reverse the array.
 **/
template <class Type>
void dynamic_array<Type>::reverse(){    
    int half_size = int(size / 2);
    for(int i = 0; i < half_size; i++){
        Type tmp = array[i];
        array[i] = array[(size - 1) - i];
        array[(size - 1) - i] = tmp;
    }
    
    return;
}

    
/**
 * @fn void dynamic_array<Type>::clear()
 * @brief Clear whole array.
 **/
template <class Type>
void dynamic_array<Type>::clear(){
    release_array(array);
    array = new Type[init_capacity];
    capacity = init_capacity;
    size = 0;
    return;
}

/**
 * @fn void dynamic_array<Type>::shrink_to_fit()
 * @brief Shrink array to fit size.
 **/
template <class Type>
void dynamic_array<Type>::shrink_to_fit(){
    capacity = size;
    copy_from_array(array);
    return;
}

/**
 * @fn int dynamic_array<Type>::trans_index(int indx, bool fit) const
 * @brief Translate negative index to positive index.
 * @param indx The index for translation, negative value is allowed.
 * @param fit An option making index after translation fit in the range of the array.
 * @return tindx Index after translation.
 **/
template <class Type>
int dynamic_array<Type>::trans_index(int indx, bool fit) const{
    int tindx = (indx >= 0) ? indx : (size + indx) ;
    if(fit){
        if(tindx < 0)
            tindx = 0;
        else if(size == 0)
            tindx = 0;
        else if(tindx >= size)
            tindx = size - 1;
        
    }
    return tindx;
}

/**
 * @fn bool dynamic_array<Type>::in_range(int indx) const
 * @brief Chekc if index in the range.
 * @param indx The index to check if in the range or not.
 * @retval true indx is in the range.
 * @retval false indx is out of range.
 **/
template <class Type>
bool dynamic_array<Type>::in_range(int indx) const{
    int t_indx = trans_index(indx);
    return t_indx < size && t_indx >= 0;
}

/**
 * @fn void dynamic_array<Type>::copy_from_array(Type* in_array)
 * @brief Copy to new array and release old array.
 * @param in_array The pointer to the array to be copied.
 **/
template <class Type>
void dynamic_array<Type>::copy_from_array(Type* in_array){
    Type* old_array = array;
    array = new Type[capacity];
    for(int i= 0; i < size; i++){
        array[i] = in_array[i];
    }
    release_array(old_array);
    return;
}

/**
 * @fn void dynamic_array<Type>::insert_e_capacity_fixed(Type& e, int& indx)
 * @brief Insert an element by index, with fixed capacity.
 * @param e An element to be inserted.
 * @param indx The index where e will be inserted.
 **/
template <class Type>
void dynamic_array<Type>::insert_e_capacity_fixed(Type& e, int& indx){
    int tindx = trans_index(indx);
    if(tindx < 0)
        tindx = 0;
    
    if(tindx >= size){
        array[size] = e;
        return;
    }
    
    int ti;
    int i;
    for(i = -1, ti = trans_index(i); in_range(ti); i--, ti = trans_index(i)){
        
        array[ti + 1] = array[ti];
        if(ti == tindx){
            array[ti] = e;
            break;
        }
    }
    return;
}
    

/**
 * @fn void dynamic_array<Type>::erase_e_capacity_fixed(int& indx)
 * @brief Erase an element by index, with fixed capacity.
 * @param indx The index of the element which will be erased.
 **/
template <class Type>
void dynamic_array<Type>::erase_e_capacity_fixed(int& indx){
    int tindx = trans_index(indx);
    if(tindx < 0)
        tindx = 0;
    
    if(tindx >= size){
        array[-1] = 0;
        return;
    }
    
    int i;
    for(i = tindx; in_range(i); i++){
        array[i] = array[i + 1];
    }
    return;
}

/**
 * @fn void dynamic_array<Type>::estimate(int a_sz)
 * @brief Estimate input index to nearest power of 2.
 * @param a_sz Array sized to be estimated.
 **/
template <class Type>
void dynamic_array<Type>::estimate(int a_sz){
    int p_a_sz = ceil(log2(a_sz));
    capacity = int(pow(2, p_a_sz));
    size = a_sz;
    return;
}
    
/**
 * @fn void dynamic_array<Type>::check_expand()
 * @brief Check if it needs to expand, if so, double array size.
 **/
template <class Type>
void dynamic_array<Type>::check_expand(){
    if(size >= int(0.75 * capacity)){
        capacity *= 2;
        copy_from_array(array);
    }
    return;
}

/**
 * @fn void dynamic_array<Type>::check_shrink()
 * @brief Check if it needs to shrink, if so, half array size.
 **/
template <class Type>
void dynamic_array<Type>::check_shrink(){
    if(size == 0){
        if(capacity != 0 ){
            release_array(array);
            capacity = 0;
        }
        return;
    }
    else if(size <= int(0.25 * capacity) ){
        capacity = int(capacity / 2);
        copy_from_array(array);
    }
    return;
}

/**
 * @fn void dynamic_array<Type>::release_array(Type* a)
 * @brief Release memory for array by it's pointer.
 * @param a The array to be delete.
 **/
template <class Type>
void dynamic_array<Type>::release_array(Type* a){
    delete [] a;
    return;
}


    
    
}



#endif /* dynamic_array_hpp */
