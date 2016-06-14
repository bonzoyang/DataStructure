/**
 *  @file binary_tree.hpp
 *  @brief A binary tree class template for user specified Type.
 *  @version v1.0
 *
 *  @author Created by Bonzo on 2016/5/18.
 *  @author Copyright © 2016 Bonzo. All rights reserved.
 *
 **/


#ifndef binary_tree_hpp
#define binary_tree_hpp
//#include "primitive_node.hpp"
//#include "basic_op.hpp"
//#include "dynamic_array.hpp"
//#include "debug.hpp"
#include "iterator.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include <iomanip>

/**
 * namespace bonzo.
 * @brief Customized namespace for this library.
 **/
namespace bonzo{
using bonzo::primitive_node;
using bonzo::iterator;
using bonzo::stack;
using bonzo::queue;
using std::cout;
using std::setw;
using std::setfill;
using std::ostream;
using std::vector;
using std::setiosflags;
using std::resetiosflags;
using std::ios;

template <class Type>
class binary_tree;

template <class Type>
ostream& operator << (ostream&, const binary_tree<Type>&);

/** @defgroup group1 Class Template Declaration
 *  binary_tree class template declaration
 *
 *  @{
 **/
/**
 * @class binary_tree
 * @brief A binary_tree class.
 * A template of binary tree, support subscripting.\n
 * Template variable: Type
 **/
template <class Type>
class binary_tree : /*public basic_op<Type>,*/ public iterator<Type>{
    typedef primitive_node<Type>* pnode_ptr;
    typedef pnode_ptr (iterator<Type>::* move_fp)(pnode_ptr);
    typedef enum {ready, go_down, go_sibling, go_up} traves_state;
    
public:
    binary_tree();                   /**< Default constructor. */
    binary_tree(binary_tree&); /**< Copy constructor. */
    ~binary_tree();                  /**< Destructor. */
    binary_tree sub_tree(pnode_ptr);
    bool insert(Type, pnode_ptr, bool = true);
    bool erase(pnode_ptr);
    void clear();
    void print(int = 1, int = 3) const;
    
    virtual pnode_ptr begin() const;
    virtual pnode_ptr end() const;
    virtual pnode_ptr next(move_fp, pnode_ptr) const;
    virtual pnode_ptr travers1(pnode_ptr);
    virtual pnode_ptr travers2(pnode_ptr);
    virtual pnode_ptr travers3(pnode_ptr);
    virtual pnode_ptr travers4(pnode_ptr);
    
    friend ostream& operator << <Type> (ostream&, const binary_tree<Type>&);
    
    binary_tree& operator = (const binary_tree&);
    bool operator == (const binary_tree&);
    bool operator != (const binary_tree&);

private:
    pnode_ptr root;
//    pnode_ptr tail;
//    pnode_ptr iter;
    queue<pnode_ptr> dft_q;
    queue<pnode_ptr> bft_q;
    queue<pnode_ptr> post_q;
    queue<pnode_ptr> in_q;
    
//    pnode_ptr left_child(pnode_ptr);
//    pnode_ptr right_child(pnode_ptr);
//    pnode_ptr dft_back_trace(pnode_ptr);
//    pnode_ptr right_sibling(pnode_ptr);
    pnode_ptr parent(pnode_ptr) const;
    
    int children_count(pnode_ptr) const;
    int level_count(pnode_ptr);
    bool no_child(pnode_ptr);

//    bool one_child(pnode_ptr);
    bool two_child(pnode_ptr) const;
    bool has_sibling(pnode_ptr) const;
    bool is_a_left_child(pnode_ptr) const;
    bool has_left_child(pnode_ptr) const;
    bool has_right_child(pnode_ptr) const;
    
