#include<iostream>
#include "../../include/functions.h"

using namespace std;

void assignConstant(string varName, int value, const std::string &filePath){
// 	lui	$2,%hi(a)
// 	li	$3,10			# 0xa
// 	sw	$3,%lo(a)($2)
  string s;
  s = "	lui	$2,%hi(" + varName + ")";
  writeLine(s, filePath);
  s = "	li	$3," + to_string(value);
  writeLine(s, filePath);
  s = "	sw	$3,%lo(" + varName + ")($2)";
  writeLine(s, filePath);
}


/*
 *
 * The things in the vector are 
 * 1. string -> variable name
 * 2. int -> value
 * 3. pair<string, int> -> Array
 *
 * when we get an element from the vector, we have to get the information 
 * on what that element represents. 
 *
 * for type checking, include : 
 *            #include <typeinfo>
 * to get the type of an element : 
 *            typeid(<element>).name()
 *
 *
 * */





void patternMatchingFunction(string LHSnode, vector<std::variant<std::string, std::pair<std::string, int>, int>>RHSnodes, const std::string &filePath){
  /*
   *
   *  Two cases : 
   *  1. RHSnodes.size() = 1
   *  2. RHSnodes.size() > 1
   * 
   *  if(size == 1){
   *    
   *  }
   *
   *
   *
   * */
  ;
}
