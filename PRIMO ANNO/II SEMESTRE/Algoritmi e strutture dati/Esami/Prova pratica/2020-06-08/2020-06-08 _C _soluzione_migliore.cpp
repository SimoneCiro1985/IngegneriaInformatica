//NOTA: A differenza dell'altra soluzione proposta, questa è un pò più complessa ma ha complessità minore -> O(logn) contro O(n)

#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <fstream>
#include <math.h>       /* floor */
#include <stdlib.h>
#include <cmath>        /* pow  */

using namespace std;

struct Node
{
    int value;
    Node * left;
    Node * right;

    Node( int i ): value(i) , left(NULL) , right(NULL) {}
};

class BinTree
{
    Node * root_;
public:

    BinTree() { root_ = NULL ; }

    Node * getRoot() { return root_; cout << "getRoot" << endl;}

    void insert( int i )
    {
        Node * node = new Node(i);

        Node * pre = NULL;
        Node * post = root_;
        while( post != NULL)
        {
            pre = post;
            if( i <= post->value )
            {
                post = post->left;
            }
            else
            {
                post = post->right;
            }
        }

        if( pre == NULL )
            root_ = node;
        else if( i <= pre->value )
        {
            pre->left = node;
        }
        else
        {
            pre->right = node;
        }
        return;

    }
};

// --------------------------METODO ESTERNO DA AGGIUNGERE--------------------------

int n_conformi(Node* tree, int h){
    if(!tree)
        return 0;
    if(tree->value%h <= 1)
        return 1 + n_conformi(tree->left,h+1) + n_conformi(tree->right,h+1);
    return n_conformi(tree->left,h+1) + n_conformi(tree->right,h+1);
}

// --------------------------------------------------------------------------------

void min_max(Node* tree, int & min, int & max, bool direzione, bool primo){
    //la variabile "direzione dice in che verso sto scendendo (se dx o sx)
    //la variabile "primo" mi dice se sono nella prima chiamata o no della funzione.
    //Infatti, l'unica funzione che può lanciare anche la discesa verso sinistra è la prima

    if(!tree){
        min = max = -1;
        return;
    }

    if(primo){
        primo = 0;
        if(!tree->right)
            max = tree->value;
        else
            min_max(tree->right, min, max,1,0); //Lancio la discesa verso dx, senza "diritti di amministratore"

        if(!tree->right)
            min = tree->value;
        else min_max(tree->left, min, max, 0,0);
    }
    else{
        //MASSIMO
        if(direzione == 1){
            if(!tree->right)
                max = tree->value;
            else
                min_max(tree->right, min, max,direzione,primo);
        }
        //MINIMO
        else{
            if(!tree->left)
                min = tree->value;
            else
                min_max(tree->left, min, max,direzione,primo);
        }
    }
}

//=======================================MAIN======================================

int main()
{
    int N = 7;
    int x ;
    BinTree albero ;
    int arr[] = {7,3,9,2,4,8,11};

//    cin >> N ;

    // Inserimento elementi nell' albero
    for(int i=0 ; i<N ; ++i )   {
//        cin >> x;
        albero.insert(arr[i]);
    }

    // --------------------------CHIAMATA AL METODO----------------------------

    int MINIMO = 1000;
    int MASSIMO = 0;
    min_max(albero.getRoot(),MINIMO, MASSIMO,1,1);
    cout << MINIMO << ", " << MASSIMO << endl;
    // ------------------------------------------------------------------------
}
