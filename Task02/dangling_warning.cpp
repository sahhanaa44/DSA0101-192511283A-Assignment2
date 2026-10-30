// Compile only: g++ -std=c++17 -Wall -Wextra -c dangling_warning.cpp
// Never call badReference(): dereferencing the returned reference is undefined behavior.
int& badReference(){int local=42;return local;}
