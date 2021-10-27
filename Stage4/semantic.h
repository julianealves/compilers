/*
Compiladores - Etapa 4 2021/1 - Juliane da Rocha Alves
*/

#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include "hash.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern int SemanticErrors;

int verify_semantic(AST *root);
bool verify_type_elements(AST *node, int data_type);
int calculate_number_of_elements_array(AST *node);
void check_and_set_declarations(AST *node);
void check_undeclared(AST *node);
void check_attribution(AST *node);
void check_expression(AST *node, int data_type);
bool data_type_match(int data_type1, int data_type2);
bool valid_range(AST *node);
int calculate_array_size(AST *node);
void check_vector_access(AST* node);
void check_use_of_functions(AST *node);
AST* get_node_function(char *function_name, AST* node);
int get_num_params_func_call(AST* node);
int get_num_params_func_dec(AST* node);
void verify_return(AST* node, int data_type);
void check_use_of_bool(AST* node);
bool use_bool(AST* node);
void check_comefrom(AST* node);
void check_count_label(AST* node, char *label_name);
void check_label_daclared(AST* node, char *label_name);
void verify_parameters_types(AST* node_func_dec, AST* node_func_call);

#endif
