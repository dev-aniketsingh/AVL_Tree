#ifndef _AVL_H
#define _AVL_H
#include <iostream>
#include <new>
#include <ostream>
#include <algorithm>
#include <exception>
using namespace std;

static const int MAX_IMBALANCE = 1;

template<typename T>
class AVLTree {
	private:
		struct AVLNode {
				T element;
		        AVLNode  *left;
		        AVLNode  *right;
		        int height;

		        AVLNode(const T & el, AVLNode *l, AVLNode *r, int h = 0) {
		        	element = el;
		        	left = l;
		        	right = r;
		        }
		        AVLNode( T && el, AVLNode *l, AVLNode *r, int h = 0 ) { 
          			element = move(el); 
          			left = l;  
          			right = r;
          			height = h;
          		} 
		};
		AVLNode *root;
		int height(AVLNode *r) {
    		if(r == nullptr) {
    			return -1;
    		}
    		else {
    			return (r->height);
    		}
    	}
    	AVLNode *replicate(AVLNode *r) const {
	        if(r == nullptr )
	            return nullptr;
	        else
	            return new AVLNode{r->element,replicate(r->left),replicate(r->right),r->height};
    	}
    	AVLNode *Min(AVLNode *r) const {
	        if(r == nullptr )
	            return nullptr;
	        if(r->left == nullptr )
	            return r;
	        return Min(r->left);
    	}
    	AVLNode *Max(AVLNode *r) const {
	        if(r == nullptr)
	        	return nullptr;
	        if(r->left == nullptr)
	        	return r;
	        return Max(r->right);
    	}
    	bool hasGot(const T & x,AVLNode * r) const {
	        if(r == nullptr)
	            return false;
	        else if(x < r->element)
	            return hasGot(x, r->left);
	        else if(r->element < x)
	            return hasGot(x, r->right);
	        else
	            return true;    
    	}
    	void empty(AVLNode * & r) {
	        if( r != nullptr ) {
	            empty( r->left );
	            empty( r->right );
	            delete r;
	        }
	        r = nullptr;
    	}
    	void print(AVLNode *r) const {
	        if(r != nullptr )
	        {
	            print(r->left);
	            cout << r->element << endl;
	            print(r->right);
	        }
    	}
    	void rotateWithLeftChild(AVLNode * & b) {
	        AVLNode *a = b->left;
	        b->left = a->right;
	        a->right = b;
	        b->height = max( height( b->left ), height( b->right ) ) + 1;
	        a->height = max( height( a->left ), b->height ) + 1;
	        b = a;
    	}
	    void rotateWithRightChild(AVLNode * & a) {
	        AVLNode *b = a->right;
	        a->right = b->left;
	        b->left = a;
	        a->height = max( height(a->left ), height(a->right)) + 1;
	        b->height = max( height(b->right ), a->height) + 1;
	        a = b;
	    }
	    void doubleWithLeftChild(AVLNode * & c) {
	        rotateWithRightChild(c->left );
	        rotateWithLeftChild(c);
	    }
	    void doubleWithRightChild(AVLNode * & a) {
	        rotateWithLeftChild(a->right);
	        rotateWithRightChild(a);
	    }
	    void balance(AVLNode * & r) {
	        if(r == nullptr )
	            return;
	        
	        if(height(r->left) - height(r->right) > MAX_IMBALANCE ) {
	            if( height( r->left->left ) >= height( r->left->right ) )
	                rotateWithLeftChild(r);
	            else
	                doubleWithLeftChild(r);
	        }
	        else {
		        if(height(r->right) - height(r->left) > MAX_IMBALANCE) {
		            if( height(r->right->right) >= height(r->right->left))
		                rotateWithRightChild(r);
		            else
		                doubleWithRightChild(r);
		        }
		        r->height = max(height(r->left),height(r->right)) + 1;

	    	}
    	}
    	void insert( const T & x, AVLNode * & r)
    	{
	        if( r == nullptr )
	            r = new AVLNode{ x, nullptr, nullptr };
	        else if( x < r->element )
	            insert( x, r->left );
	        else if( r->element < x )
	            insert( x, r->right );
	        
	        balance(r);
    	}
    	void insert( T && x, AVLNode * & r ) {
	        if( r == nullptr )
	            r = new AVLNode{ std::move( x ), nullptr, nullptr };
	        else if( x < r->element )
	            insert( std::move( x ), r->left );
	        else if( r->element < x )
	            insert( std::move( x ), r->right );
	        
	        balance(r);
   		}
    	void deleteVal(const T & x, AVLNode * &r) {
	        if( r == nullptr )
	            return;  
	        
	        if( x < r->element )
	            deleteVal( x, r->left );
	        else if( r->element < x )
	            deleteVal( x, r->right );
	        else if( r->left != nullptr && r->right != nullptr ) 
	        {
	            r->element = Min(r->right)->element;
	            deleteVal(r->element, r->right);
	        }
	        else
	        {
	            AVLNode *oldNode = r;
	            r = ( r->left != nullptr ) ? r->left : r->right;
	            delete oldNode;
	        } 
	        balance(r);
		}
	public:
	    AVLTree() {
	    	root = nullptr;
	    }
	    AVLTree(const AVLTree &rhs) : root{nullptr} {
	    	root = replicate(rhs.root);
	    }
	    AVLTree(AVLTree && rhs ) : root{rhs.root} {
        	rhs.root = nullptr;
   		}
	    ~AVLTree() {
        	empty();
    	}
	    AVLTree & operator = (const AVLTree & rhs) {
	        AVLTree lhs = rhs;
	        std::swap(*this,lhs);
	        return *this;
	    }
	    AVLTree & operator = (AVLTree && rhs) {
	        std::swap(root,rhs.root);
	        return *this;
	    }
	    const T & Min() const {
	        if(root == nullptr) {
	        	throw  "underflow_error"; 
	        }
	        return Min(root)->element;
    	}
	    const T & Max() const
	    {
	        if(root == nullptr)
	            throw "underflow_error";
	        return Max(root)->element;
	    }
	    bool hasGot(const T & x) const
	    {
	        return hasGot(x,root);
	    }
	    bool isEmpty() const
	    {
	        return (root == nullptr);
	    }
	    void print() const
	    {
	        if(root == nullptr)
	            cout << "Empty tree" << endl;
	        else
	            print(root);
	    }
	    void empty()
	    {
	        empty(root);
	    }

	    void insert(const T & x)
	    {
	        insert(x,root);
	    }

	    void deleteVal(const T & x)
	    {
	        deleteVal(x,root);
	    }
};
#endif