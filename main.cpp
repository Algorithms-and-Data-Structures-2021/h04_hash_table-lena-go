#include <iostream>
#include "hash_table.hpp"

using namespace std;
using namespace itis;
int main(int argc, char **argv) {
  std::cout << "Hello, stranger!" << std::endl;

  auto table = HashTable(10);
  table.Put(1, "g");
  table.Put(11, "m");
  table.Put(21, "m");
  table.Put(1, "k");

  return 0;
}