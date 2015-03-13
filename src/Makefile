all: basic_example overload_example forward_example

basic_example: basic_example.cpp
	g++ -std=c++11 -o basic_example-gcc basic_example.cpp 
	clang++ -std=c++11 -o basic_example-clang basic_example.cpp 

overload_example: overload_example.cpp
	g++ -std=c++11 -o overload_example-gcc overload_example.cpp 
	clang++ -std=c++11 -o overload_example-clang overload_example.cpp 

forward_example: forward_example.cpp
	g++ -std=c++11 -o forward_example-gcc forward_example.cpp 
	clang++ -std=c++11 -o forward_example-clang forward_example.cpp 

test:
	./basic_example-gcc
	./basic_example-clang
	./overload_example-gcc
	./overload_example-clang
	./forward_example-gcc forward_example-clang

clean:
	rm basic_example-gcc basic_example-clang \
           overload_example-gcc overload_example-clang \
           forward_example-gcc forward_example-clang
