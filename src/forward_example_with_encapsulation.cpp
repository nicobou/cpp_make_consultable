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
  Widget(const string &str): name_(str){}
  string get_name() const {return name_;}
  string get_name(int a) const {return name_ + std::to_string(a);}
 private:
  string name_;
};

class WidgetOwner {
 public:
  Make_consultable(WidgetOwner, Widget, &first_, consult_first);
  Make_consultable(WidgetOwner, Widget, &second_, consult_second);
 private:
  Widget first_{"First"};
  Widget second_{"Second"};
};

class Box {
 public:
  Forward_consultable(Box, WidgetOwner, &wo_, consult_first, fwd_first);
  Forward_consultable(Box, WidgetOwner, &wo_, consult_second, fwd_second);
  Selective_hook(fwd_second,
                 COvT(&Widget::get_name, Widget, string),
                 &Widget::get_name,
                 &Box::get_name_wrapper);
 private:
  WidgetOwner wo_;
  string get_name_wrapper() const {return "box";}
  // global encapsulation
  struct torPrinter{
    torPrinter(){ cout << "ctor "; }
    ~torPrinter(){ cout << "dtor\n"; }
  };
  torPrinter encapsulated() const {return torPrinter();}
  Global_wrap(fwd_first, torPrinter, encapsulated);
};

int main() {
  Box b{};
  cout << b.fwd_first<COPtr(&Widget::get_name, Widget, string)>()        // prints First
       << b.fwd_second<COPtr(&Widget::get_name, Widget, string, int)>(2) // prints Second2
       << endl; 
  return 0;
}
