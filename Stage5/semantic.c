/*
Compiladores - Etapa 4 2021/1 - Juliane da Rocha Alves
*/

#include "semantic.h"

int SemanticErrors = 0;
AST *root_;

int verify_semantic(AST *root){
    root_ = root;
    check_and_set_declarations(root);
    check_undeclared(root);
    check_attribution(root);
    check_use_of_functions(root);
    check_use_of_bool(root);
    check_comefrom(root);

    return SemanticErrors;
}

void check_and_set_declarations(AST *node){
//    fprintf(stderr, "Starting semantic check\n");
    int i = 0;

    if (node == 0){
        return;
    }
//    fprintf(stderr, "Node type %d\n", node->type);
    switch (node->type) {
        case AST_VAR:
//            fprintf(stderr, "First case\n");
//            fprintf(stderr, "Node symbol %d\n", node->symbol->data_type);
            if (node->symbol->type != SYMBOL_IDENTIFIER){
                fprintf(stderr, "Semantic ERROR: variable '%s' already declared\n", node->symbol->text);
                SemanticErrors++;
            }
            else{
                node->symbol->type = SYMBOL_VARIABLE;
                if (node->sons[0]->type == AST_KW_CHAR){
                    node->symbol->data_type = DATA_TYPE_CHAR;
                }
                else if (node->sons[0]->type == AST_KW_INT){
                    node->symbol->data_type = DATA_TYPE_INT;
                }
                else if (node->sons[0]->type == AST_KW_FLOAT){
                    node->symbol->data_type = DATA_TYPE_FLOAT;
                }
//                fprintf(stderr, "Changing node type to %d\n", node->symbol->type);
//                fprintf(stderr, "Changing node data type to %d\n", node->symbol->data_type);
                if(!data_type_match(node->symbol->data_type, node->sons[1]->symbol->data_type)){
                    fprintf(stderr, "Semantic ERROR: Data type mismatch in line %d\n", node->line_number);
                    SemanticErrors++;
                }
            }
            break;
        case AST_VECTOR:
            if (node->symbol->type != SYMBOL_IDENTIFIER){
                fprintf(stderr, "Semantic ERROR: vector '%s' already declared\n", node->symbol->text);
                SemanticErrors++;
            }
            else{
                node->symbol->type = SYMBOL_VECTOR;
                if (node->sons[0]->type == AST_KW_CHAR){
                    node->symbol->data_type = DATA_TYPE_CHAR;
                }
                else if (node->sons[0]->type == AST_KW_INT){
                    node->symbol->data_type = DATA_TYPE_INT;
                }
                else if (node->sons[0]->type == AST_KW_FLOAT){
                    node->symbol->data_type = DATA_TYPE_FLOAT;
                }

                // Verify if the list of elements correspond with the size of the vector
                int size_array = calculate_array_size(node->sons[1]);
                if (node->sons[2] != 0) {
                    if (node->sons[2]->type == AST_VECTOR_DECL){
                        int number_elements = calculate_number_of_elements_array(node->sons[2]);
//                            fprintf(stderr, "Number of elements in vector %s is %d\n", node->symbol->text, number_elements);
                        if (number_elements > size_array){
                            fprintf(stderr, "Semantic ERROR: vector '%s' has more elements than the size declarated. "
                                            "Number of elements: %d. Size declared: %d\n", node->symbol->text, number_elements, size_array);
                            SemanticErrors++;
                        }
                        if(!verify_type_elements(node->sons[2], node->symbol->data_type)){
                            fprintf(stderr, "Semantic ERROR: Vector %s Data type mismatch\n", node->symbol->text);
                            SemanticErrors++;
                        }
                    }
                }
            }
            break;
        case AST_FUNC:
            if (node->symbol->type != SYMBOL_IDENTIFIER){
                fprintf(stderr, "Semantic ERROR: function '%s' already declared\n", node->symbol->text);
                SemanticErrors++;
            }
            else{
                node->symbol->type = SYMBOL_FUNCTION;
                if (node->sons[0]->type == AST_KW_CHAR){
                    node->symbol->data_type = DATA_TYPE_CHAR;
                }
                else if (node->sons[0]->type == AST_KW_INT){
                    node->symbol->data_type = DATA_TYPE_INT;
                }
                else if (node->sons[0]->type == AST_KW_FLOAT){
                    node->symbol->data_type = DATA_TYPE_FLOAT;
                }
            }
            break;
        case AST_FUNC_SINGLE_PARAM:
            if (node->symbol->type != SYMBOL_IDENTIFIER){
//                fprintf(stderr, "Node symbol type %d\n", node->symbol->type);
//                fprintf(stderr, "CASE AST_FUNC_SINGLE_PARAM\n");
                fprintf(stderr, "Semantic ERROR: parameter '%s' already declared. Line: %d\n", node->symbol->text, node->line_number);
                SemanticErrors++;
            }
            else{
                node->symbol->type = SYMBOL_PARAMETER;
                if (node->sons[0]->type == AST_KW_CHAR){
                    node->symbol->data_type = DATA_TYPE_CHAR;
                }
                else if (node->sons[0]->type == AST_KW_INT){
                    node->symbol->data_type = DATA_TYPE_INT;
                }
                else if (node->sons[0]->type == AST_KW_FLOAT){
                    node->symbol->data_type = DATA_TYPE_FLOAT;
                }
            }
            break;
        case AST_FUNC_LIST_PARAM:
            if (node->symbol->type != SYMBOL_IDENTIFIER){
//                fprintf(stderr, "Node symbol type %d\n", node->symbol->type);
//                fprintf(stderr, "CASE AST_FUNC_LIST_PARAM\n");
                fprintf(stderr, "Semantic ERROR: parameter '%s' already declared. Line: %d\n", node->symbol->text, node->line_number);
                SemanticErrors++;
            }
            else{
                node->symbol->type = SYMBOL_PARAMETER;
                if (node->sons[0]->type == AST_KW_CHAR){
                    node->symbol->data_type = DATA_TYPE_CHAR;
                }
                else if (node->sons[0]->type == AST_KW_INT){
                    node->symbol->data_type = DATA_TYPE_INT;
                }
                else if (node->sons[0]->type == AST_KW_FLOAT){
                    node->symbol->data_type = DATA_TYPE_FLOAT;
                }
            }
            break;
    }
    for (i=0; i<MAX_SONS; i++){
        check_and_set_declarations(node->sons[i]);
    }

}

