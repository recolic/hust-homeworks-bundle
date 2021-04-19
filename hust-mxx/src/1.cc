#include "utils.hpp"
#include <climits>
#include <exception>
#include <fstream>
#include <iostream>
#include <new>
#include <string>

typedef struct _STACK {
  int *elements;
  int max;
  int pos;
} STACK;
void initSTACK(STACK *const p, int m) {
  p->elements = new int[m];
  p->max = m;
  p->pos = 0;
}

void initSTACK(STACK *const p, const STACK &s) {
  p->elements = new int[s.max];
  p->pos = s.pos;
  for (int i = 0; i < s.pos; ++i)
    p->elements[i] = s.elements[i];
}

int size(const STACK *const p) { return p->max; }

int howMany(const STACK *const p) { return p->pos; }

int getelem(const STACK *const p, int x) {
  if (x >= p->max)
    throw out_of_range("out of range");
  return p->elements[x];
}

STACK *const push(STACK *const p, int e) {
  if (p->pos == p->max)
    throw logic_error("stack full");
  p->elements[p->pos] = e;
  ++p->pos;
  return p;
}

STACK *const pop(STACK *const p, int &e) {
  if (p->pos == 0)
    throw logic_error("stack empty");
  e = p->elements[--p->pos];
  return p;
}

STACK *const assign(STACK *const p, const STACK &s) {
  p->pos = s.pos;
  p->max = s.max;

  delete p->elements;
  p->elements = new int[p->pos];

  for (int i = 0; i < s.pos; ++i)
    p->elements[i] = s.elements[i];

  return p;
}

void print(const STACK *const p, std::stringstream &cout) {
  for (int i = 0; i < p->pos; ++i) {
    if (i != p->pos - 1)
      cout << p->elements[i] << "  ";
    else
      cout << p->elements[i];
  }
  cout << flush;
}

void destroySTACK(STACK *const p) {
  delete[] p->elements;
  p->elements = nullptr;
  p->pos = 0;
  p->max = 0;
}
int main(int argc, char *argv[]) {
  string arg;
  int number;
  RMXX_BEGIN_MAIN

  STACK *stack = new STACK;

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

        initSTACK(stack, number);
        cout << "S  " << number;
      } else if (arg == "-I" || arg == "-i") {
        cout << "I";

        for (++i; i < argc; ++i) {
          arg = string(argv[i]);

          if (!convertToInt(arg, number)) {
            break;
          }
          push(stack, number);
        }
        if (i != argc)
          --i;

        if (howMany(stack)) {
          cout << "  ";
          print(stack, cout);
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
          pop(stack, garbage);
        }

        if (howMany(stack)) {
          cout << "  ";
          print(stack, cout);
        }

      } else if (arg == "-C" || arg == "-c") {
        STACK *newStack = new STACK;
        initSTACK(newStack, *stack);
        stack = newStack;

        cout << "C";
        if (howMany(stack)) {
          cout << "  ";
          print(stack, cout);
        }
      } else if (arg == "-A" || arg == "-a") {
        CHECK_IF_LAST_ARG

        arg = string(argv[++i]);
        if (!convertToInt(arg, number)) {
          cerr << "Error: cannot convert " << arg << " to int" << endl;
          return 1;
        }

        STACK *newStack = new STACK;
        initSTACK(newStack, number);
        assign(newStack, *stack);
        stack = newStack;

        cout << "A";
        if (howMany(stack)) {
          cout << "  ";
          print(stack, cout);
        }

      } else if (arg == "-N" || arg == "-n") {
        cout << "N  " << howMany(stack);

      } else if (arg == "-G" || arg == "-g") {
        CHECK_IF_LAST_ARG

        arg = string(argv[++i]);
        if (!convertToInt(arg, number)) {
          cout << "Error: cannot convert " << arg << " to int" << endl;
        }

        cout << "G  " << getelem(stack, number);
      } else {
        cerr << "Wrong parameter: " << arg << endl;
        return 1;
      }

      if (i != argc - 1)
        cout << "  ";
    }
  } catch (logic_error &err) {
    cout << "  E";
  }
  RMXX_END_MAIN(1)
  return 0;
}
