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

#include <vector>
#include <iostream>
#include "../make-consultable.hpp"

using namespace std;

using vect_t = std::vector<int>;
using cref_t = vect_t::const_reference;
using vsize_t = vect_t::size_type;

class VectorOwner {
 public:
  Make_consultable(VectorOwner, vect_t, &first_, consult_first);
  Make_consultable(VectorOwner, vect_t, &second_, consult_second);

 private:
  vect_t first_{{10, 20, 30}};
  vect_t second_{{40, 50}};
};

int main() {
  VectorOwner wo;                                                         // print:
  cout << wo.consult_first<MPtr(&vect_t::size)>()                       // 3
       << wo.consult_second<MPtr(&vect_t::size)>()                      // 2
       << *wo.consult_second<MPtr(&vect_t::cbegin)>()                   // 40
       << wo.consult_second<
         COPtr(&vect_t::operator[], vect_t, cref_t, vsize_t)>(1) // 50
       << endl;

  for (auto it = wo.consult_first<MPtr(&vect_t::cbegin)>();
       it !=  wo.consult_first<MPtr(&vect_t::cend)>();
       ++it) {                                                            //102030
    std::cout << *it;                                
  }
  std::cout << std::endl;

}
