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
  Widget(const string &name): name_(name){}
  // make a setter consultable from inside the delegate 
  // set_name needs to be const and name_ needs to be mutable
  std::string set_name(const string &name) const {
    name_ = name;
    return name_;
  }
 private:
  mutable string name_{};
};

class WidgetOwner {
 public:
  Make_consultable(Widget, &first_, consult_first);
  
  private:
  Widget first_{"first"};
};

int main() {
  WidgetOwner wo{};
  // accessing set_name (made const from the Widget)
  cout << wo.consult_first(&Widget::set_name, "other")  // other
       << endl;
  return 0;
}