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

class Box2 {
 public:
  Forward_consultable(Box2, NameOwner, &nown_, first, fwd_first);
  Forward_consultable(Box2, NameOwner, &nown_, second, fwd_second);
  Selective_hook(fwd_second,
                 decltype(&Name::get),
                 &Name::get,
                 &Box2::hooking_get);
 private:
  NameOwner nown_{};
  string hooking_get() const {
    return "hooked! (was "
        + nown_.second<&Name::get>()
        + ")";
  }
};

int main() {
  Box2 b;
  cout << b.fwd_first<&Name::get>()  // Augusta
       << b.fwd_second<&Name::get>() // hooked! (was Ada)
       << endl; 
}
