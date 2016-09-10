
#include <iostream>
#include <cstdlib>

unsigned int fibo_recursive(unsigned int n) {
    if (n <= 1u) {
        return n;
    }
    else {
        return fibo_recursive(n-1) + fibo_recursive(n-2);
    }
}
     
unsigned int fibo_iterative(unsigned int n) {
    unsigned int buf[2] = { 0u, 1u }; 
    unsigned int current = n;

    while(n && --n) {
        current = buf[0]+buf[1];
        buf[0]  = buf[1];
        buf[1]  = current;
    }
    return current;
}

int main(int argc, const char *argv[]) {

    const unsigned int N = 30u; 


    /* Fibonacci recursive version */
    {
        std::cout << "Testing fibo_recursive:\n\t";
        for (unsigned int i=0u; i<N; i++) {
            std::cout << fibo_recursive(i) << ", ";
        }
        std::cout << std::endl;
    }
   
  
    /* Fibonacci iterative version */
    {
        std::cout << "\nTesting fibo_iterative:\n\t";
        for (unsigned int i=0u; i<N; i++) {
            std::cout << fibo_iterative(i) << ", ";
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}