bool verify_type_elements(AST *node, int data_type){
    if (node != 0){
        if(!data_type_match(data_type, node->sons[0]->symbol->data_type)){
            return false;
        }
    }
    if(node->sons[1] != 0){
        return verify_type_elements(node->sons[1], data_type);
    }
    return true;
}

int calculate_number_of_elements_array(AST *node){
    if (node == 0){
        return 0;
    }
//    return calculate_number_of_elements_array(node->sons[0])+1;
    return calculate_number_of_elements_array(node->sons[1])+1;
}

int calculate_array_size(AST *node){
    int index1 = atoi(node->symbol->text);
    int index2 = atoi(node->sons[0]->symbol->text);

    return abs(index2 - index1) + 1;
}

bool valid_range(AST *node){
    if (node->symbol->data_type == DATA_TYPE_INT && node->sons[0]->symbol->data_type == DATA_TYPE_INT){
        return true;
    }
    return false;
}

bool data_type_match(int data_type1, int data_type2){
//    fprintf(stderr, "Data type1: %d\n", data_type1);
//    fprintf(stderr, "Data type2: %d\n", data_type2);
    if (data_type1 == data_type2 && data_type1 != 0 && data_type2 != 0){
        return true;
    }
    else if (data_type1 == DATA_TYPE_INT && (data_type2 == DATA_TYPE_FLOAT || data_type2 == DATA_TYPE_CHAR)){
        return true;
    }
    else if (data_type1 == DATA_TYPE_CHAR && (data_type2 == DATA_TYPE_INT || data_type2 == DATA_TYPE_FLOAT)){
        return true;
    }
    else if (data_type1 == DATA_TYPE_FLOAT && (data_type2 == DATA_TYPE_INT || data_type2 == DATA_TYPE_CHAR)){
        return true;
    }
    return false;
}

