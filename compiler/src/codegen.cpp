#include "../include/functions.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

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
  s = "	.ident	\"GCC: (Ubuntu 10.5.0-4ubuntu2) 10.5.0\"";
  writeLine(s);
  s = "	.section	.note.GNU-stack,\"\",@progbits";
  writeLine(s);
}


vector<pair<type, pair<string, int>>> collectDeclarationNodes(node *GdeclSec){
  vector<pair<type, pair<string,int>>> variables;
  // go to Decl_list
  node *Gdecl_list = GdeclSec->next;

  // Gdecl_list === Gdecl
  node *Gdecl = Gdecl_list;
  while(Gdecl != NULL){
    node *Glist = Gdecl->rt;
    node *Gid = Glist;

    while(Gid != NULL){
      variables.push_back({Gid->Type, {Gid->name, getIntValue(Gid->value)}});
      Gid = Gid->next;
    }
    Gdecl = Gdecl->next;
  }
  return variables;
}


void insertVariable(string name, int value, bool isFirstVariable){

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
  writeLine(s);

//	.section	.bss,"aw",@nobits
  if(isFirstVariable){
    s = "	.section	.bss,\"aw\",@nobits";
    writeLine(s);
  }

//	.align	2
  s = "	.align	2";
  writeLine(s);

//	.type	a, @object
  s = "	.type	";
  s = s + name;
  s = s + ", @object";
  writeLine(s);

// 	.size	a, 4
  s = "	.size	" + name + ", ";
  int size = 4;
  if(value != UNDEFINED){
    size = size*value;
    cout << "size: " << size << endl;
  } 
  s = s + to_string(size);
  writeLine(s);

//a:
  s = name + ":";
  writeLine(s);

//	.space	4
  s = "	.space	";
  s = s + to_string(size);
  writeLine(s);
}

void MainInitAssembly(){
  string s;
  s = "	.text";
  writeLine(s);
  s = "	.align	2";
  writeLine(s);
  s = "	.globl	main";
  writeLine(s);
  s = "	.set	nomips16";
  writeLine(s);
  s = "	.set	nomicromips";
  writeLine(s);
  s = "	.ent	main";
  writeLine(s);
  s = "	.type	main, @function";
  writeLine(s);
  s = "main:";
  writeLine(s);
  s = "	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0";
  writeLine(s);
  s = "	.mask	0x40000000,-4";
  writeLine(s);
  s = "	.fmask	0x00000000,0";
  writeLine(s);
  s = "	.set	noreorder";
  writeLine(s);
  s = "	.set	nomacro";
  writeLine(s);
  s = "	addiu	$sp,$sp,-8";
  writeLine(s);
  s = "	sw	$fp,4($sp)";
  writeLine(s);
  s = "	move	$fp,$sp";
  writeLine(s);
}

void MainEndAssembly(){
  string s;
  s = "	move	$2,$0";
  writeLine(s);
  s = "	move	$sp,$fp";
  writeLine(s);
  s = "	lw	$fp,4($sp)";
  writeLine(s);
  s = "	addiu	$sp,$sp,8";
  writeLine(s);
  s = "	jr	$31";
  writeLine(s);
  s = "	nop";
  writeLine(s);
  s = "";
  writeLine(s);
  s = "	.set	macro";
  writeLine(s);
  s = "	.set	reorder";
  writeLine(s);
  s = "	.end	main";
  writeLine(s);
  s = "	.size	main, .-main";
  writeLine(s);
}

void codegen(node *ast) {
  if (ast == NULL) {
    throw std::runtime_error("AST is null");
    return;
  }

  // ast->Type = Prog
  if (ast->Type != Prog) {
    throw std::runtime_error("Invalid AST");
    return;
  }
  ProgInitAssembly();

  // declaration section
  vector<pair<type, pair<string, int>>>declaredVars = collectDeclarationNodes(ast->lt);

  bool isFirstVariable = true;
  for (auto p : declaredVars) {

    if(p.first == declVar){
      insertVariable(p.second.first, UNDEFINED, isFirstVariable);
    } else if (p.first == declArray) {
      insertVariable(p.second.first, p.second.second, isFirstVariable);
    } else {
      throw std::runtime_error("Invalid declaration");
    }
    if(isFirstVariable){
      isFirstVariable = false;
    }
  }

  // main section
  
  node *mymain = ast->rt;


  MainInitAssembly();

  // body
  node *stmt_list = mymain->body;


  node *statement = stmt_list;
  while(statement != NULL){

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

  MainEndAssembly();

  ProgEndAssembly();
}

