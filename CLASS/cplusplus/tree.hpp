
#include <iostream>

template <typename T>
struct tree {
	T value;
	tree* left;
	tree* right;
};


template <typename S>
std::ostream& operator<< (std::ostream& out, const tree<S>& t) {
	if (t.left) out << *t.left << " ";
	out << t.value;
	if (t.right) out << " " << *t.right;

	return out;
}

template <typename T>
T sum(const tree<T>& t) {
	T total = t.value;
	if (t.left) {total += sum(*t.left);}
	if (t.right){total += sum(*t.right);}
	return total;
}