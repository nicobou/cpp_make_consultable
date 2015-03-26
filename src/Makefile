all: \
    basic_example \
    overload_example \
    forward_example \
    consultable_setters_example \
    delegate_example

basic_example: basic_example.cpp
	g++ -std=c++11 -o basic_example-gcc -Wall -Werror -Wfatal-errors basic_example.cpp 
	clang++ -std=c++11 -o basic_example-clang -Wall -Werror -Wfatal-errors basic_example.cpp 

overload_example: overload_example.cpp
	g++ -std=c++11 -o overload_example-gcc -Wall -Werror -Wfatal-errors overload_example.cpp 
	clang++ -std=c++11 -o overload_example-clang -Wall -Werror -Wfatal-errors overload_example.cpp

forward_example: forward_example.cpp
	g++ -std=c++11 -o forward_example-gcc -Wall -Werror -Wfatal-errors forward_example.cpp 
	clang++ -std=c++11 -o forward_example-clang -Wall -Werror -Wfatal-errors forward_example.cpp 

consultable_setters_example: consultable_setters_example.cpp
	g++ -std=c++11 -o consultable_setters_example-gcc -Wall -Werror -Wfatal-errors consultable_setters_example.cpp 
	clang++ -std=c++11 -o consultable_setters_example-clang -Wall -Werror -Wfatal-errors consultable_setters_example.cpp 

delegate_example: delegate_example.cpp
	g++ -std=c++11 -o delegate_example-gcc -Wall -Werror -Wfatal-errors delegate_example.cpp 
	clang++ -std=c++11 -o delegate_example-clang -Wall -Werror -Wfatal-errors delegate_example.cpp 

test:
	./basic_example-gcc
	./basic_example-clang
	./overload_example-gcc
	./overload_example-clang
	./forward_example-gcc
	./forward_example-clang
	./consultable_setters_example-gcc
	./consultable_setters_example-clang
	./delegate_example-gcc
	./delegate_example-clang

clean:
	rm basic_example-gcc basic_example-clang \
           overload_example-gcc overload_example-clang \
           forward_example-gcc forward_example-clang \
           consultable_setters_example-gcc consultable_setters_example-clang \
           delegate_example-gcc delegate_example-clang
