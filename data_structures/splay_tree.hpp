#ifndef SPLAY_TREE_HPP
#define SPLAY_TREE_HPP
#include <map>
#include <set>
#include <iostream>
#include <utility>
#include <algorithm>

#define dbg(x)  std::cout << #x << " = " << x << std::endl

struct NodeSP  {
	int val;
	NodeSP  * l, * r;
	
	NodeSP () : val(0), l(nullptr), r(nullptr) {} ;
	NodeSP (int c, NodeSP  * L, NodeSP  * R) : val(c), l(L), r(R){} ;
};

NodeSP  * rotateRight(NodeSP  * n){
	NodeSP  * aux = n->l;
	n->l = aux->r;
	aux->r = n;
	return aux;
}

NodeSP  * rotateLeft(NodeSP  * n){
	NodeSP  * aux = n->r;
	n->r = aux->l;
	aux->l = n;
	return aux;
}
 
NodeSP  * minimo(NodeSP  * a){
	if(a->l == nullptr)
		return a;
	else
		return minimo(a->l);
}

NodeSP  * splay(NodeSP  * a, NodeSP  * topo, bool isRoot = true){
	if(a == nullptr || a == topo) return a;
	if(a->val > topo->val){
		a->l = splay(a->l, topo, false);

		if(a->l->l == topo) {
			a = rotateRight(a);
			a = rotateRight(a);
		}
		else if(a->l->r == topo) {
			a->l = rotateLeft(a->l);
			a = rotateRight(a);
		}
		else if(isRoot && a != topo) {
			a = rotateRight(a);
		}
	}
	else{
		a->r = splay(a->r, topo, false);
		if(a->r->l == topo) {
			a->r = rotateRight(a->r);
			a = rotateLeft(a);
		}
		else if(a->r->r == topo) {
			a = rotateLeft(a);
			a = rotateLeft(a);
		}
		else if(isRoot && a != topo){
			a = rotateLeft(a);
		}
	}

	return a;
}

NodeSP  * search(NodeSP  * a, int val){
	if(a == nullptr) return nullptr;
	
	if(a->val == val)
		return a;
	if(a->val > val)
		return search(a->l, val);
	else 
		return search(a->r, val);
}

bool searchSplay(NodeSP  ** a, int val){
	NodeSP  * aux = search(*a, val);

	if(aux != nullptr) {
		*a = splay(*a, aux);
		return true;
	}
	else return false;
}

NodeSP  * insere(NodeSP  * a, int val){
	acessados++;
	if(a == nullptr) 
		return new NodeSP (val, nullptr, nullptr);
	
	if(a->val > val)
		a->l = insere(a->l, val);
	else 
		a->r = insere(a->r, val);
	return a;
}

NodeSP  * insereSplay(NodeSP  * a, int val){
	a = insere(a, val);
	return splay(a, search(a, val));
}


NodeSP  * deletaRaiz(NodeSP  * root){
	NodeSP  * p, * q;
	if(root->r == nullptr){
		p = root->l;
		delete root;
		return p;
	}

	// Procura o menor cara na subárovre da direita
	p = root, q = root->r;
	while(q->l != nullptr){
		p = q;
		q = q->l;
	}

	if(p != root){
		p->l = q->r;
		q->r = root->r;
	}

	q->l = root->l;
	delete root;
	return q;
}

NodeSP  * deletaSplay(NodeSP  * a, int val){
	NodeSP  * root = a, * pai = nullptr; // "it" é o mesmo que o "a" na árvore nova
	
	while(a != nullptr && a->val != val){
		if(a->val > val){
			pai = a;
			a = a->l;
		}
		else if(a->val < val){
			pai = a;
			a = a->r;
		}
	}

	if(a == nullptr)
		return root;
	

	if(pai->l == a) pai->l = deletaRaiz(a);
	else pai->r = deletaRaiz(a);

	return splay(root, pai);
}

void print(const std::string& prefix, const NodeSP * node , bool isLeft){
    if( node  != nullptr ){
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node 
        std::cout << node ->val << std::endl;

        // enter the next tree level - left and right branch
        print( prefix + (isLeft ? "│   " : "    "), node ->l, true);
        print( prefix + (isLeft ? "│   " : "    "), node ->r, false);
    }
}

void print(const NodeSP * node ){
    print("", node , false);    
}

#endif