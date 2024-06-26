#pragma once
#include <vector>
#include "EfficientList/Include/LinkedList.hpp"

template <class T>
class BinomialHeap {
public:
	BinomialHeap<T>(T element);

	void Insert(T element);

	void Merge(const BinomialHeap<T>& heap);
	

	T getMin() const;
	void extractMin();

	~BinomialHeap<T>();

private:
	
	

	template <class T>
	struct Node {
		T value;
		//Node<T>* parent;
		//Node<T>* left;
		Node<T>* right = nullptr;
		Node<T>* left_child = nullptr;
		int rank;

		Node<T>() : /*parent(nullptr), left(nullptr), */ right(nullptr), left_child(nullptr), rank(0), value(0) {
		}
		Node<T>(T elem) : /*parent(nullptr), left(nullptr),*/ right(nullptr), left_child(nullptr), rank(0), value(elem) {}

		Node<T>(const Node<T>* elem) : rank(elem->rank), value(elem->value) {
			/*
			if (elem->parent)
				if (!(parent = new Node<T>(elem->parent)))
					throw NotEnoughSpaceException("Node constructor: not enough space");
			*/
			/*
			if (elem->left)
				if (!(left = new Node<T>(elem->left)))
					throw NotEnoughSpaceException("Node constructor: not enough space");
			*/
			if (elem->right){
				if (!(right = new Node<T>(elem->right)))
					throw NotEnoughSpaceException("Node constructor: not enough space");
			}
				
			if (elem->left_child)
				if (!(left_child = new Node<T>(elem->left_child)))
					throw NotEnoughSpaceException("Node constructor: not enough space");
		}



		~Node<T>() {
			if (left_child) delete left_child;
			if (right) delete right;
			//if (parent) delete parent;
			//if (left) delete left;
			//if (this) delete this;
			
			//parent = nullptr;
			//left = nullptr;
			right = nullptr;
			left_child = nullptr;
			
		}

	};


	BinomialHeap<T>::Node<T>* minim;
	std::vector<Node<T>*> tree_;

	BinomialHeap<T>(const LinkedList<BinomialHeap<T>::Node<T>*>& list);

	inline BinomialHeap<T>::Node<T>* MergeTrees(Node<T>* main, Node<T>* additional) {
		if (main->value > additional->value) std::swap(main, additional);
		if (!main->rank) {
			if (main->left_child) {
				delete main->left_child;
				main->left_child = nullptr;
			}
			main->left_child = new Node<T>(additional);
			/*if (additional) {
				delete additional;
				additional = nullptr;
			}*/
			//additional->parent = main;
			++main->rank;
			return main;
		}
		additional->right = new Node<T>(main->left_child);
		//main->left_child->left = additional;
		//additional->parent = main;
		if (main->left_child)
		{
			delete main->left_child;
			main->left_child = nullptr;
		}
		main->left_child = new Node<T>(additional);
		if (additional) {
			delete additional;
			additional = nullptr;
		}
		++main->rank;
		return main;
	}
};

template <class T>
BinomialHeap<T>::BinomialHeap<T>(T element) {
	BinomialHeap<T>::Node<T>* current;
	if (!(current = new Node<T>(element)))
		throw NotEnoughSpaceException("BinomialHeap constructor: not enough space");
	minim = current;
	tree_.push_back(current);
}

template <class T>
BinomialHeap<T>::BinomialHeap<T>(const LinkedList<BinomialHeap<T>::Node<T>*>& list) {
	Node<T>* elem;
	//Element<Node<T>*>* current = new Element<Node<T>*>(list.head);
	Element<Node<T>*>* l_current = list.head;
	Element<Node<T>*>* tmp_current = l_current;
	Element<Node<T>*>* last = nullptr;
	//if (current) minim = new Node<T>(current->info);//this prevents error when list.size() == 0
	while (l_current) {
		elem = new Node<T>(l_current->info);
		if (minim && elem->value <= minim->value) {
			 delete minim;
			minim = elem;
		}
		this->tree_.push_back(elem);
		tmp_current = l_current;
		l_current = XOR(l_current->diff, last);
		last = tmp_current;
	}

}


template <class T>
void BinomialHeap<T>::Insert(T element) {
	BinomialHeap heap(element);
	this->Merge(heap);
}

