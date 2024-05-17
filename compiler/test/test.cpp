#include<iostream>
#include<vector>
#include<string>

#include "../include/functions.h"

using namespace std;

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
