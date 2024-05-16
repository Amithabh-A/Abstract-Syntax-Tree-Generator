#include "../include/functions.h"

#include <fstream>
#include <iostream>

// #ifndef UNDEFINED
// #define UNDEFINED INT_MAX
// #endif
//
// #ifndef NOT_INITIALIZED
// #define NOT_INITIALIZED INT_MIN
// #endif

using namespace std;

void writeLine(std::string str, const std::string &filePath) {
  // Open the file in append mode
  std::ofstream outFile(filePath, std::ios::app);
  str += "\n";

  if (outFile.is_open()) {
    // Write the string to the end of the file
    outFile << str;
    // Close the file
    outFile.close();
  } else {
    std::cerr << "Unable to open the file: " << filePath << std::endl;
  }
}

void ProgInitAssembly() {
  string s;
  s = "	.file	1 \"test.c\"";
  writeLine(s);
  s = "	.section .mdebug.abi32";
  writeLine(s);
  s = "	.previous";
  writeLine(s);
  s = "	.nan	legacy";
  writeLine(s);
  s = "	.module	fp=xx";
  writeLine(s);
  s = "	.module	nooddspreg";
  writeLine(s);
  s = "	.abicalls";
  writeLine(s);
  s = "	.text";
  writeLine(s);
}

void ProgEndAssembly() {
  string s;
  s = "	jr	$31";
  writeLine(s);
  s = "	nop";
  writeLine(s);
  s = "";
  writeLine(s);
  s = "	.set	macro";
  writeLine(s);
  s = " .set	reorder";
  writeLine(s);
  s = " .end	main";
  writeLine(s);
  s = " .size	main, .-main";
  writeLine(s);
  s = "	.ident	\"GCC: (Ubuntu 10.5.0-4ubuntu2) 10.5.0\"";
  writeLine(s);
  s = "	.section	.note.GNU-stack,\"\",@progbits";
  writeLine(s);
}

void codegen(node *ast) {
  if (ast == NULL) {
    writeLine("null");
    return;
  }
  // ast->Type = Prog
  if (ast->Type != Prog) {
    throw std::runtime_error("Invalid AST");
    return;
  }
  ProgInitAssembly();
  // declaration section
  // main section
  ProgEndAssembly();
}
