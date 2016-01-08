all: 01_consultable     \
     02_forwarding      \
     03_hooking         \
     04_global_wrapping \
     04_global_wrapping_lock \
     05_type_mosaicing

01_consultable: 01_consultable.cpp
	g++ -std=c++11 -o 01_consultable-gcc -Wall -Werror -Wfatal-errors 01_consultable.cpp 
	clang++ -std=c++11 -stdlib=libc++ -o 01_consultable-clang -Wall -Werror -Wfatal-errors 01_consultable.cpp 

02_forwarding: 02_forwarding.cpp
	g++ -std=c++11 -o 02_forwarding-gcc -Wall -Werror -Wfatal-errors 02_forwarding.cpp 
	clang++ -std=c++11 -stdlib=libc++ -o 02_forwarding-clang -Wall -Werror -Wfatal-errors 02_forwarding.cpp 

03_hooking: 03_hooking.cpp
	g++ -std=c++11 -o 03_hooking-gcc -Wall -Werror -Wfatal-errors 03_hooking.cpp 
	clang++ -std=c++11 -stdlib=libc++ -o 03_hooking-clang -Wall -Werror -Wfatal-errors 03_hooking.cpp 

04_global_wrapping: 04_global_wrapping.cpp
	g++ -std=c++11 -o 04_global_wrapping-gcc -Wall -Werror -Wfatal-errors 04_global_wrapping.cpp 
	clang++ -std=c++11 -stdlib=libc++ -o 04_global_wrapping-clang -Wall -Werror -Wfatal-errors 04_global_wrapping.cpp 

04_global_wrapping_lock: 04_global_wrapping_lock.cpp
	g++ -std=c++11 -o 04_global_wrapping_lock-gcc -Wall -Werror -Wfatal-errors -pthread 04_global_wrapping_lock.cpp 
	clang++ -std=c++11 -stdlib=libc++ -o 04_global_wrapping_lock-clang -Wall -Werror -Wfatal-errors -pthread 04_global_wrapping_lock.cpp 

05_type_mosaicing: 05_type_mosaicing.cpp
	g++ -std=c++11 -o 05_type_mosaicing-gcc -Wall -Werror -Wfatal-errors 05_type_mosaicing.cpp 
	clang++ -std=c++11 -stdlib=libc++ -o 05_type_mosaicing-clang -Wall -Werror -Wfatal-errors 05_type_mosaicing.cpp 

test:
	./01_consultable-gcc
	./01_consultable-clang
	./02_forwarding-gcc
	./02_forwarding-clang
	./03_hooking-gcc
	./03_hooking-clang
	./04_global_wrapping-gcc
	./04_global_wrapping-clang
	./04_global_wrapping_lock-gcc
	./04_global_wrapping_lock-clang
	./05_type_mosaicing-gcc
	./05_type_mosaicing-clang

clean:
	rm ./01_consultable-gcc ./01_consultable-clang                     \
           ./02_forwarding-gcc ./02_forwarding-clang                       \
           ./03_hooking-gcc ./03_hooking-clang                             \
           ./04_global_wrapping-gcc ./04_global_wrapping-clang             \
           ./04_global_wrapping_lock-gcc ./04_global_wrapping_lock-clang   \
           ./05_type_mosaicing-gcc ./05_type_mosaicing-clang
