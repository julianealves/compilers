/*
Compiladores - Etapa 5 2021/1 - Juliane da Rocha Alves
*/
#include <stdlib.h>
#include "tacs.h"

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2){
    TAC* newtac = 0;
    newtac = (TAC*) calloc(1, sizeof(TAC));
    newtac->type = type;
    newtac->res = res;
    newtac->op1 = op1;
    newtac->op2 = op2;
    newtac->prev = 0;
    newtac->next=0;

    return newtac;
}

void tacPrint(TAC* tac){
    if (!tac){
        return;
    }

    if (tac->type == TAC_SYMBOL){
        return;
    }

//    fprintf(stderr, "TAC TYPE %d\n", tac->type);
    fprintf(stderr, "TAC(");

    switch(tac->type){
        case TAC_SYMBOL:
            fprintf(stderr, "TAC_SYMBOL");
            break;
        case TAC_ADD:
            fprintf(stderr, "TAC_ADD");
            break;
        case TAC_SUB:
            fprintf(stderr, "TAC_SUB");
            break;
        case TAC_MUL:
            fprintf(stderr, "TAC_MUL");
            break;
        case TAC_DIV:
            fprintf(stderr, "TAC_DIV");
            break;
        case TAC_MOVE:
            fprintf(stderr, "TAC_MOVE");
            break;
        case TAC_LABEL:
            fprintf(stderr, "TAC_LABEL");
            break;
        case TAC_BEGINFUN:
            fprintf(stderr, "TAC_BEGINFUN");
            break;
        case TAC_ENDFUN:
            fprintf(stderr, "TAC_ENDFUN");
            break;
        case TAC_IFZ:
            fprintf(stderr, "TAC_IFZ");
            break;
        case TAC_JUMP:
            fprintf(stderr, "TAC_JUMP");
            break;
        case TAC_CALL:
            fprintf(stderr, "TAC_CALL");
            break;
        case TAC_ARG:
            fprintf(stderr, "TAC_ARG");
            break;
        case TAC_RET:
            fprintf(stderr, "TAC_RET");
            break;
        case TAC_PRINT:
            fprintf(stderr, "TAC_PRINT");
            break;
        case TAC_READ:
            fprintf(stderr, "TAC_READ");
            break;
        case TAC_COPY:
            fprintf(stderr, "TAC_COPY");
            break;
        case TAC_LE:
            fprintf(stderr, "TAC_LE");
            break;
        case TAC_LESS:
            fprintf(stderr, "TAC_LESS");
            break;
        case TAC_GE:
            fprintf(stderr, "TAC_GE");
            break;
        case TAC_EQ:
            fprintf(stderr, "TAC_EQ");
            break;
        case TAC_DIF:
            fprintf(stderr, "TAC_DIF");
            break;
        case TAC_BIGGER:
            fprintf(stderr, "TAC_BIGGER");
            break;
        case TAC_OR:
            fprintf(stderr, "TAC_OR");
            break;
        case TAC_NOT:
            fprintf(stderr, "TAC_NOT");
            break;
        case TAC_AND:
            fprintf(stderr, "TAC_AND");
            break;
        case TAC_COMEFROM:
            fprintf(stderr, "TAC_COMEFROM");
            break;
        case TAC_COPY_VEC:
            fprintf(stderr, "TAC_COPY_VEC");
            break;
        case TAC_LIST_EXPR:
            fprintf(stderr, "TAC_LIST_EXPR");
            break;
        case TAC_LIST_STR_PRINT:
            fprintf(stderr, "TAC_LIST_STR_PRINT");
            break;
        case TAC_LIST_PRINT:
            fprintf(stderr, "TAC_LIST_PRINT");
            break;
        case TAC_VECTOR_ACCESS:
            fprintf(stderr, "TAC_VECTOR_ACCESS");
            break;
        case TAC_FUNC:
            fprintf(stderr, "TAC_FUNC");
            break;
        case TAC_LIST_CMD:
            fprintf(stderr, "TAC_LIST_CMD");
            break;
        case TAC_VECTOR_DECL:
            fprintf(stderr, "TAC_VECTOR_DECL");
            break;
        default:
            fprintf(stderr, "TAC_UNKNOWN");
            break;
    }

    fprintf(stderr, ",%s", (tac->res)?tac->res->text:"0");
    fprintf(stderr, ",%s", (tac->op1)?tac->op1->text:"0");
    fprintf(stderr, ",%s", (tac->op2)?tac->op2->text:"0");
    fprintf(stderr, ");\n");
}

