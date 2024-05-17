#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void createFile(const std::string &fileName) {
  std::ofstream file(fileName);
  if (file.is_open()) {
    std::cout << "File '" << fileName << "' created successfully." << std::endl;
    // Optionally, you can write something into the file here
    file.close();
  } else {
    std::cerr << "Unable to create file '" << fileName << "'." << std::endl;
  }
}

int main() {
  std::string fileName;
  std::cout << "Enter the file name: ";
  std::cin >> fileName;
  createFile(fileName);
  return 0;
}
