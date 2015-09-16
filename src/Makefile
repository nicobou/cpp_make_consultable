all: \
    basic_example \
    overload_example \
    forward_example \
    consultable_setters_example \
    delegate_example \
    vector_example \
    selective_encapsulation



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

vector_example: vector_example.cpp
	g++ -std=c++11 -o vector_example-gcc -Wall -Werror -Wfatal-errors vector_example.cpp 
	clang++ -std=c++11 -o vector_example-clang -Wall -Werror -Wfatal-errors vector_example.cpp 

selective_encapsulation: selective_encapsulation.cpp
	g++ -std=c++11 -o selective_encapsulation-gcc -Wall -Werror -Wfatal-errors selective_encapsulation.cpp 
	clang++ -std=c++11 -o selective_encapsulation-clang -Wall -Werror -Wfatal-errors selective_encapsulation.cpp 

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
	./vector_example-gcc
	./vector_example-clang
	./selective_encapsulation-gcc
	./selective_encapsulation-clang

clean:
	rm basic_example-gcc basic_example-clang \
           overload_example-gcc overload_example-clang \
           forward_example-gcc forward_example-clang \
           consultable_setters_example-gcc consultable_setters_example-clang \
           delegate_example-gcc delegate_example-clang \
           vector_example-gcc vector_example-clang \
           selective_encapsulation-gcc selective_encapsulation-clang		
