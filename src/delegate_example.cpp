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

class Widget {
 public:
  // a non-const method:
  std::string hello(const std::string &str) {
    last_hello_ = str;
    return "hello " + str;
  }
 private:
  std::string last_hello_{};
};

class WidgetOwner {
 public:
  // all public methods are enabled with delegates:
  Make_delegate(Widget, &first_, use_first);
  Make_delegate(Widget, &second_, use_second);
  
  private:
  Widget first_{};
  Widget second_{};
};

class Box {
 public:
  Forward_consultable(WidgetOwner, &wo_, use_first, fwd_first);
  Forward_delegate(WidgetOwner, &wo_, use_second, fwd_second);
 private:
  WidgetOwner wo_;
};

int main() {
  // testing access when owning WidgetOwner
  WidgetOwner wo{};
  // both invokation are allowed since first_ and second are delegated
  cout << wo.use_first(&Widget::hello, "you") << endl;   // hello you
  cout << wo.use_second(&Widget::hello, "you") << endl;  // hello you

  // testing access when owning Box 
  Box b{};
  // compile error first_ is now a consultable:
  // cout << b.fwd_first(&Widget::hello, "you") << endl;  
  //  OK, second_ is a delegate:
  cout << b.fwd_second(&Widget::hello, "you") << endl;   // hello you
}
