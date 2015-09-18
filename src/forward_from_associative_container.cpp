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
#include <map>
#include <memory>
#include <utility>  // make_pair
#include <cassert>
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
 private:
  Widget first_{"First"};
};

class Box {
 public:
  Box(){
    // get some WidgetOwner into container:
    wos_[1234] = std::unique_ptr<WidgetOwner>(new WidgetOwner());
    wos_[4321] = std::unique_ptr<WidgetOwner>(new WidgetOwner());
  }
  Forward_consultable_from_associative_container(
      Box,
      WidgetOwner,
      find_wos_element,
      int,
      construct_error_return,
      consult_first,
      fwd_first);
  // selective encapsulation of string Widget::get_name(int)
  Selective_hook(fwd_first,
                 Const_Overload_Type(&Widget::get_name, Widget, string, int),
                 &Widget::get_name,
                 &Box::get_name_wrapper);

 private:
  std::map<int, std::unique_ptr<WidgetOwner>> wos_;
  
  // will be used by Forward_consultable_from_associative_container
  std::pair<bool, WidgetOwner *> find_wos_element(int key) const{
    std::cout << __LINE__ << std::endl;
    auto it = wos_.find(key);
    std::cout << __LINE__ << std::endl;
    if (wos_.end() == it){
    std::cout << __LINE__ << std::endl;
      return std::make_pair(false, nullptr);
    }
    std::cout << __LINE__ << std::endl;
    return std::make_pair(true, it->second.get());
  };
  // construct result to pass when element has not been not found,
  // the return type expected is given as template parameter:
  template<typename ReturnType>
  ReturnType construct_error_return(int /*key*/) const{
    std::cout << __LINE__ << std::endl;
    assert(false); // bug
    std::cout << __LINE__ << std::endl;
    return ReturnType();
  }

  string get_name_wrapper(int a) const {return std::to_string(a) + " from Box";}
  // global encapsulation
  struct torPrinter{
    torPrinter(){ cout << "ctor "; }
    ~torPrinter(){ cout << "dtor\n"; }
  };
  torPrinter encapsulated() const {return torPrinter();}
  Global_wrap(fwd_first, torPrinter, encapsulated);
};  // class Box

class BoxOwner{
 public:
  Forward_consultable(BoxOwner, Box, &b_, fwd_first, fwd_last);
  // selective encapsulation of string Widget::get_name(int)
  Selective_hook(fwd_last,
                 Const_Overload_Type(&Widget::get_name, Widget, string, int),
                 &Widget::get_name,
                 &BoxOwner::get_name_wrapper);
 private:
  Box b_{};

  string get_name_wrapper(int a) const {return std::to_string(a) + " from BoxOwner";}

  struct torPrinter{
    torPrinter(){ cout << "cctor "; }
    ~torPrinter(){ cout << "ddtor\n"; }
  };
  torPrinter encapsulated() const {return torPrinter();}
  Global_wrap(fwd_last, torPrinter, encapsulated);
};

int main() {

  {  // testing use of forwarding from container
    Box b{};
    // prints "First"
    cout  << b.fwd_first<Const_Overload(&Widget::get_name, Widget, string)>(1234) 
          << endl;
    // prints "34 from box" 
    cout << b.fwd_first<Const_Overload(&Widget::get_name, Widget, string, int)>(1234, 34)   
         << endl; 
  }

  {  // testing the use of forwaring after forwarding from container
     BoxOwner bo{};
    // prints "First"
    cout  << bo.fwd_last<Const_Overload(&Widget::get_name, Widget, string)>(1234) 
          << endl;
    // prints "34 from box" 
    cout << bo.fwd_last<Const_Overload(&Widget::get_name, Widget, string, int)>(1234, 34)   
         << endl; 
    // 666 is not a valid key, so the following invocation
    // will call "construct_error_return<string>(int)" (which is calling assert):
    // cout << bo.fwd_last<Const_Overload(&Widget::get_name, Widget, string)>(666)   
    //      << endl; 
  }
 
  return 0;
}