void check_undeclared(AST *node){
    int i = 0;

    if (node == 0){
        return;
    }

    switch (node->type) {
        case AST_ATTRIBUTION:
            if (node->symbol->type == SYMBOL_IDENTIFIER){
                fprintf(stderr, "Semantic ERROR: variable '%s' not declared. Line: %d\n", node->symbol->text, node->line_number);
                SemanticErrors++;
            }
            break;
        case AST_VECT_ATTRIBUTION:
            if (node->symbol->type == SYMBOL_IDENTIFIER){
                fprintf(stderr, "Semantic ERROR: vector '%s' not declared. Line: %d\n", node->symbol->text, node->line_number);
                SemanticErrors++;
            }
            break;
        case AST_CALL_FUNC:
            if (node->symbol->type == SYMBOL_IDENTIFIER){
                fprintf(stderr, "Semantic ERROR: function '%s' not declared. Line: %d\n", node->symbol->text, node->line_number);
                SemanticErrors++;
            }
            break;
    }

    for (i=0; i<MAX_SONS; i++){
        check_undeclared(node->sons[i]);
    }
}

void check_attribution(AST *node){
    int i = 0;

    if (node == 0){
        return;
    }

    switch (node->type) {
        case AST_ATTRIBUTION:
            if (node->symbol->type != SYMBOL_IDENTIFIER && node->sons[0]->symbol != NULL){
                if(node->symbol->type != SYMBOL_VARIABLE && node->symbol->type != SYMBOL_PARAMETER){
                    fprintf(stderr, "Semantic ERROR: Function or vector being used as scalar. Line: %d\n", node->line_number);
                    SemanticErrors++;
                }
            }
            check_expression(node->sons[0], node->symbol->data_type);
            break;
        case AST_VECT_ATTRIBUTION:
            if (node->symbol->type != SYMBOL_IDENTIFIER && node->sons[0]->symbol != NULL){
                if(node->symbol->type != SYMBOL_VECTOR){
                    fprintf(stderr, "Semantic ERROR: Function or variable being used as vector. Line: %d\n", node->line_number);
                    SemanticErrors++;
                }
            }
            check_expression(node->sons[1], node->symbol->data_type);
            check_vector_access(node->sons[0]);
            break;
    }

    for (i=0; i<MAX_SONS; i++){
        check_attribution(node->sons[i]);
    }
}