void tacPrintBackwards(TAC* tac){
    if (!tac){
        return;
    }

    tacPrintBackwards(tac->prev);
    tacPrint(tac);
}

TAC* tacJoin(TAC* l1, TAC* l2){
    TAC *point;

    if (!l1){
        return l2;
    }

    if (!l2){
        return l1;
    }

    for(point=l2; point->prev!=0; point=point->prev);

    point->prev = l1;
    return l2;
}

TAC* generateCode(AST* node){
    int i;
    TAC *result = 0;
    TAC *code[MAX_SONS];

    if(!node){
        return 0;
    }

    for (i=0; i<MAX_SONS; i++){
        code[i] = generateCode(node->sons[i]);
    }

    switch (node->type) {
        case AST_SYMBOL:
            result = tacCreate(TAC_SYMBOL, node->symbol,0,0);
            break;
        case AST_ADD:
            result = binOperation(TAC_ADD, code[0], code[1]);
            break;
        case AST_SUB:
            result = binOperation(TAC_SUB, code[0], code[1]);
            break;
        case AST_MULT:
            result = binOperation(TAC_MUL, code[0], code[1]);
            break;
        case AST_DIV:
            result = binOperation(TAC_DIV, code[0], code[1]);
            break;
        case AST_AND:
            result = binOperation(TAC_AND, code[0], code[1]);
            break;
        case AST_NOT:
            result = binOperation(TAC_NOT, code[0], code[1]);
            break;
        case AST_LE:
            result = binOperation(TAC_LE, code[0], code[1]);
            break;
        case AST_GE:
            result = binOperation(TAC_GE, code[0], code[1]);
            break;
        case AST_EQ:
            result = binOperation(TAC_EQ, code[0], code[1]);
            break;
        case AST_DIF:
            result = binOperation(TAC_DIF, code[0], code[1]);
            break;
        case AST_LESS:
            result = binOperation(TAC_LESS, code[0], code[1]);
            break;
        case AST_BIGGER:
            result = binOperation(TAC_BIGGER, code[0], code[1]);
            break;
        case AST_OR:
            result = binOperation(TAC_OR, code[0], code[1]);
            break;
        case AST_ATTRIBUTION:
            result = tacJoin(code[0], tacCreate(TAC_COPY, node->symbol,code[0]?code[0]->res:0,0));
            break;
        case AST_VECT_ATTRIBUTION:
//            result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_COPY_VEC, node->symbol, code[0]?code[0]->res:0, code[1]?code[1]->res:0)));
            result = tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_COPY_VEC, node->symbol, code[0]?code[0]->res:0, code[1]?code[1]->res:0));
            break;
        case AST_KW_IF:
//            fprintf(stderr, "ENTRE NO IF");
            result = makeIfThen(code[0], code[1], code[2]);
            break;
        case AST_KW_READ:
            result = tacCreate(TAC_READ, makeTemp(),0,0);
            break;
        case AST_KW_COMEFROM:
            result = tacCreate(TAC_COMEFROM, node->symbol,0,0);
            break;
        case AST_KW_RETURN:
//            fprintf(stderr, "ENTREI NO RETURN\n");
            result = tacJoin(code[0], tacCreate(TAC_RET, code[0]?code[0]->res:0,0,0));
            break;
        case AST_LIST_STR_PRINT:
            result = tacJoin(code[0], tacCreate(TAC_LIST_STR_PRINT, node->symbol,code[0]?code[0]->res:0,0));
            break;
        case AST_LIST_PRINT:
//            result = tacJoin(code[0], tacJoin(code[1], tacCreate(TAC_PRINT, code[0]?code[0]->res:0, code[1]?code[1]->res:0,0)));
            result = tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_LIST_PRINT, code[0]?code[0]->res:0, code[1]?code[1]->res:0,0));
            break;
        case AST_KW_PRINT:
            result = tacJoin(code[0], tacCreate(TAC_PRINT, code[0]?code[0]->res:0, 0,0));
            break;
        case AST_CALL_FUNC:
            result = tacJoin(code[0], tacCreate(TAC_CALL, node->symbol, code[0]?code[0]->res:0, 0));
            break;
        case AST_LIST_EXPR:
            result = tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_LIST_EXPR, code[0]?code[0]->res:0, code[1]?code[1]->res:0, 0));
            break;
        case AST_VECTOR_ACCESS:
            result = tacJoin(code[0], tacCreate(TAC_VECTOR_ACCESS, node->symbol,code[0]?code[0]->res:0,0));
            break;
        case AST_FUNC:
