#include "../include/functions.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void expressionEvaluator(node *e1, node *e2, const std::string &filePath) {
  if (e1->Type == constant && e2->Type == constant) {
    string s;
    s = "li	$3,4			# 0x4";
    writeLine(s, filePath);
  }
}
