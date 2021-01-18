/*  g++ array-basic.cc -o array-basic -Wall */
#include <iostream>

using namespace std;

class IntArray {
  public:

    IntArray(size_t size) {
      m_contents = new int[size];
      m_size = size;
    }

    ~IntArray() {
      cout << "IntArray::~IntArray()" << endl;
      if(m_contents) {
        delete m_contents;
      }
    }

    size_t size() const {
      return m_size;
    }

    int & operator[](size_t index) {
      // O(1)
      return m_contents[index];
    }

    const int operator[](size_t index) const {
      // O(1)
      return m_contents[index];
    }

    int count_instances(int needle) {
      // O(N)
      int count = 0;

      for(size_t index = 0; index < m_size; index++) {
        if(m_contents[index] == needle) {
          count++;
        }
      }

      return count;
    }

  private:

    int *m_contents {nullptr};
    size_t m_size {0};
};

ostream& operator<<(ostream &stream, const IntArray &array) {
  for(size_t pos = 0; pos < array.size(); pos++) {
    stream << array[pos] << ", ";
  }

  return stream;
}

int main(int argc, char ** argv) {
  cout << "Static Array" << endl;

  IntArray array(10);
  cout << "array.size=" << array.size() << endl;
  cout << "array=" << array << endl;
  
  array[1] = 123;
  array[5] = 456;
  array[7] = 123;
  cout << "array=" << array << endl;

  int count;
  count = array.count_instances(123);
  cout << "instances of 123: " << count << endl;

  count = array.count_instances(456);
  cout << "instances of 456: " << count << endl;

  return 0;
}
