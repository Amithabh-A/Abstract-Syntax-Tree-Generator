#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <utility> // For std::pair
#include "../include/functions.h"
using namespace std;


vector<std::variant<std::string, std::pair<std::string, int>, int>> collectRHSnodes(node *expr) {
  // Define the variant type
  using VariantType = std::variant<std::string, std::pair<std::string, int>, int>;

  if(expr->Type == constant){
    return vector<VariantType>{getIntValue(expr->value)};
  }

  if(expr->Type == var){
    return vector<VariantType>{string(expr->name)};
  }

  if(expr->Type == Array){
    return vector<VariantType>{make_pair(string(expr->name), getIntValue(expr->value))};
  }


  vector<VariantType> left = collectRHSnodes(expr->lt);
  vector<VariantType> right = collectRHSnodes(expr->rt);

  vector<VariantType> nodes;
  nodes.insert(nodes.end(), left.begin(), left.end());
  nodes.insert(nodes.end(), right.begin(), right.end());

  return nodes;
}
