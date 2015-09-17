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
  string hello() const {
    return "hello";
  }
  string hello(const string &str) const {
    return "hello " + str;
  }
};

class WidgetOwner {
 public:
  Make_consultable(WidgetOwner, Widget, &first_, consult_first);

 private:
  Widget first_{};
};

int main() {
  WidgetOwner wo{};
  // in case of overloads, signature types give as template parameter
  // allows to distinguishing which overload to select
  cout  << wo.consult_first<Const_Overload(&Widget::hello, Widget, string)>() // hello
        << endl
        << wo.consult_first<Const_Overload(&Widget::hello, Widget, string, const string &)>(
            std::string("you"))                                               // hello you
        << endl;
  
  // static_cast allows for more verbosely selecting the wanted
  cout << wo.consult_first<
    decltype(static_cast<string(Widget::*)() const>(&Widget::hello)),
            &Widget::hello                                                    // hello
            >()
       << endl;
  
  return 0;
}
