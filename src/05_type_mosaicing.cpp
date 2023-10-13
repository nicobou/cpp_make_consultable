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

template<typename T> class Prop {
 public:
  Prop() = default;
  Prop(const T &val) : val_(val){}
  T get() const { return val_; }
  void set(const T &val) { val_ = val; }
  // ...
 private:
  T val_{};
};

class Element {
 public:
  Element(string info, int num) : info_(info), num_(num){}
  Make_consultable(Element, Prop<string>, &info_, info);
  Make_consultable(Element, Prop<int>, &num_, num);
  Make_delegate(Element, Prop<string>, &last_msg_, last_msg);
 protected:
  Make_delegate(Element, Prop<string>, &info_, prot_info);
 private:
  Prop<string> info_{};
  Prop<int> num_{0};
  Prop<string> last_msg_{};
};

struct Countess : public Element {
  Countess() : Element("programmer", 1){}
  void mutate(){
    prot_info<&Prop<string>::set>("mathematician");
  }
};

int main() {
  Countess a;
  a.last_msg<&Prop<string>::set>("Analytical Engine");
  cout << a.num<&Prop<int>::get>();      // "1"
  // a.info<&Prop<string>::set>("...");  // does not compile
  cout << a.info<&Prop<string>::get>();  // "programmer"
  a.mutate();
  cout << a.info<&Prop<string>::get>();  // "mathematician"
}
