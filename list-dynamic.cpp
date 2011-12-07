#include <iostream>
#include <stdexcept>

template <typename T>
struct Elem {
	T value;
	Elem<T> * next;
	Elem<T> * prev;
};

template <typename T>
class List {
private:
	Elem<T> * first;
	Elem<T> * last;

public:
	class Iterator {
	public:
		Elem<T> * cur;

	public:
		Iterator(Elem<T> * cur) : cur(cur) {}

		T & operator * () {
			return cur->value;
		}

		void operator ++ () {
			cur = cur->next;
		}

		bool operator == (Iterator it) {
			return cur == it.cur;
		}

		bool operator != (Iterator it) {
			return cur != it.cur;
		}

		Iterator operator +(int offset) {
			Iterator copy = *this;
			for ( int i = 0; i < offset && copy.cur != 0; ++ i )
				copy ++;
			return copy;
		}

	};

	List() : first(0), last(0) {}

	void add(T value) {
		if ( last == 0 ) {
			Elem<T> * el = new Elem<T>();
			el->value = value;
			el->prev = 0;
			el->next = 0;

			first = el;
			last = el;
		} else {
			Elem<T> * el = new Elem<T>();
			el->value = value;
			el->prev = last;
			el->next = 0;

			last->next = el;
			last = el;
		}
	}

	void insert(Iterator it, T value) {
		if (it.cur == 0) {
			add(value);
		} else if (it.cur == first) {
			Elem<T> * el = new Elem<T>();
			el->value = value;
			el->prev = 0;
			el->next = first;

			first->prev = el;
			first = el;
		} else {
			Elem<T> * prev = it.cur->prev;
			Elem<T> * next = it.cur;

			Elem<T> * el = new Elem<T>();
			el->value = value;
			el->prev = prev;
			el->next = next;

			prev->next = el;
			next->prev = el;
		}
	}

	void remove() {
		if ( last == 0 )
			throw std::logic_error("List is empty");

		if ( first == last ) {
			delete first;
			first =0;
			last = 0;
		} else {
			last = last->prev;
			delete last->next;
			last->next = 0;
		}
	}


	Iterator begin() {
		return Iterator(first);
	}

	Iterator end() {
		return Iterator(0);
	}

};

int main() {

	List<double> list;

	list.add(1);
	list.add(2.5);
	list.add(-2.2);
	list.insert(list.begin() + 1, 3);
	list.insert(list.begin(), 0);
	list.remove();

	for (List<double>::Iterator elem = list.begin(); elem != list.end(); ++ elem) {
		std::cout << *elem << std::endl;
	}

}
