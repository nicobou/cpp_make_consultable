all: basic_example overload_example forward_example add_setters_example

basic_example: basic_example.cpp
	g++ -std=c++11 -o basic_example-gcc -Wall -Werror -Wfatal-errors basic_example.cpp 
	clang++ -std=c++11 -o basic_example-clang -Wall -Werror -Wfatal-errors basic_example.cpp 

overload_example: overload_example.cpp
	g++ -std=c++11 -o overload_example-gcc -Wall -Werror -Wfatal-errors overload_example.cpp 
	clang++ -std=c++11 -o overload_example-clang -Wall -Werror -Wfatal-errors overload_example.cpp

forward_example: forward_example.cpp
	g++ -std=c++11 -o forward_example-gcc -Wall -Werror -Wfatal-errors forward_example.cpp 
	clang++ -std=c++11 -o forward_example-clang -Wall -Werror -Wfatal-errors forward_example.cpp 

add_setters_example: add_setters_example.cpp
	g++ -std=c++11 -o add_setters_example-gcc -Wall -Werror -Wfatal-errors add_setters_example.cpp 
	clang++ -std=c++11 -o add_setters_example-clang -Wall -Werror -Wfatal-errors add_setters_example.cpp 

test:
	./basic_example-gcc
	./basic_example-clang
	./overload_example-gcc
	./overload_example-clang
	./forward_example-gcc
	./forward_example-clang
	./add_setters_example-gcc
	./add_setters_example-clang

clean:
	rm basic_example-gcc basic_example-clang \
           overload_example-gcc overload_example-clang \
           forward_example-gcc forward_example-clang \
           add_setters_example-gcc add_setters_example-clang
