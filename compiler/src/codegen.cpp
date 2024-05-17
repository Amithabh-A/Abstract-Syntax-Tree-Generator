#include "../include/functions.h"

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

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

void ProgInitAssembly(const std::string &filePath) {
  string s;
  s = "	.file	1 \"test.c\"";
  writeLine(s, filePath);
  s = "	.section .mdebug.abi32";
  writeLine(s, filePath);
  s = "	.previous";
  writeLine(s, filePath);
  s = "	.nan	legacy";
  writeLine(s, filePath);
  s = "	.module	fp=xx";
  writeLine(s, filePath);
  s = "	.module	nooddspreg";
  writeLine(s, filePath);
  s = "	.abicalls";
  writeLine(s, filePath);
  s = "	.text";
  writeLine(s, filePath);
}

void ProgEndAssembly(const std::string &filePath) {
  string s;
  s = "	.ident	\"GCC: (Ubuntu 10.5.0-4ubuntu2) 10.5.0\"";
  writeLine(s, filePath);
  s = "	.section	.note.GNU-stack,\"\",@progbits";
  writeLine(s, filePath);
}

vector<pair<type, pair<string, int>>> collectDeclarationNodes(node *GdeclSec) {
  vector<pair<type, pair<string, int>>> variables;
  // go to Decl_list
  node *Gdecl_list = GdeclSec->next;

  // Gdecl_list === Gdecl
  node *Gdecl = Gdecl_list;
  while (Gdecl != NULL) {
    node *Glist = Gdecl->rt;
    node *Gid = Glist;

    while (Gid != NULL) {
      variables.push_back({Gid->Type, {Gid->name, getIntValue(Gid->value)}});
      Gid = Gid->next;
    }
    Gdecl = Gdecl->next;
  }
  return variables;
}

void insertVariable(const std::string &filePath, string name, int value,
                    bool isFirstVariable) {

  /*
          .globl	a
          .section	.bss,"aw",@nobits
          .align	2
          .type	a, @object
          .size	a, 4
  a:
          .space	4
   * */

  string s;
  //	.text
  //   s = "	.text";
  //   writeLine(s);

  //	.globl	a
  s = "	.globl	";
  s = s + name;
  writeLine(s, filePath);

  //	.section	.bss,"aw",@nobits
  if (isFirstVariable) {
    s = "	.section	.bss,\"aw\",@nobits";
    writeLine(s, filePath);
  }

  //	.align	2
  s = "	.align	2";
  writeLine(s, filePath);

  //	.type	a, @object
  s = "	.type	";
  s = s + name;
  s = s + ", @object";
  writeLine(s, filePath);

  // 	.size	a, 4
  s = "	.size	" + name + ", ";
  int size = 4;
  if (value != UNDEFINED) {
    size = size * value;
    cout << "size: " << size << endl;
  }
  s = s + to_string(size);
  writeLine(s, filePath);

  // a:
  s = name + ":";
  writeLine(s, filePath);

  //	.space	4
  s = "	.space	";
  s = s + to_string(size);
  writeLine(s, filePath);
}

void MainInitAssembly(const std::string &filePath) {
  string s;
  s = "	.text";
  writeLine(s, filePath);
  s = "	.align	2";
  writeLine(s, filePath);
  s = "	.globl	main";
  writeLine(s, filePath);
  s = "	.set	nomips16";
  writeLine(s, filePath);
  s = "	.set	nomicromips";
  writeLine(s, filePath);
  s = "	.ent	main";
  writeLine(s, filePath);
  s = "	.type	main, @function";
  writeLine(s, filePath);
  s = "main:";
  writeLine(s, filePath);
  s = "	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0";
  writeLine(s, filePath);
  s = "	.mask	0x40000000,-4";
  writeLine(s, filePath);
  s = "	.fmask	0x00000000,0";
  writeLine(s, filePath);
  s = "	.set	noreorder";
  writeLine(s, filePath);
  s = "	.set	nomacro";
  writeLine(s, filePath);
  s = "	addiu	$sp,$sp,-8";
  writeLine(s, filePath);
  s = "	sw	$fp,4($sp)";
  writeLine(s, filePath);
  s = "	move	$fp,$sp";
  writeLine(s, filePath);
}

void MainEndAssembly(const std::string &filePath) {
  string s;
  s = "	move	$2,$0";
  writeLine(s, filePath);
  s = "	move	$sp,$fp";
  writeLine(s, filePath);
  s = "	lw	$fp,4($sp)";
  writeLine(s, filePath);
  s = "	addiu	$sp,$sp,8";
  writeLine(s, filePath);
  s = "	jr	$31";
  writeLine(s, filePath);
  s = "	nop";
  writeLine(s, filePath);
  s = "";
  writeLine(s, filePath);
  s = "	.set	macro";
  writeLine(s, filePath);
  s = "	.set	reorder";
  writeLine(s, filePath);
  s = "	.end	main";
  writeLine(s, filePath);
  s = "	.size	main, .-main";
  writeLine(s, filePath);
}

bool createFile(const std::string &filePath) {
  std::ofstream file(filePath);
  if (!file.is_open()) {
    std::cerr << "Error: Unable to create file " << filePath << std::endl;
    return false;
  }
  file.close();
  std::cout << "File created successfully: " << filePath << std::endl;
  return true;
}

void codegen(node *ast, const std::string &filePath) {
  if (ast == NULL) {
    throw std::runtime_error("AST is null");
    return;
  }

  // ast->Type = Prog
  if (ast->Type != Prog) {
    throw std::runtime_error("Invalid AST");
    return;
  }
  ProgInitAssembly(filePath);

  // declaration section
  vector<pair<type, pair<string, int>>> declaredVars =
      collectDeclarationNodes(ast->lt);

  bool isFirstVariable = true;
  for (auto p : declaredVars) {

    if (p.first == declVar) {
      insertVariable(filePath, p.second.first, UNDEFINED, isFirstVariable);
    } else if (p.first == declArray) {
      insertVariable(filePath, p.second.first, p.second.second,
                     isFirstVariable);
    } else {
      throw std::runtime_error("Invalid declaration");
    }
    if (isFirstVariable) {
      isFirstVariable = false;
    }
  }

  // main section

  node *mymain = ast->rt;

  MainInitAssembly(filePath);

  // body
  node *stmt_list = mymain->body;

  node *statement = stmt_list;
  while (statement != NULL) {

    // switch(statement->Type){
    //   // assign stmt

    //   case assignStmt:

    //   // write stmt
    //   //
    //   // cond stmt
    //   //
    //   // break stmt

    // }

    statement = statement->next;
  }

  // return stmt
  node *ret_stmt = mymain->returnStmt;

  MainEndAssembly(filePath);

  ProgEndAssembly(filePath);
}
