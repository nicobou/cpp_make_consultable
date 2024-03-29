/* The MIT License (MIT)
 *
 * Copyright (c) 2015 Nicolas Bouillot
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

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

class Box3 {
 public:
  Forward_consultable(Box3, NameOwner, &nown_, first, fwd_first);
 private:
  NameOwner nown_{};
  struct torPrinter{
    torPrinter(){ cout << " ctor "; }
    ~torPrinter(){ cout << " dtor "; }
  };
  torPrinter make_TorPrinter() const {return torPrinter();}
  Global_wrap(fwd_first, torPrinter, make_TorPrinter);
};

int main() {
  Box3 b;
  b.fwd_first<&Name::print>();       // ctor Augusta dtor
  cout << b.fwd_first<&Name::get>()  // ctor dtor Augusta
       << endl; 
}
