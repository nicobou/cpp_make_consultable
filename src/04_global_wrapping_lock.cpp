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
#include <thread>
#include <mutex>
#include "./make-consultable.hpp"

using namespace std;

class Count {
 public:
  int get() const { return count_; }
  void incr() { ++count_; }
 private:
  int count_{0};
};

class CountOwner {
 public:
  Make_delegate(CountOwner, Count, &counter_, count);
 private:
  Count counter_{};
  mutable std::mutex count_mtx_{};
  std::unique_lock<std::mutex> lock_counter() const {
    return std::unique_lock<std::mutex>(count_mtx_);
  }
  Global_wrap(count, std::unique_lock<std::mutex>, lock_counter);
};


void use_counter(CountOwner &countOwner
                 ){
  int i = 100000;
  while (--i >= 0){
    countOwner.count<&Count::incr>();
  }
}

int main() {
  CountOwner countOwner;
  std::thread th1(use_counter, std::ref(countOwner));
  std::thread th2(use_counter, std::ref(countOwner));
  th1.join();
  th2.join();
  std::cout << std::to_string(countOwner.count<&Count::get>())
            << std::endl;
}
