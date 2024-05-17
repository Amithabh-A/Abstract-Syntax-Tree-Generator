#include "../include/functions.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void assignLhsAssembly(node *e1, node *e2, const std::string &filePath) {

  string s;

  if (e1->Type == constant && e2->Type == constant) {

	  // lui	$2,%hi(b)
    s = "	li	$3," + to_string(getIntValue(e1->value) + getIntValue(e2->value)) +  "			# 0x" + to_string(getIntValue(e1->value) + getIntValue(e2->value));
    writeLine(s, filePath);
	  // sw	$3,%lo(b)($2)

  } 

  else if(e1->Type == var && e2->Type == constant) {

    s = "	lui	$2,%hi(" +  string(e1->name)  + ")";
    writeLine(s, filePath);
    s = "	lw	$2,%lo("+  string(e1->name)  +")($2)";
    writeLine(s, filePath);

    s = "	addiu	$3,$2," + to_string(getIntValue(e2->value));
    writeLine(s, filePath);


    // LHS of equation
	  // lui	$2,%hi(a)
	  // sw	$3,%lo(a)($2)
    
  } 
  
  else if(e1->Type == constant && e2->Type == var) {
     
    s = "	lui	$2,%hi(" +  string(e2->name)  + ")";
    writeLine(s, filePath);
    s = "	lw	$2,%lo("+  string(e2->name)  +")($2)";
    writeLine(s, filePath);

    s = "	addiu	$3,$2," + to_string(getIntValue(e1->value));
    writeLine(s, filePath);


    // LHS of equation
	  // lui	$2,%hi(a)
	  // sw	$3,%lo(a)($2)
    
  }

  else if(e1->Type == constant && e2->Type == Array){
    // Array -> expr :: NUM 
    // Array -> expr -> value :: variant<int, bool>
    int n = getIntValue(e2->expr->value);
    s = "	lui	$2,%hi("+   string(e2->name)    +")";
    writeLine(s, filePath);
    s = "	addiu	$2,$2,%lo(" + string(e2->name) + ")";
    writeLine(s, filePath);
    s = "	lw	$2," + to_string(n*4) + "($2)";
    writeLine(s, filePath);



    s = "	addiu	$3,$2," + to_string(getIntValue(e1->value));
    writeLine(s, filePath);


    // LHS of equation
  	// lui	$2,%hi(b)
  	// sw	$3,%lo(b)($2)

  }


  else if(e1->Type == Array && e2->Type == constant){

    int n = getIntValue(e1->expr->value);

    s = "	lui	$2,%hi(" + string(e1->name) + ")";
    writeLine(s, filePath);
    s = "	addiu	$2,$2,%lo(" + string(e1->name) + ")";
    writeLine(s, filePath);
    s = "	lw	$2," + to_string(n*4) + "($2)";
    writeLine(s, filePath);


    s = "	addiu	$3,$2," + to_string(getIntValue(e2->value));
    writeLine(s, filePath);


    // LHS of equation
	  // lui	$2,%hi(b)
	  // sw	$3,%lo(b)($2)

  }


  else if(e1->Type == var && e2->Type == Array){
    int n = getIntValue(e2->expr->value);
    s = "	lui	$2,%hi("  + string(e2->name) +  ")";
    writeLine(s, filePath);
    s = "	addiu	$2,$2,%lo("  + string(e2->name) +  ")";
    writeLine(s, filePath);
    s = "	lw	$3," + to_string(n*4) + "($2)";
    writeLine(s, filePath);
    s = "	lui	$2,%hi(" + string(e1->name) + ")";
    writeLine(s, filePath);
    s = "	lw	$2,%lo(" + string(e1->name) + ")($2)";
    writeLine(s, filePath);



    s = "	addu	$3,$3,$2";
    writeLine(s, filePath);



    
    // LHS of equation
	  // lui	$2,%hi(b)
	  // sw	$3,%lo(b)($2)
    

  }
}
