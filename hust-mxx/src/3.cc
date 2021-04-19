#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

class STACK {
private:
  int *const elems;
  const int max;
  int pos;

public:
  STACK(int m) : elems(new int[m]), max(m), pos(0) {}

  STACK(const STACK &s) : elems(new int[s.max]), max(s.max), pos(s.pos) {
    for (int i = 0; i < pos; ++i)
      elems[i] = s.elems[i];
  }

  virtual int size() const { return max; }

  virtual operator int() const { return pos; }

  virtual int operator[](int x) const {
    if (x >= pos)
      throw std::out_of_range("index out of range");
    return elems[x];
  }

  virtual STACK &operator<<(int e) {
    if (pos == max)
      throw std::logic_error("full stack");
    elems[pos] = e;
    ++pos;
    return *this;
  }

  virtual STACK &operator>>(int &e) {
    if (pos == 0)
      throw std::logic_error("empty stack");
    e = elems[--pos];
    return *this;
  }

  virtual STACK &operator=(const STACK &s) {

    int *ref = const_cast<int *>(elems);
    delete ref;
    ref = new int[s.max];
    int *num = const_cast<int *>(&max);
    *num = s.max;
    pos = s.pos;

    for (int i = 0; i < pos; ++i)
      elems[i] = s.elems[i];
    return *this;
  }

  virtual void print(std::stringstream &cout) const {
    for (int i = 0; i < pos; ++i) {
      if (i != pos - 1)
        cout << elems[i] << "  ";
      else
        cout << elems[i];
    }
    cout << flush;
  }

  virtual ~STACK() { delete[] elems; }
};

int main(int argc, char *argv[]) {

  string arg;
  int number;

  RMXX_BEGIN_MAIN

  STACK *stack = nullptr;

#define CHECK_IF_LAST_ARG                                                      \
  if (i == argc - 1) {                                                         \
    cerr << "paramter not found after: " << arg << endl;                       \
    return 1;                                                                  \
  }

  try {
    for (int i = 1; i < argc; ++i) {
      arg = string(argv[i]);
      if (arg == "-S" || arg == "-s") {
        CHECK_IF_LAST_ARG;

        arg = string(argv[++i]);
        if (!convertToInt(arg, number)) {
          cerr << "Error: cannot convert " << arg << " to int" << endl;
          return 1;
        }

        stack = new STACK(number);
        cout << "S  " << number;
      } else if (arg == "-I" || arg == "-i") {
        cout << "I";

        for (++i; i < argc; ++i) {
          arg = string(argv[i]);

          if (!convertToInt(arg, number)) {
            break;
          }
          (*stack) << number;
        }
        if (i != argc)
          --i;

        if (int(*stack)) {
          cout << "  ";
          stack->print(cout);
        }
      } else if (arg == "-O" || arg == "-o") {
        CHECK_IF_LAST_ARG

        cout << "O";
        arg = string(argv[++i]);
        if (!convertToInt(arg, number)) {
          cerr << "Error: cannot convert " << arg << " to int" << endl;
          return 1;
        }

        int garbage;
        for (int j = 0; j < number; ++j) {
          (*stack) >> garbage;
        }

        if (int(*stack)) {
          cout << "  ";
          stack->print(cout);
        }

      } else if (arg == "-C" || arg == "-c") {
        STACK *newStack = new STACK(*stack);
        stack = newStack;

        cout << "C";
        if (int(*stack)) {
          cout << "  ";
          stack->print(cout);
        }
      } else if (arg == "-A" || arg == "-a") {
        CHECK_IF_LAST_ARG

        arg = string(argv[++i]);
        if (!convertToInt(arg, number)) {
          cerr << "Error: cannot convert " << arg << " to int" << endl;
          return 1;
        }

        STACK *newStack = new STACK(number);
        *newStack = *stack;
        stack = newStack;

        cout << "A";
        if (int(*stack)) {
          cout << "  ";
          stack->print(cout);
        }

      } else if (arg == "-N" || arg == "-n") {
        cout << "N  " << int(*stack);

      } else if (arg == "-G" || arg == "-g") {
        CHECK_IF_LAST_ARG

        arg = string(argv[++i]);
        if (!convertToInt(arg, number)) {
          cerr << "Error: cannot convert " << arg << " to int" << endl;
          return 1;
        }

        cout << "G  " << (*stack)[number];

      } else {
        cerr << "Wrong parameter: " << arg << endl;
        return 1;
      }

      if (i != argc - 1)
        cout << "  ";
    }
  } catch (logic_error &error) {
    cout << "  E" << endl;
  }
  RMXX_END_MAIN(3)
  return 0;
}