//            result = tacJoin(tacJoin(code[2], code[3]), tacCreate(TAC_FUNC, node->symbol, code[2]?code[2]->res:0, code[3]?code[3]->res:0));
//            result = tacJoin(tacJoin(code[2], code[3]), tacCreate(TAC_FUNC, node->symbol, code[3]?code[3]->res:0, 0));
//            fprintf(stderr, "ENTREI NO AST_FUNC\n");
            result = tacJoin(makeFunction(tacCreate(AST_SYMBOL, node->symbol, 0, 0), code[1], code[2]), code[3]);
            break;
//        case AST_LIST_CMD:
//            result = tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_LIST_CMD, code[0]?code[0]->res:0, code[1]?code[1]->res:0, 0));
//            break;
        case AST_VAR:
            result = tacJoin(code[1], tacCreate(TAC_COPY, node->symbol, code[1]?code[1]->res:0,0));
            break;
//        case AST_VECTOR_DECL:
//            result = tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_VECTOR_DECL, code[0]?code[0]->res:0, code[1]?code[1]->res:0, 0));
//            break;
        case AST_VECTOR:
            if (code[2] != 0){
                result = tacJoin(code[2], tacCreate(TAC_COPY, node->symbol, code[2]?code[2]->res:0, 0));
            }
            break;
        case AST_KW_UNTIL:
            result = makeUntil(code[0], code[1]);
            break;
        default:
            result = tacJoin(code[0], tacJoin(code[1], tacJoin(code[2], code[3])));
            break;
    }
    return result;
}

TAC* makeFunction(TAC* symbol, TAC* code1, TAC* code2){
    return tacJoin(tacJoin(tacJoin(tacCreate(TAC_BEGINFUN, symbol->res, 0, 0), code1), code2), tacCreate(TAC_ENDFUN, symbol->res, 0, 0));
}

TAC* makeIfThen(TAC* code0, TAC* code1, TAC* code2){
    TAC* tac_if = 0;
    TAC* label_if_tac = 0;
    HASH_NODE * label_if = 0;

    label_if = makeLabel();

    tac_if = tacJoin(code0, tacCreate(TAC_IFZ, label_if, code0?code0->res:0,0));
    label_if_tac = tacCreate(TAC_LABEL, label_if, 0, 0);

    if (code2){
        HASH_NODE * label_else = makeLabel();
        TAC* label_else_tac = tacCreate(TAC_LABEL, label_else,0,0);
        TAC* jump_else_tac = tacCreate(TAC_JUMP, label_else,0,0);
        TAC* tac_if_else = tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tac_if, code1), jump_else_tac), label_if_tac), code2), label_else_tac);
        return tac_if_else;
    }

    return tacJoin(tacJoin(tac_if, code1), label_if_tac);
}

TAC* binOperation(int tac_type, TAC* code0, TAC* code1){
    return tacJoin(tacJoin(code0, code1), tacCreate(tac_type, makeTemp(), code0?code0->res:0, code1?code1->res:0));
}

TAC* makeUntil(TAC* code0, TAC* code1){
    HASH_NODE *jump_label = makeLabel();
    HASH_NODE *until_label = makeLabel();
    TAC* tac_until = 0;
    TAC* tac_jump = 0;
    TAC* tac_until_label = 0;
    TAC* tac_jump_label = 0;

    //Jump to 'jump_label' if condition is false (code0)
    tac_until = tacCreate(TAC_IFZ, jump_label, code0?code0->res:0, 0);
    tac_until_label = tacCreate(TAC_LABEL, until_label, 0, 0);

    //Jump back to 'until_label' after process
    tac_jump = tacCreate(TAC_JUMP, until_label, 0, 0);
    tac_jump_label = tacCreate(TAC_LABEL, jump_label, 0, 0);

    return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tac_until_label, code0), tac_until), code1), tac_jump), tac_jump_label);
}