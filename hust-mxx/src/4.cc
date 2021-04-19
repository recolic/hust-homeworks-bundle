#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

class STACK {
private:
  int *const elems;

  const int max;

  int pos;

public:
  STACK(int m) : elems(new int[m]), max(m), pos(0) {}

  STACK(const STACK &s) : elems(new int[s.max]), max(s.max) {
    pos = s.pos;
    for (int i = 0; i < pos; ++i)
      elems[i] = s.elems[i];
  }

  virtual int size() const { return max; }

  virtual operator int() const { return pos; }

  virtual int operator[](int x) const {
    if (x >= pos)
      throw std::logic_error("array index out of range");
    return elems[x];
  }

  virtual STACK &operator<<(int e) {
    if (pos == max)
      throw std::logic_error("array is full, cannot push");
    elems[pos] = e;
    ++pos;
    return *this;
  }

  virtual STACK &operator>>(int &e) {
    if (pos == 0)
      throw std::logic_error("pop from empty stack");
    e = elems[--pos];
    return *this;
  };

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

class QUEUE : public STACK {
private:
  STACK s2;

public:
  QUEUE(int m) : STACK(m), s2(m) {}

  QUEUE(const QUEUE &s) : STACK(static_cast<STACK>(s)), s2(s.s2) {}

  virtual operator int() const {
    return STACK::operator int() + s2.operator int();
  }

  virtual int full() const {
    return STACK::operator int() == STACK::size() && !s2.operator int();
  }

  virtual int operator[](int x) const {
    if (x >= STACK::operator int() + s2.operator int())
      throw std::logic_error("trying to get elem outside of queue");

    if (x >= int(s2))
      return STACK::operator[](x - int(s2));
    else
      return s2[int(s2) - x - 1];
  }

  virtual QUEUE &operator<<(int e) {

    if (STACK::operator int() == STACK::size()) {
      int temp;
      int origSize = STACK::operator int();
      for (int i = 0; i < origSize; ++i) {
        STACK::operator>>(temp);
        s2 << temp;
      }
    }

    STACK::operator<<(e);
    return *this;
  }

  virtual QUEUE &operator>>(int &e) {
    if (int(s2)) {
      s2 >> e;
    } else {
      int temp;
      int origSize = STACK::operator int();
      for (int i = 0; i < origSize - 1; ++i) {
        STACK::operator>>(temp);
        s2 << temp;
      }
      STACK::operator>>(e);
    }
    return *this;
  }

  virtual QUEUE &operator=(const QUEUE &s) {
    STACK::operator=(static_cast<STACK>(s));
    s2 = s.s2;
    return *this;
  }

  virtual void print(std::stringstream &cout) const {

    for (int i = 0; i < int(s2); ++i) {
      if (i)
        cout << "  ";
      cout << s2[int(s2) - i - 1];
    }

    if (int(s2) && STACK::operator int())
      cout << "  ";

    for (int i = 0; i < STACK::operator int(); ++i) {
      if (i)
        cout << "  ";
      cout << STACK::operator[](i);
    }

    cout << flush;
  }

  virtual ~QUEUE() {}
};

using namespace std;

int main(int argc, char *argv[]) {

  if (argc == 1) {
    int menNum, womenNum, m, f;

    while (true) {
      cout << "How many men? " << flush;
      cin >> menNum;
      if (cin.eof() || cin.bad()) {
        continue;
      } else if (cin.fail()) {
        cout << "wrong input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      } else if (!isPrime(menNum)) {
        cout << "prime number wanted" << endl;
      } else
        break;
    }

    while (true) {
      cout << "How many women? " << flush;
      cin >> womenNum;
      if (cin.eof() || cin.bad()) {
        continue;
      } else if (cin.fail()) {
        cout << "wrong input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      } else if (!isPrime(womenNum)) {
        cout << "prime number wanted" << endl;
      } else if (womenNum == menNum) {
        cout << "wanted women != men " << endl;
      } else
        break;
    }

    while (true) {
      cout << "m (1 <= m <= number of men)? " << flush;
      cin >> m;
      if (cin.eof() || cin.bad()) {
        continue;
      } else if (cin.fail()) {
        cout << "wrong input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      } else if (m <= 0 || m > menNum) {
        cout << "out of range" << endl;
      } else
        break;
    }

    while (true) {
      cout << "f (1 <= f <= number of women)? " << flush;
      cin >> f;
      if (cin.eof() || cin.bad()) {
        continue;
      } else if (cin.fail()) {
        cout << "wrong input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      } else if (f <= 0 || f > womenNum) {
        cout << "out of range" << endl;
      } else
        break;
    }

    QUEUE queueMen(2 * menNum + 1), queueWomen(2 * womenNum + 1);
    for (int i = 0; i < menNum; ++i)
      queueMen << i + 1;
    for (int i = 0; i < womenNum; ++i)
      queueWomen << i + 1;

    int currentMan, currentWoman, counter = 1;
    while (1) {
      queueMen >> currentMan;
      queueWomen >> currentWoman;
      if (currentMan == m && currentWoman == f) {
        cout << "round " << counter << endl;
        break;
      }
      queueMen << currentMan;
      queueWomen << currentWoman;
      ++counter;
    }
    return 0;
  } else {

    string arg;
    int number;

    RMXX_BEGIN_MAIN

    QUEUE *queue = nullptr;
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

          queue = new QUEUE(number);
          cout << "S  " << number;
        } else if (arg == "-I" || arg == "-i") {
          cout << "I";

          for (++i; i < argc; ++i) {
            arg = string(argv[i]);

            if (!convertToInt(arg, number)) {
              break;
            }
            (*queue) << number;
          }
          if (i != argc)
            --i;

          if (int(*queue)) {
            cout << "  ";
            queue->print(cout);
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
            (*queue) >> garbage;
          }

          if (int(*queue)) {
            cout << "  ";
            queue->print(cout);
          }

        } else if (arg == "-C" || arg == "-c") {
          QUEUE *newQueue = new QUEUE(*queue);
          queue = newQueue;

          cout << "C";
          if (int(*queue)) {
            cout << "  ";
            queue->print(cout);
          }
        } else if (arg == "-A" || arg == "-a") {
          CHECK_IF_LAST_ARG

          arg = string(argv[++i]);
          if (!convertToInt(arg, number)) {
            cerr << "Error: cannot convert " << arg << " to int" << endl;
            return 1;
          }

          QUEUE *newQueue = new QUEUE(number);
          *newQueue = *queue;
          queue = newQueue;

          cout << "A";
          if (int(*queue)) {
            cout << "  ";
            queue->print(cout);
          }

        } else if (arg == "-N" || arg == "-n") {
          cout << "N  " << int(*queue);

        } else if (arg == "-G" || arg == "-g") {
          CHECK_IF_LAST_ARG

          arg = string(argv[++i]);
          if (!convertToInt(arg, number)) {
            cerr << "Error: cannot convert " << arg << " to int" << endl;
            return 1;
          }

          cout << "G  " << (*queue)[number];

        } else {
          cerr << "Wrong parameter: " << arg << endl;
          return 1;
        }

        if (i != argc - 1)
          cout << "  ";
      }
    } catch (logic_error error) {
      cout << "  E" << endl;
    }
  rmxx_end:
    RMXX_END_MAIN(4)
    return 0;
  }
}
