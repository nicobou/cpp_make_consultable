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
  // make a setter const, i.e. consultable from inside the delegate 
  // name_ need to be mutable
  std::string get_name() const {
    return name_;
  }
  std::string hello(const std::string &str) {
    last_hello_ = str;
    return "hello " + str;
  }
 private:
  string name_{};
  std::string last_hello_{};
};

class WidgetOwner {
 public:
  Make_consultable(Widget, &first_, consult_first);
  // all non const methods are enabled:
  Make_delegate(Widget, &second_, use_second);
  Make_delegate(Widget, &third_, use_third);
  
  private:
  Widget first_{"first"};
  Widget second_{"second"};
  Widget third_{"third"};
};

class Box {
 public:
  Forward_consultable(WidgetOwner, &wo_, consult_first, fwd_first);
  Forward_delegate(WidgetOwner, &wo_, use_second, fwd_second);
  Forward_consultable(WidgetOwner, &wo_, use_third, fwd_third);
 private:
  WidgetOwner wo_;
};

int main() {
  {  // testing access when owning WidgetOwner
    WidgetOwner wo{};
    /* only invocation of hello from first is locked since made consultable */
    // cout << wo.consult_first(&Widget::hello, "you") << endl;   // compile error
     cout << wo.use_second(&Widget::hello, "you") << endl;        // hello you
     cout << wo.use_third(&Widget::hello, "you") << endl;         // hello you
  }
  
  {  // testing access when owning Box 
    Box b{};
    /* this time, hello invocation from third is made unavailable since
     * forwarded as consultable.
     * invocation of hello from second is still available since
     * forwarded as delegate */
    // cout << b.fwd_first(&Widget::hello, "you") << endl;  // still compile error
    cout << b.fwd_second(&Widget::hello, "you") << endl;   // hello you
    // cout << b.fwd_third(&Widget::hello, "you") << endl; // compile error 
    
    // ensuring const method are still available
    cout << b.fwd_first(&Widget::get_name) << endl;   // first
    cout << b.fwd_second(&Widget::get_name) << endl;  // second 
    cout << b.fwd_third(&Widget::get_name) << endl;   // third 
  }
}
