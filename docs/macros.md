# What is the basic work of macros in C?
Macros in C are a way to define constants or functions that can be reused throughout the code. They are defined using the `#define` directive and are processed by the preprocessor before the actual compilation of the code begins. Macros can help improve code readability, reduce redundancy, and make it easier to maintain. They can be used for simple constant values, complex expressions, or even function-like constructs. However, it's important to use them judiciously, as they do not have type safety and can lead to unexpected behavior if not used carefully.


#define LINE(N) int a = N;
LINE(5) 
int a = 5;
