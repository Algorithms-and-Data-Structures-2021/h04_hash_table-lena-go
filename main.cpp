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
  table.Remove(11);
  table.Put(34, "m");
  table.Put(3, "m");
  table.Put(7, "m");
  table.Put(145, "m");

  return 0;
}