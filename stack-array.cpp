#include <stdexcept>
#include <iostream>

class Stack {
private:
	int size, count;
	double * data;

public:
	Stack(int size) :
	  count(0), size(size), data(new double[size]) {}
	  ~Stack() {
		  delete [] data;
	  }

	  void push(double v) {
		  if ( count >= size ) {
			  double * newdata = new double[size*2];

			  memcpy(newdata, data, size*sizeof(double));

			  delete[] data;

			  data = newdata;
			  size = size * 2;
		  }

		data[count] = v;
		count ++;
	  }

	  double pop() {
		  if (count <= 0)
			  throw std::logic_error("Stack is empty");

		  count --;
		  return data[count];
	  }

	  double top() {
		  if (count <= 0)
			  throw std::logic_error("Stack is empty");

		  return data[count-1];
	  }

	  bool empty() {
		  return count == 0;
	  }
};

int main() {
	Stack s(1);
	s.push(23);
	s.push(11);
	s.push(5);

	while (!s.empty())
		std::cout << s.pop() << std::endl;
}
