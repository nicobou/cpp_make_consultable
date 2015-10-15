all: 01_consultable     \
     02_forwarding      \
     03_hooking         \
     04_global_wrapping

01_consultable: 01_consultable.cpp
	g++ -std=c++11 -o 01_consultable-gcc -Wall -Werror -Wfatal-errors 01_consultable.cpp 
	clang++ -std=c++11 -o 01_consultable-clang -Wall -Werror -Wfatal-errors 01_consultable.cpp 

02_forwarding: 02_forwarding.cpp
	g++ -std=c++11 -o 02_forwarding-gcc -Wall -Werror -Wfatal-errors 02_forwarding.cpp 
	clang++ -std=c++11 -o 02_forwarding-clang -Wall -Werror -Wfatal-errors 02_forwarding.cpp 

03_hooking: 03_hooking.cpp
	g++ -std=c++11 -o 03_hooking-gcc -Wall -Werror -Wfatal-errors 03_hooking.cpp 
	clang++ -std=c++11 -o 03_hooking-clang -Wall -Werror -Wfatal-errors 03_hooking.cpp 

04_global_wrapping: 04_global_wrapping.cpp
	g++ -std=c++11 -o 04_global_wrapping-gcc -Wall -Werror -Wfatal-errors 04_global_wrapping.cpp 
	clang++ -std=c++11 -o 04_global_wrapping-clang -Wall -Werror -Wfatal-errors 04_global_wrapping.cpp 

test:
	./01_consultable-gcc
	./01_consultable-clang
	./02_forwarding-gcc
	./02_forwarding-clang
	./03_hooking-gcc
	./03_hooking-clang
	./04_global_wrapping-gcc
	./04_global_wrapping-clang

clean:
	rm ./01_consultable-gcc ./01_consultable-clang           \
           ./02_forwarding-gcc ./02_forwarding-clang             \
           ./03_hooking-gcc ./03_hooking-clang                   \
           ./04_global_wrapping-gcc ./04_global_wrapping-clang
