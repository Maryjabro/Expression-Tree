
#include "ExpressionTree.h"
//precedence ()^*/+-

//set nodes
template <typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode ( char elem, ExprTreeNode *leftPtr, ExprTreeNode *rightPtr ):dataItem(elem),left(leftPtr),right(rightPtr)
{
}



template <typename DataType>
ExprTree<DataType>::ExprTree ():root(0)
{

}

//copy constructor
template <typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree& source)
{
    root = source.root;
    copyHelper(root);
        
    
}
//assignment
template <typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree& source) {
    if (&source != this) {  // Use proper comparison
        clear();  // Clear existing nodes
        root = copyHelper(source.root);  // Copy everything
    }
    return *this;
}

template <typename DataType>
ExprTree<DataType>::~ExprTree ()
{
    clear(); //clear
}
//Reads an arithmetic expression in prefix form from the keyboard and builds the corresponding expression tree.
template <typename DataType>
void ExprTree<DataType>::build ()
{
    clear();
    buildHelper(root);

}

//Outputs the expression corresponding ot the value of the tree ni fuly parenthesized
//infix form.
template <typename DataType>
void ExprTree<DataType>::expression () const
{
    exprHelper(root);
}
//Returns the value of the corresponding arithmetic expression.
template <typename DataType>
DataType ExprTree<DataType>::evaluate() const throw (logic_error)
{
    return evalHelper(root);

}

template <typename DataType>
void ExprTree<DataType>::clear ()
{
    clearHelper(root);
}

template <typename DataType>
void ExprTree<DataType>::commute()
{
    commuteHelper(root);
}

template <typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree& source) const
{
    return isEquivalentHelper(root,source->root);
}

template <typename DataType>
bool ExprTree<DataType>::isEmpty() const
{
	return false;
}

//helpers

template <typename DataType>
void ExprTree<DataType>:: copyHelper (ExprTreeNode *&p ){
    if ( p != 0 ){
        p = new ExprTreeNode(p->dataItem,p->left,p->right);
        copyHelper(p->left);
        copyHelper(p->right);
    }
}

template <typename DataType>
void ExprTree<DataType>::buildHelper(ExprTreeNode*& p) {
    char ch; // Input operator or number
    cin >> ch;
    p = new ExprTreeNode(ch,0,0); // Link in node
    if ( !isdigit(ch) ) // Operator -- construct subtrees
    {
        //recursive
        buildHelper(p->left);
        buildHelper(p->right);
    }

}
template <typename DataType>
void ExprTree<DataType>::exprHelper(ExprTreeNode* p) const {
    if (p != nullptr) {
        if (!isdigit(p->dataItem)) cout << '(';
        cout << p->dataItem;  // Output node data
        exprHelper(p->left);  // Recursively traverse left subtree
        if (!isdigit(p->dataItem)) cout << ')';
        exprHelper(p->right);  // Recursively traverse right subtree
    }
}

template <>
float ExprTree<float>::evalHelper(ExprTreeNode* p) const{
    // define variables for intermediate and final results
    if ( isdigit(p->dataItem) )
       return  p->dataItem - '0';      // Convert from char to number
    else {
        // evaluate left and right subtrees, and combine results
        float left = evalHelper(p->left);
        float right = evalHelper(p->right);
        
        switch(p->dataItem){
                
            case '+':
                return left+right;
            case '-':
                return left-right;
                
            case '*':
                return left*right;
                
            case '/':
                return left/right;
            default:
                cerr<<"not an operator";
                return 0;
        }
        
    }
}


template <typename DataType>
void ExprTree<DataType>:: clearHelper (ExprTreeNode *p ){
    if ( p != 0 ){
        // clear left and right subtrees
        delete p;
        clearHelper(p->left);
        clearHelper(p->right);
    }
}



template <typename DataType>
void ExprTree<DataType>::commuteHelper(ExprTreeNode* p){
    // define temperature stores pointer during swap
    if ( p != 0 ){
        // commute left and right subtree
        
        if( !isDigit(p->dataItem)){
            ExprTreeNode* temp = p->left;
            p->left = p->right;
            p->right = temp;
            commuteHelper(p->right);
            commuteHelper(p->left);
        }
    }
}
    


template <typename DataType>
bool ExprTree<DataType>::isEquivalentHelper(const ExprTreeNode* x, const ExprTreeNode* y) const{
    
    
    // if both are empty,  return true
    // if only one is empty, return false
    if(x==NULL && y == NULL) return true;
    else if (x==NULL || y ==NULL) return false;
    
    else if (x->dataItem != y->dataItem) return false;
    // compare left subtree and right subtree

    
    //otherwise theyre both else so lets continue checking
    
        bool left = isEquivalentHelper(x->left,y->left);
        bool right = isEquivalentHelper(x->right,y->right);
        
    return left && right;
    
    
    
}



#include "show8.cpp"
