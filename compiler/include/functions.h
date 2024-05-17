// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../include/compiler.h"

#include <limits.h>
#include <map>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#define UNDEFINED INT_MAX
#define NOT_INITIALIZED INT_MIN

using namespace std;

// functions.cpp

void printTree(node *stmt_list, type Type);

bool is_statement(type value);

node *createNode(type Type, std::variant<int, bool> value = UNDEFINED,
                 const char *name = NULL, node *leftTree = NULL,
                 node *rightTree = NULL, node *next = NULL, node *expr = NULL,
                 node *ifTrue = NULL, node *ifFalse = NULL, node *init = NULL,
                 node *condition = NULL, node *update = NULL, node *body = NULL,
                 node *returnStmt = NULL);

std::variant<int, bool>
getSymbolValue(const string &name,
               unordered_map<string, std::variant<int, bool>> &symbol_table);

int getIntValue(std::variant<int, bool> value);
bool getBoolValue(std::variant<int, bool> value);

void setSymbolValue(
    const string &name, std::variant<int, bool> value,
    unordered_map<string, std::variant<int, bool>> symbol_table);

void printNode(const node *node, int param = 0);
void NodeImage(node *node);
void printTree(node *stmt_list, type Type);

void insertNext(node *stmt_list, node *stmt);

int *set_array(string name, int size,
               map<string, pair<int *, int>> array_table);
void set_array_element(string name, int index, int value,
                       map<string, pair<int *, int>> array_table);
int *get_array(string name, map<string, pair<int *, int>> array_table);
int get_array_element(string name, int index,
                      map<string, pair<int *, int>> array_table);

// codegen.cpp

void createFile(std::string &fileName);

void writeLine(std::string str = "<EMPTY STRING>",
               const std::string &filePath = "test/codegen.s");
void codegen(node *ast, const std::string &filePath = "test/codegen.s");

vector<pair<type, pair<string, int>>> collectDeclarationNodes(node *GdeclSec);

void ProgInitAssembly(const std::string &filePath);
void insertVariable(const std::string &filePath, string name, int value,
                    bool isFirstVariable);
void ProgEndAssembly(const std::string &filePath);
void MainInitAssembly(const std::string &filePath);
void MainEndAssembly(const std::string &filePath);

#endif // FUNCTIONS_H