    void make_dft_queue();
    void make_bft_queue();
    void make_post_queue();
    void make_in_queue();
    int position(pnode_ptr) const;
    bool is_a_tree_node(pnode_ptr) const;
    void copy_from_tree(const binary_tree&, pnode_ptr = nullptr);
    

//    dynamic_array<pnode_ptr> nptr_a;
    
//    node_ptr depth_first_nest();
//    node_ptr breadth_first_next();

    
};
/** @} */ // end of group1
using bonzo::print_dbg_msg;
using bonzo::_DEBUG_ON;

/**
 * @fn binary_tree<Type>::binary_tree()
 * @brief Default constructor.
 * @see binary_tree(const linked_list& rhs)
 **/
template <class Type>
binary_tree<Type>::binary_tree():root(nullptr){
    return;
}

/**
 * @fn binary_tree<Type>::binary_tree(const binary_tree& rhs)
 * @brief Copy constructor.
 * @see binary_tree()
 **/
template <class Type>
binary_tree<Type>::binary_tree(binary_tree& rhs){
    copy_from_tree(rhs, rhs.begin());
    return;
}
    

/**
 * @fn binary_tree<Type>::~binary_tree()
 * @brief Destructor.
 * @see ~binary_tree()
 **/
template <class Type>
binary_tree<Type>::~binary_tree(){
    //clear();
    return;
}


template<class Type>
binary_tree<Type> binary_tree<Type>::sub_tree(pnode_ptr curr){
    binary_tree<Type> curr_sub_tree;
    curr_sub_tree.copy_from_tree(*this, curr);
    return curr_sub_tree;
}
    
 

template<class Type>
bool binary_tree<Type>::insert(Type e, pnode_ptr curr, bool add_at_left){
    if(root == nullptr && curr == root){
        pnode_ptr new_node = new primitive_node<Type>(e);
        root = new_node;
    }
    else if(!is_a_tree_node(curr) || two_child(curr)){
        return false;
    }
    else if(no_child(curr)){
        pnode_ptr new_node = new primitive_node<Type>(e);
        if(add_at_left)
            curr -> left = new_node;
        else
            curr -> right = new_node;
        
        new_node -> parent = curr;
    }else{
        pnode_ptr new_node = new primitive_node<Type>(e);
        if(has_left_child(curr))
            curr -> right = new_node;
        else
            curr -> left = new_node;
        
        new_node -> parent = curr;
    }
    
    make_dft_queue();
    make_bft_queue();
    make_post_queue();
    make_in_queue();
    return true;
}

template<class Type>
bool binary_tree<Type>::erase(pnode_ptr curr){
    if(!is_a_tree_node(curr))
        return false;
    
    stack<pnode_ptr> post_temp1;
    stack<pnode_ptr> post_temp2;
    
    post_temp1.push(curr);
    while(!post_temp1.empty()){
        curr = post_temp1.pop();
        post_temp2.push(curr);

        
        if(!no_child(curr)){
            if(has_left_child(curr))
                post_temp1.push(curr -> left);

            if(has_right_child(curr))
                post_temp1.push(curr -> right);
        }
    }
    
    while(!post_temp2.empty())
        delete post_temp2.pop();
    
    make_dft_queue();
    make_bft_queue();
    make_post_queue();
    make_in_queue();

    return true;
}
    
template<class Type>
void binary_tree<Type>::clear(){
    erase(root);
}


template<class Type>
void binary_tree<Type>::print(int node_wid, int dash) const{    
    int unit = node_wid + dash;
    int level_node_cnt_phase0 = 1;
    int level_node_cnt_phase1 = 1;
    int next_level_node_cnt = 0;
    int curr_position = 0;
    int level_print_so_far = 0;
    int parent_position = 0;
    pnode_ptr curr = nullptr;
    int phase = 0;
    
    
    for(int i = 0; i < bft_q.size(); i++){
        curr = bft_q[i];
        curr_position = position(curr);

        if(i == 0){
            cout << setfill(' ') << setw(curr_position * unit) << "" <<  *curr << " <- ROOT";
            next_level_node_cnt += children_count(curr);
            level_node_cnt_phase1--;
            phase = 1;
        }
        else{
            parent_position = position(parent(curr));
            
            if(phase == 0){
                if(is_a_left_child(curr)){
                    cout << setfill(' ') << setw((curr_position -  level_print_so_far) * unit) << "";
                    cout << setfill('-') << setw((parent_position - curr_position) * unit) << "";
                    level_print_so_far = parent_position;
                }else{
                    if(!has_left_child(parent(curr))){
                        cout << setfill(' ') << setw((parent_position -  level_print_so_far) * unit) << "";
                        level_print_so_far = parent_position;
                    }
                    cout << setfill('-') << setw((curr_position -  level_print_so_far/* - 1*/) * unit+ 1) << "";
                    level_print_so_far = curr_position;
                }
                
                level_node_cnt_phase0--;
            }
            
            
            if(phase == 1){
                if(is_a_left_child(curr)){
                    cout << setfill(' ') << setw((curr_position -  level_print_so_far) * unit) << "";
                    cout << setiosflags(ios::left) << setfill(' ')  << setw((parent_position - curr_position)*unit) << *curr<<resetiosflags(ios::left);
                    level_print_so_far = parent_position;
                }else{
                    cout << setfill(' ') << setw((curr_position -  level_print_so_far) * unit) << "";
                    cout << setiosflags(ios::right) << *curr<<resetiosflags(ios::right);
                    level_print_so_far = curr_position;
                }
                
                level_node_cnt_phase1--;
                next_level_node_cnt += children_count(curr);
            }

        }
        

        if(phase == 0){
            if(level_node_cnt_phase0 == 0){
                cout << endl;
                level_print_so_far = 0;
                i -= level_node_cnt_phase1;
                phase = 1;
            }
        }
        else if(phase == 1){
            if(level_node_cnt_phase1 == 0){
                cout << endl;
                level_node_cnt_phase0 = next_level_node_cnt;
                level_node_cnt_phase1 = next_level_node_cnt;
                next_level_node_cnt = 0;
                level_print_so_far = 0;
                phase = 0;
            }
        }
    
    
    }

    return;
}

/**
 * @fn rimitive_node<Type>* binary_tree<Type>::begin()
 * @brief Let iterator iter at the root.
 * @return root The root of binary tree.
 **/
template<class Type>
primitive_node<Type>* binary_tree<Type>::begin() const {
    return root;
}
/**
 * @fn rimitive_node<Type>* binary_tree<Type>::end()
 * @brief Let iterator iter at the tail.
 * @return tail The tail of binary tree.
 **/
template<class Type>
primitive_node<Type>* binary_tree<Type>::end() const {
    //return tail;
    return nullptr;
}

template<class Type>
primitive_node<Type>* binary_tree<Type>::next(move_fp m, pnode_ptr curr) const{
    // iterator<Type>::move_next = m;
    const_cast<binary_tree*>(this) -> move_next = m;
    iterator<Type>* iterator_ptr = const_cast<binary_tree*>(this);
    return (iterator_ptr ->* iterator<Type>::move_next)(curr);
}

/**
 * @fn primitive_node<Type>* binary_tree<Type>::travers1(pnode_ptr curr)
 * @brief Depth first traversal.
 * @return tail A pointer to next node.
 **/
template <class Type>
primitive_node<Type>* binary_tree<Type>::travers1(pnode_ptr curr) {
    int i = 0;
    for( ; i < dft_q.size(); i++)
        if(dft_q[i] == curr)
            break;
    
    return (i >= dft_q.size() - 1) ? nullptr : dft_q[i + 1];
}

    
/**
 * @fn primitive_node<Type>* binary_tree<Type>::travers2(pnode_ptr curr)
 * @brief Breadth first traversal.
 * @return tail A pointer to next node.
 **/
template <class Type>
primitive_node<Type>* binary_tree<Type>::travers2(pnode_ptr curr) {
    int i = 0;
    for( ; i < bft_q.size(); i++)
        if(bft_q[i] == curr)
            break;
    
    return (i >= bft_q.size() - 1) ? nullptr : bft_q[i + 1];
}

/**
 * @fn primitive_node<Type>* binary_tree<Type>::travers3(pnode_ptr curr)
 * @brief Breadth first traversal.
 * @return tail A pointer to next node.
 **/
template <class Type>
primitive_node<Type>* binary_tree<Type>::travers3(pnode_ptr curr) {
    int i = 0;
    for( ; i < post_q.size(); i++)
        if(post_q[i] == curr)
            break;
    
    return (i >= post_q.size() - 1) ? nullptr : post_q[i + 1];
}
    
/**
 * @fn primitive_node<Type>* binary_tree<Type>::travers4(pnode_ptr curr)
 * @brief Breadth first traversal.
 * @return tail A pointer to next node.
 **/
template <class Type>
primitive_node<Type>* binary_tree<Type>::travers4(pnode_ptr curr) {
    int i = 0;
    for( ; i < in_q.size(); i++)
        if(in_q[i] == curr)
            break;
    
    return (i >= in_q.size() - 1) ? nullptr : in_q[i + 1];
}

template <class Type>
ostream& operator << (ostream& os, const binary_tree<Type>& rhs){
    rhs.print(4, 3);
    return os;
}

    
template <class Type>
binary_tree<Type>& binary_tree<Type>::operator = (const binary_tree& rhs){
    if(&rhs != this)
        copy_from_tree(rhs);
    return *this;
}

template<class Type>
bool binary_tree<Type>::operator == (const binary_tree& rhs){
    stack<pnode_ptr> dft_temp;
    stack<pnode_ptr> rhs_dft;

    dft_temp.push(root);
    rhs_dft.push(rhs.root);
    pnode_ptr curr;
    pnode_ptr rhs_curr;
    while(!dft_temp.empty()){
        curr = dft_temp.pop();
        rhs_curr = rhs_dft.pop();
        //dft_q.push(curr);
        
        if(children_count(curr) != children_count(rhs_curr))
            return false;
        
        if(has_right_child(curr) ^ has_right_child(rhs_curr))
            return false;
        
        if(!no_child(curr)){
            if(has_right_child(curr)){
                dft_temp.push(curr -> right);
                rhs_dft.push(rhs_curr -> right);
            }
            
            if(has_left_child(curr)){
                dft_temp.push(curr -> left);
                rhs_dft.push(rhs_curr -> left);
            }

        }
        
        if(*curr != *rhs_curr)
            return false;
    }

    return true;

    
}
    
template<class Type>
bool binary_tree<Type>::operator != (const binary_tree& rhs){
    return !(*this == rhs);
}

// private method

template <class Type>
primitive_node<Type>* binary_tree<Type>::parent(pnode_ptr curr) const{
    return curr -> parent;
}
    
template <class Type>
int binary_tree<Type>::children_count(pnode_ptr curr) const{
    int n = 0;
    if(curr == nullptr)
        return n;

    if(curr -> left != nullptr)
        n += 1;
    
    if(curr -> right != nullptr)
        n+= 1;
        
    return n;
}

template <class Type>
int binary_tree<Type>::level_count(pnode_ptr curr){
    int n = 1;
    while(curr != root){
        curr = parent(curr);
        n += 1;
    }
    
    return n;
}

template <class Type>
bool  binary_tree<Type>::no_child(pnode_ptr curr){
    return children_count(curr) == 0;
}
/*
template <class Type>
bool  binary_tree<Type>::one_child(pnode_ptr curr){
    return children_count(curr) == 1;
}
*/

template <class Type>
bool  binary_tree<Type>::two_child(pnode_ptr curr) const{
    return children_count(curr) == 2;
}

template <class Type>
bool binary_tree<Type>::has_sibling(pnode_ptr curr) const{
    return two_child(parent(curr));
}

    
template <class Type>
bool binary_tree<Type>::is_a_left_child(pnode_ptr curr) const{
    return  parent(curr) == nullptr ? curr == nullptr : curr == parent(curr) -> left;
}

template <class Type>
bool binary_tree<Type>::has_left_child(pnode_ptr curr) const{
    return curr -> left != nullptr;
}


template <class Type>
bool binary_tree<Type>::has_right_child(pnode_ptr curr) const{
    return curr -> right != nullptr;
}

template <class Type>
void  binary_tree<Type>::make_dft_queue(){
    dft_q.clear();
    stack<pnode_ptr> dft_temp;

    dft_temp.push(root);
    pnode_ptr curr;
    while(!dft_temp.empty()){
        curr = dft_temp.pop();
        dft_q.push(curr);
        
        if(!no_child(curr)){
            if(has_right_child(curr))
                dft_temp.push(curr -> right);
                
            if(has_left_child(curr))
                dft_temp.push(curr -> left);
        }
    }

    return;
}
    
template <class Type>
void  binary_tree<Type>::make_bft_queue(){
    bft_q.clear();
    queue<pnode_ptr> bft_temp;
    
    bft_temp.push(root);
    pnode_ptr curr;
    while(!bft_temp.empty()){
        curr = bft_temp.pop();
        bft_q.push(curr);
        
        if(!no_child(curr)){
            if(has_left_child(curr))
                bft_temp.push(curr -> left);

            if(has_right_child(curr))
                bft_temp.push(curr -> right);
        }
    }

    return;
}
    
template <class Type>
void  binary_tree<Type>::make_post_queue(){
    post_q.clear();
    stack<pnode_ptr> post_temp1;
    stack<pnode_ptr> post_temp2;
    
    post_temp1.push(root);
    pnode_ptr curr;

    while(!post_temp1.empty()){
        curr = post_temp1.pop();
        post_temp2.push(curr);

        
        if(!no_child(curr)){
            if(has_left_child(curr))
                post_temp1.push(curr -> left);

            if(has_right_child(curr))
                post_temp1.push(curr -> right);
        }
        
    }
    
    while(!post_temp2.empty()){
        post_q.push(post_temp2.pop());
    }
  
    return;
}

template <class Type>
void  binary_tree<Type>::make_in_queue(){
    in_q.clear();
    stack<pnode_ptr> in_temp1;
    stack<bool> in_temp1_out;
    
    in_temp1.push(root);
    in_temp1_out.push(false);
    
    pnode_ptr curr;
    bool curr_out;

    while(!in_temp1.empty()){

        curr = in_temp1.pop();
        curr_out = in_temp1_out.pop();
        if(no_child(curr) || curr_out){
            in_q.push(curr);
        }else if(!no_child(curr)){
            
            if(has_right_child(curr)){
                in_temp1.push(curr -> right);
                in_temp1_out.push(false);
            }
            
            in_temp1.push(curr);
            in_temp1_out.push(true);

            if(has_left_child(curr)){
                in_temp1.push(curr -> left);
                in_temp1_out.push(false);
            }
            
        }
    }

    return;
}
template <class Type>
int  binary_tree<Type>::position(pnode_ptr curr) const{
    for(int i = 0; i < in_q.size(); i++)
        if(curr == in_q[i])
            return i;
    
    return -1;
}


template<class Type>
bool binary_tree<Type>::is_a_tree_node(pnode_ptr curr) const{
    
    if(curr == nullptr || root == nullptr)
        return false;
    
    for(int i = 0; i < dft_q.size(); i++)
        if(dft_q[i] == curr)
            return true;
    
    return false;
}

   
template<class Type>
void binary_tree<Type>::copy_from_tree(const binary_tree& rhs, pnode_ptr rhs_curr){
    clear();
    
    if(!rhs.is_a_tree_node(rhs_curr))
        return;
    
    if(rhs_curr == nullptr)
        rhs_curr = rhs.begin();
    
    pnode_ptr curr;
    pnode_ptr rhs_curr_temp = rhs_curr;
    
    insert(rhs_curr -> get_node(), root);
    curr = root;
    
    while(rhs_curr != nullptr){
            if(rhs.has_left_child(rhs_curr)){
                rhs_curr_temp = rhs.next(&iterator<Type>::travers2, rhs_curr_temp);
                if(rhs_curr_temp != nullptr)
                    insert(rhs_curr_temp -> get_node(), curr, true);
            }
        
            if(rhs.has_right_child(rhs_curr)){
                rhs_curr_temp = rhs.next(&iterator<Type>::travers2, rhs_curr_temp);
                if(rhs_curr_temp != nullptr)
                    insert(rhs_curr_temp -> get_node(), curr, false);
            }

        rhs_curr = rhs.next(&iterator<Type>::travers2, rhs_curr);
        curr = next(&iterator<Type>::travers2, curr);
        
    }
    return;

}

}


#endif /* binary_tree_hpp */
