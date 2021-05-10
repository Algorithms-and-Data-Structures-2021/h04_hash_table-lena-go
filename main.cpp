#include <iostream>
#include "hash_table.hpp"

using namespace std;
using namespace itis;
int main(int argc, char **argv) {
  std::cout << "Hello, stranger!" << std::endl;

  auto table = HashTable(10, 0.45);

  return 0;
}