void check_expression(AST *node, int data_type){
    int i = 0;

    if (node == 0){
        return;
    }

    switch (node->type) {
        case AST_SYMBOL:
            if (!data_type_match(data_type, node->symbol->data_type)){
                if (data_type == 0 || node->symbol->data_type == 0){
                    fprintf(stderr, "Semantic ERROR: Unkown data type. Variable, vector or function not declared. Line: %d\n", node->line_number);
                }
                else{
                    fprintf(stderr, "Semantic ERROR: Data type mismatch. Line: %d\n", node->line_number);
                }
                SemanticErrors++;
            }
            break;
        case AST_ADD:
            check_expression(node->sons[0], data_type);
            check_expression(node->sons[1], data_type);
            break;
        case AST_SUB:
            check_expression(node->sons[0], data_type);
            check_expression(node->sons[1], data_type);
            break;
        case AST_MULT:
            check_expression(node->sons[0], data_type);
            check_expression(node->sons[1], data_type);
            break;
        case AST_DIV:
            check_expression(node->sons[0], data_type);
            check_expression(node->sons[1], data_type);
            break;
        case AST_CURLY_BRACKET:
            check_expression(node->sons[0], data_type);
            break;
        case AST_BRACKETS:
            check_expression(node->sons[0], data_type);
            break;
        case AST_PAREN:
            check_expression(node->sons[0], data_type);
            break;
        case AST_LE:
            fprintf(stderr, "Semantic ERROR: Invalid bool operation. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_GE:
            fprintf(stderr, "Semantic ERROR: Invalid bool operation. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_EQ:
            fprintf(stderr, "Semantic ERROR: Invalid bool operation. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_DIF:
            fprintf(stderr, "Semantic ERROR: Invalid bool operation. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_LESS:
            fprintf(stderr, "Semantic ERROR: Invalid bool operation. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_BIGGER:
            fprintf(stderr, "Semantic ERROR: Invalid bool operation. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_OR:
            fprintf(stderr, "Semantic ERROR: Invalid bool operation. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_NOT:
            fprintf(stderr, "Semantic ERROR: Invalid bool operation. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_AND:
            fprintf(stderr, "Semantic ERROR: Invalid bool operation. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_VECTOR_ACCESS:
            check_vector_access(node);
            break;
    }
}

void check_vector_access(AST* node){
    int i = 0;

    if (node == 0){
        return;
    }

    switch (node->type) {
        case AST_SYMBOL:
            if (node->symbol->data_type != DATA_TYPE_INT){
                fprintf(stderr, "Semantic ERROR: Invalid vector access. Line: %d\n", node->line_number);
                SemanticErrors++;
            }
            break;
        case AST_ADD:
            check_vector_access(node->sons[0]);
            check_vector_access(node->sons[1]);
            break;
        case AST_SUB:
            check_vector_access(node->sons[0]);
            check_vector_access(node->sons[1]);
            break;
        case AST_MULT:
            check_vector_access(node->sons[0]);
            check_vector_access(node->sons[1]);
            break;
        case AST_DIV:
            check_vector_access(node->sons[0]);
            check_vector_access(node->sons[1]);
            break;
        case AST_LE:
            fprintf(stderr, "Semantic ERROR: Invalid vector access. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_GE:
            fprintf(stderr, "Semantic ERROR: Invalid vector access. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_EQ:
            fprintf(stderr, "Semantic ERROR: Invalid vector access. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_DIF:
            fprintf(stderr, "Semantic ERROR: Invalid vector access. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_LESS:
            fprintf(stderr, "Semantic ERROR: Invalid vector access. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_BIGGER:
            fprintf(stderr, "Semantic ERROR: Invalid vector access. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_OR:
            fprintf(stderr, "Semantic ERROR: Invalid vector access. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_NOT:
            fprintf(stderr, "Semantic ERROR: Invalid vector access. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_AND:
            fprintf(stderr, "Semantic ERROR: Invalid vector access. Line: %d\n", node->line_number);
            SemanticErrors++;
            break;
        case AST_PAREN:
            check_vector_access(node->sons[0]);
            break;
        case AST_BRACKETS:
            check_vector_access(node->sons[0]);
            break;
        case AST_CURLY_BRACKET:
            check_vector_access(node->sons[0]);
            break;
    }
}

void check_use_of_functions(AST *node){
    int i = 0;
    int num_params_declared = 0;
    int num_params_call_func = 0;
    AST* node_func;

    if (node == 0){
        return;
    }

    switch (node->type) {
        case AST_CALL_FUNC:
            node_func = get_node_function(node->symbol->text, root_);
            if (node_func != NULL){
                if (node_func->sons[1] != 0) {
//                    fprintf(stderr, "PARAM IN FUNC %d\n", node_func->sons[1]->type);
                    num_params_declared = get_num_params_func_dec(node_func->sons[1]) - 1;
                }
                if (node->sons[0] != 0) {
//                    fprintf(stderr, "PARAM IN CALL %d\n", node->sons[0]->type);
                    num_params_call_func = get_num_params_func_call(node->sons[0]);
                }
                if (num_params_declared != num_params_call_func){
                    if (num_params_declared < num_params_call_func){
                        fprintf(stderr, "Semantic ERROR: More parameters than the expected for function %s. Passed %d. "
                                        "Expected %d. Line: %d\n", node->symbol->text, num_params_call_func, num_params_declared, node->line_number);
                    }
                    else if (num_params_declared > num_params_call_func){
                        fprintf(stderr, "Semantic ERROR: Less parameters than the expected for function %s. Passed %d. "
                                        "Expected %d. Line: %d\n", node->symbol->text, num_params_call_func, num_params_declared, node->line_number);
                    }
                    SemanticErrors++;
                }
                if (node_func->sons[1] != 0 && node->sons[0] != 0)
                    verify_parameters_types(node_func->sons[1], node->sons[0]);
            }
            break;
        case AST_FUNC:
            verify_return(node->sons[2], node->symbol->data_type);
            break;
    }

    for (i=0; i<MAX_SONS; i++){
        check_use_of_functions(node->sons[i]);
    }
}

void verify_parameters_types(AST* node_func_dec, AST* node_func_call){
    if (node_func_dec == 0 || node_func_call == 0){
        fprintf(stderr, "NODE IS ZERO: %d\n", node_func_dec->type);
        return;
    }

//    fprintf(stderr, "DEC NODE TYPE: %d\n", node_func_dec->type);
//    fprintf(stderr, "CALL NODE TYPE: %d\n", node_func_call->type);
//    fprintf(stderr, "DEC PARAM TYPE SON[0]: %d\n", node_func_dec->sons[0]->type);
//    fprintf(stderr, "DEC PARAM TYPE SON[1]: %d\n", node_func_dec->sons[1]->type);
//    fprintf(stderr, "CALL PARAM TYPE SON[0]: %d\n", node_func_call->sons[0]->type);
//    fprintf(stderr, "CALL PARAM TYPE SON[1]: %d\n", node_func_call->sons[1]->type);


    if (node_func_dec->sons[0] != 0 && node_func_call->sons[0] != 0) {
        if (!data_type_match(node_func_dec->sons[0]->symbol->data_type,
                             node_func_call->sons[0]->symbol->data_type)) {
            fprintf(stderr, "Semantic ERROR: Data type mismatch in function call. Line: %d\n",
                    node_func_call->line_number);
            SemanticErrors++;
        }
    }

    if(node_func_dec->sons[1] != 0){
        verify_parameters_types(node_func_dec->sons[1], node_func_call->sons[1]);
    }
}

AST* get_node_function(char *function_name, AST* node){
    int i;
    AST* aux;

    if (node == 0){
        return NULL;
    }

    if(node->symbol != 0 && node->type == AST_FUNC && strcmp(node->symbol->text, function_name) == 0){
        return node;
    }

    for(i = 0;  i < MAX_SONS; i++){
        aux = get_node_function(function_name, node->sons[i]);
        if(aux != NULL){
            return aux;
        }
    }
    return NULL;
}

int get_num_params_func_call(AST* node){
//    fprintf(stderr, "get_num_params\n");
    if (node == 0){
//        fprintf(stderr, "NODE IS 0\n");
        return 0;
    }
    return get_num_params_func_call(node->sons[1])+1;
}

int get_num_params_func_dec(AST* node){
    if (node == 0){
        return 0;
    }
    if (node->sons[1] != 0){
        return get_num_params_func_dec(node->sons[1])+1;
    }
    else if (node->sons[0] != 0){
        return get_num_params_func_dec(node->sons[0])+1;
    }
    else{
        return 0;
    }
}

void verify_return(AST* node, int data_type){
    int i = 0;

    if (node == 0){
        return;
    }

    switch (node->type) {
        case AST_KW_RETURN:
            check_expression(node->sons[0], data_type);
            break;
    }

    for (i=0; i<MAX_SONS; i++){
        verify_return(node->sons[i], data_type);
    }
}

void check_use_of_bool(AST* node){
    int i = 0;

    if (node == 0){
        return;
    }

    switch (node->type) {
        case AST_KW_UNTIL:
            if (!use_bool(node->sons[0])){
                fprintf(stderr, "Semantic ERROR: 'until' needs a bool expression. Line: %d\n", node->line_number);
                SemanticErrors++;
            }
            break;
        case AST_KW_IF:
            if (!use_bool(node->sons[0])){
                fprintf(stderr, "Semantic ERROR: 'if' needs a bool expression. Line: %d\n", node->line_number);
                SemanticErrors++;
            }
            break;
    }

    for (i=0; i<MAX_SONS; i++){
        check_use_of_bool(node->sons[i]);
    }
}

bool use_bool(AST* node){
    if (node != 0){
        if(node->type == AST_LE || node->type == AST_GE || node->type == AST_EQ || node->type == AST_DIF ||
        node->type == AST_LESS || node->type == AST_BIGGER || node->type == AST_OR || node->type == AST_NOT ||
        node->type == AST_AND){
            return true;
        }
    }
    if(node->sons[0] != 0){
        return use_bool(node->sons[0]);
    }
    else if(node->sons[1] != 0){
        return use_bool(node->sons[1]);
    }
    return false;

}

void check_comefrom(AST* node){
    int i = 0;

    if (node == 0){
        return;
    }

    switch (node->type) {
        case AST_KW_COMEFROM:
//            fprintf(stderr, "COMEFROM %s\n", node->symbol->text);
            check_count_label(root_, node->symbol->text);
//            check_label_daclared(root_, node->symbol->text);
//            if (node->label_declarated == 0){
//                fprintf(stderr, "Semantic ERROR: Label '%s' was not declared. Line: %d\n", node->symbol->text, node->line_number);
//                //fprintf(stderr, "LINE %d.\n", node->line_number);
//                SemanticErrors++;
//            }
            break;

    }

    for (i=0; i<MAX_SONS; i++){
        check_comefrom(node->sons[i]);
    }
}

void check_count_label(AST* node, char *label_name){
    int i;

    if (node == 0){
        return;
    }

    if(node->symbol != 0 && node->type == AST_KW_COMEFROM && strcmp(node->symbol->text, label_name) == 0 && node->label == 0){
        //fprintf(stderr, "FOUND LABEL IN LINE %d.\n", node->line_number);
        node->label = 1;
    }
    else if (node->symbol != 0 && node->type == AST_KW_COMEFROM && strcmp(node->symbol->text, label_name) == 0 && node->label == 1){
        fprintf(stderr, "Semantic ERROR: Label '%s' is been used more than once. Line: %d\n", label_name, node->line_number);
        //fprintf(stderr, "LINE %d.\n", node->line_number);
        SemanticErrors++;
    }

    for(i = 0;  i < MAX_SONS; i++){
        check_count_label(node->sons[i], label_name);
    }
}

void check_label_daclared(AST* node, char *label_name){
    int i;

    if (node == 0){
        return;
    }

    if (node->symbol != 0 && node->type == AST_SYMBOL && strcmp(node->symbol->text, label_name) == 0){
//        fprintf(stderr, "SYMBOL TYPE %d\n", node->symbol->type);
        node->label_declarated = 1;
    }

    if (node->symbol != 0 && strcmp(node->symbol->text, label_name) == 0 &&
    (node->symbol->type == SYMBOL_VECTOR || node->symbol->type == SYMBOL_FUNCTION || node->symbol->type == SYMBOL_VARIABLE)){
        fprintf(stderr, "SYMBOL TYPE %d\n", node->symbol->type);
        fprintf(stderr, "Semantic ERROR: Can not use variable, vector or function as label. Label: %s. Line: %d.\n", node->symbol->text, node->line_number);
        SemanticErrors++;
    }

    for(i = 0;  i < MAX_SONS; i++){
        check_label_daclared(node->sons[i], label_name);
    }

}