template <class T>
void BinomialHeap<T>::Merge(const BinomialHeap<T>& heap) {
	size_t i = 0;
	size_t j = 0;

	LinkedList<BinomialHeap<T>::Node<T>*> new_heap;
	Node<T>* elem;
	while (i < tree_.size() && j < heap.tree_.size()) {
		if (tree_[i]->rank == heap.tree_[j]->rank) {
			tree_[i] = MergeTrees(tree_[i], heap.tree_[j]);
			++j;
			continue;
		}
		if (tree_[i]->rank < heap.tree_[j]->rank) {
			elem = new Node<T>(tree_[i]);
			new_heap.push_back(elem);
			++i;
			continue;
		}
		if (tree_[i]->rank > heap.tree_[j]->rank) {
			elem = new Node<T>(heap.tree_[j]);
			new_heap.push_back(elem);
			++j;
		}
	}

	while (i < tree_.size()) {
		elem = new Node<T>(tree_[i++]);
		new_heap.push_back(elem);
	}

	while (j < heap.tree_.size()) {
		elem = new Node<T>(heap.tree_[j++]);
		new_heap.push_back(elem);
	}
	
	//bool flag = true;
	//короче очень плохая реализация, так как происходит просто ядерное удаление элементов
	//надо делать вершины на двусвязном списке
	Element<Node<T>*>* current = new_heap.head;
	Element<Node<T>*>* last;
	Element<Node<T>*>* tmp;
	//while (flag) {
		//flag = false;

		if (new_heap.head)
			current = new_heap.head->diff;
		last = new_heap.head;

		while (current) {
			if (current->info->rank == last->info->rank) {
				//flag = true;
				/*
				if (last->info->value > current->info->value) {
					std::swap(last, current);
				}
				tmp = last->info;
				delete last->info;
				*/
				last->info = MergeTrees(last->info, current->info);
				tmp = XOR(current->diff, last);// next to current
				last->diff = XOR(XOR(last->diff, current), tmp);
				if (tmp) {
					tmp->diff = XOR(XOR(tmp->diff, current), last);
				}
				if (current == new_heap.tail) {
					new_heap.tail = last;//not necessary as I don't use new_heap anymore after tree_ = new_heap
				}
				delete current;
				current = tmp;
				continue;
			}
			tmp = current;

			current = XOR(current->diff, last);
			last = tmp;
		}
	//}
	for (int i = 0; i < tree_.size(); ++i) {
		delete tree_[i];
	}
	tree_.resize(new_heap.size());
	if (new_heap.head)
		minim = new_heap[0];
	
	for (int i = 0; i < new_heap.size(); ++i) {
		//std::cout << '1' << typeid(new_heap[i]).name() << '\n';
		//std::cout << '2' << typeid(new_heap[i]).name() << '\n';
		
		if(!(tree_[i] = new Node<T>(new_heap[i])))
			throw NotEnoughSpaceException("BinomialHeap Merge(): not enough space");
		
		//tree_[i] = new_heap[i];
		//minim = tree_[i] * (tree_[i] <= minim) + minim * (minim < tree_[i]);
		if (tree_[i]->value <= minim->value) {
			minim = tree_[i];
		}
	}
}

/*
template <class T> 
void BinomialHeap<T>::Merge(const LinkedList<BinomialHeap<T>::Node<T>*>& heap) {

}
*/
template <class T>
T BinomialHeap<T>::getMin() const {
	if (!minim)
		throw InvalidLengthException("BinomialHeap getMin(): no elements");
	return minim->value;
}

template <class T>
void BinomialHeap<T>::extractMin() {
	if (!minim)
		throw InvalidLengthException("BinomialHeap extractMin(): no elements");
	LinkedList<BinomialHeap<T>::Node<T>*> new_heap;
	Node<T>* cur = new Node<T>(minim->left_child);
	Node<T>* tmp_cur = cur;
	while (cur->right) {
		new_heap.push_front(cur);
		//cur->parent = nullptr;
		cur = new Node<T>(cur->right);
		tmp_cur->right = nullptr;
		//if (tmp_cur->left)
		//	tmp_cur->left->right = nullptr;
		//tmp_cur->left = nullptr;
		tmp_cur = cur;
	}
	new_heap.push_front(cur);
	auto it = std::find(tree_.begin(), tree_.end(), minim);
	if (it == tree_.end()) std::cout << "How can that be?";
	tree_.erase(it);
	BinomialHeap<T> heap(new_heap);
	this->Merge(heap);
}

template <class T>
BinomialHeap<T>::~BinomialHeap<T>() {
	for (int i = 0; i < tree_.size(); ++i) {
		delete tree_[i];
	}
}