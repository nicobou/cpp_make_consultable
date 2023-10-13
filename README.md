Here you will find the implementation of Make_consultable, Make_delegate and related Selective_hook and Global_wrap. Examples, along with several test programs are given in the src folder. The source code is release with the MIT license. It is not compatible with previous release, that was described in the Overload journal (number 127, June 2015).

Implementation and examples described in the overload 127 paper can be accessed in the "overload_127" branch:
git checkout overload_127

In order to use `Make_consultable` and `Make_delegate`, you only need to copy the header file ""

UPDATE (2023-10-12): the need of the `MPtr()` macro has been removed. Here is the new simplified syntax from the `01_consultable.cpp` file:
```
#include <string>
#include <iostream>
#include "./make-consultable.hpp"

using namespace std;

class Name {
 public:
  Name(const string &name): name_(name){}
  string get() const { return name_; }
  void print() const { cout << name_; }
  // ...
 private:
  string name_{};
};

class NameOwner {
 public:
  Make_consultable(NameOwner, Name, &first_, first);
  Make_consultable(NameOwner, Name, &second_, second);
 private:
  Name first_{"Augusta"};
  Name second_{"Ada"};
};

int main() {
  NameOwner nown;
  nown.first<&Name::print>();  // Augusta
  nown.second<&Name::print>(); // Ada
}
```

 