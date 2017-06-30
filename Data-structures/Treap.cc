#include <bits/stdc++.h>
using namespace std;

default_random_engine generator;
uniform_int_distribution<int> distribution(0,100000);

template<class T>
struct Node {
	Node *left, *right, *parent; // if parent needed.
	T order, priority, count;

	//constructor
	Node (T x) : order(x), priority(distribution(generator)), count(1) {
		left = right = parent = nullptr;
	}
};

template<class T>
struct Treap {
	inline int Cardinality(Node<T>* N) {
		return (N ? N->count : 0); //mira si es != nullptr
	}
	
	inline void SetParent (Node<T>* N, Node<T>* P) {
		if(N) N->parent = P;
	}
	
	void Update(Node<T>* N) { //Update cardinality and parent
		if (!N) return;
		N->count = 1 + Cardinality(N->left) + Cardinality(N->right);
		setp(N->left, N);
		setp(N->right, N);
	}
	
	//make the higher priority node on top, merge recursively
	//N1 seems to go to the left by default
	Node<T>* Merge(Node<T>* N1, Node<T>* N2) {
		if (!N1) return N2;
		if (!N2) return N1;
		if (N1->priority >= N2->priority) {
			N1->right = Merge(N1->right, N2);
			Update(N1);
			return N1;
		} else {
			N2->left = Merge(N1, N2->left);
			Update(N2);
			return N2;
		}
	}
	
	// leaves on the left all nodes less than x.
	pair<Node<T>*, Node<T>*> Split_by_Order(Node<T>* N, T x) {
		if (!N) return {nullptr, nullptr};
		if (N->order < x) {
			auto p = Split_by_Order(N->right, x);
			N->right = p.first;
			update(N);
			setp(N, nullptr);
			return {N, p.second};
		} else {
			auto p = Split_by_Order(N->left, x);
			N->left = p.second;
			update(N);
			setp(N, nullptr);
			return {p.first, N};
		}
	}
	
	pair<Node<T>*, Node<T>*> Split_by_Cardinality(Node<T>* N, T x) {
		if (!N) return {nullptr, nullptr};
		if (Cardinality(N->left) + 1 <= x) {
			auto p = Split_by_Cardinality(N->right, x - Cardinality(N->left) - 1);
			N->right = p.first;
			update(N);
			setp(N, nullptr);
			return {N, p.second};
		} else {
			auto p = Split_by_Cardinality(N->left, x);
			N->left = p.second;
			update(N);
			setp(N, nullptr);
			return {p.first, N};
		}
	}

	Node<T> * Insert(Node<T>* N1, Node<T>* N2) {
		auto p = split(N1, N2->order);
		N1 = merge(p.first, N2);
		N1 = merge(N1, p.second);
		return N1;
	}
	
	int Count(Node<T>* N, int x) {
		if(!N) return 0;
		if(N->order <= x) return 1 + Cardinality(N->left) + Count(N->right, x);
		return Count(N->left,x);
	}
	
	Node<T>* UpdateNode(Node<T>* R, Node<T>* N, T nx) {
		setp(N->left, nullptr);
		setp(N->right, nullptr);
		auto m = merge(N->left, N->right);
		auto p = N->parent;
		
		N->left = N->right = N->parent = nullptr;
		N->order = nx;
		Update(N);
		if(p) {
			p->left == N? p->left = m : p->right = m;
			if(m) m->parent = p;
			while(p) {
				Update(p);
				p = p->parent;
			}
		} else {
			R = m;
		}
		return Insert(R,N);
	}
};

int main() {

}
