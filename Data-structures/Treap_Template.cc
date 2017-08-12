#include <bits/stdc++.h>
using namespace std;

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);
uniform_int_distribution<int> distribution(0,1000000);

template<class T>
struct Node {
	Node *left, *right, *parent;
	T order, priority, count;
	//constructor
	Node (T x) : order(x), priority(distribution(generator)), count(1) {
		left = right = parent = nullptr;
	}
};

//returns the cardinality of a Node
template<class T>
inline int Cardinality(Node<T>* N) {
	return (N ? N->count : 0);
}

//Makes P the parent of N
template<class T>
inline void SetParent (Node<T>* N, Node<T>* P) {
	if(N) N->parent = P;
}

//Updates a node which has a modified son
//it re-sets the cardinality and adjusts the parents
template<class T>
void Update(Node<T>* N) {
	if (!N) return;
	N->count = 1 + Cardinality(N->left) + Cardinality(N->right);
	SetParent(N->left, N);
	SetParent(N->right, N);
}

//make the higher priority node on top, Merge recursively
//N1 seems to go to the left by default
template<class T>
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

// Splits the Tree into trees with order > x and order <= x
// first is x <= x, second > x
// You go Splitting  recursively and reattaching edges to the
// First node you encounter of the same type.
template<class T>
pair<Node<T>*, Node<T>*> Split_by_Order(Node<T>* N, T x) {
	if (!N) return {nullptr, nullptr};
	if (N->order < x) {
		auto p = Split_by_Order(N->right, x);
		N->right = p.first;
		Update(N);
		SetParent(N, (Node<T>*)nullptr);
		return {N, p.second};
	} else {
		auto p = Split_by_Order(N->left, x);
		N->left = p.second;
		Update(N);
		SetParent(N, (Node<T>*)nullptr);
		return {p.first, N};
	}
}


//Same as above, it simply gets the first x elements.
template<class T>
pair<Node<T>*, Node<T>*> Split_by_Cardinality(Node<T>* N, T x) {
	if (!N) return {(Node<T>*)nullptr, (Node<T>*)nullptr};
	if (Cardinality(N->left) + 1 <= x) {
		auto p = Split_by_Cardinality(N->right, x - Cardinality(N->left) - 1);
		N->right = p.first;
		Update(N);
		SetParent(N, (Node<T>*)nullptr);
		return {N, p.second};
	} else {
		auto p = Split_by_Cardinality(N->left, x);
		N->left = p.second;
		Update(N);
		SetParent(N, (Node<T>*)nullptr);
		return {p.first, N};
	}
}

//Inserts N2 into N1
//It divides N1 into 2 Treaps, and merges with the Treap of
//lesser order, then reattaches the other Treap
template<class T>
Node<T> * Insert(Node<T>* N1, Node<T>* N2) {
	auto p = Split_by_Order(N1, N2->order);
	N1 = Merge(p.first, N2);
	N1 = Merge(N1, p.second);
	return N1;
}

//Returns the number of nodes such that order < x
template<class T>
int Count(Node<T>* N, int x) {
	if(!N) return 0;
	if(N->order <= x) return 1 + Cardinality(N->left) + Count(N->right, x);
	return Count(N->left,x);
}

//Updates a Node
//Strips the 2 sons of N and merges them into one treap
//saves the parent of N and completely resets N(except for priority)
//Reattaches the splitted sons into the parent, updates until we reach root
//if N was the root we make the merged sons the Root
//Now we insert the updated N
template<class T>
Node<T>* UpdateNode(Node<T>* &R, Node<T>* N, T nx) {
	SetParent(N->left, (Node<T>*)nullptr);
	SetParent(N->right, (Node<T>*)nullptr);
	auto m = Merge(N->left, N->right);
	auto p = N->parent;

	N->left = N->right = N->parent = (Node<T>*)nullptr;
	N->order = nx;
	Update(N);
	if(p) {
		p->left == N ? p->left = m : p->right = m;
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

//Deletes a node
//Same as above but we don't reinsert
template<class T>
Node<T>* Delete(Node<T>* R, Node<T>* N) {
	SetParent(N->left, (Node<T>*)nullptr);
	SetParent(N->right, (Node<T>*)nullptr);
	auto m = Merge(N->left, N->right);
	auto p = N->parent;

	if(p) {
		p->left == N ? p->left = m : p->right = m;
		if(m) m->parent = p;
		while(p) {
			Update(p);
			p = p->parent;
		}
	} else {
		R = m;
	}
}

void dfs(Node<int>* x, int d) {
	if(x) {
		cout << d << ": order: " << x->order << " priority: " << x->priority <<
		" Cardinality: " << Cardinality(x) << ' ' << endl;
		dfs(x->left, d+1);
		dfs(x->right, d+1);
	}
}

int main() {
	srand(time(NULL));
	int n;
	cin >> n;
	vector<Node<int>*> nodes(n);
	Node<int>* Root = (Node<int>*)nullptr;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		Node<int>* N = new Node<int>(x);
		nodes[i] = N;
		Root = Insert(Root, N);
	}
	int m;
	cin >> m;
	while(m--) {
		int k;
		int x;
		cin >> k >> x;
		auto T = nodes[k-1];
		Root = UpdateNode(Root, T, x);
	}

	dfs(Root, 1);
}
