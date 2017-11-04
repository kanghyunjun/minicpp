#ifndef PRINT_H
#define PRINT_H

#include "AST.h"


struct Program *head;

void dfs(void);
void compile_Class(struct Class *);
void compile_ClassList(struct Class *);
void compile_Member(struct Member *);
void compile_VarDecl(struct VarDecl *);
void compile_VarDeclList(struct VarDecl *);
void compile_MethodDecl(struct MethodDecl *);
void compile_MethodDeclList(struct MethodDecl *);
void compile_MethodDef(struct MethodDef *);
void compile_MethodDefList(struct MethodDef *);
void compile_ClassMethodDef(struct ClassMethodDef *);
void compile_ClassMethodDefList(struct ClassMethodDef *);
void compile_MainFunc(struct MainFunc *);
void compile_Param(struct Param *);
void compile_ParamList(struct Param *);
void compile_Ident(struct Ident *);
void compile_Type(struct Type *);
void compile_CompoundStmt(struct CompoundStmt *);
void compile_Stmt(struct Stmt *);
void compile_StmtList(struct Stmt *);
void compile_ExprStmt(struct ExprStmt *);
void compile_AssignStmt(struct AssignStmt *);
void compile_RetStmt(struct RetStmt *);
void compile_WhileStmt(struct WhileStmt *);
void compile_DoStmt(struct DoStmt *);
void compile_ForStmt(struct FoRStmt *);
void compile_IfStmt(struct IfStmt *);
void compile_Expr(struct Expr *);
void compile_OperExpr(struct OperExpr *);
void compile_RefExpr(struct RefExpr *);
void compile_RefVarExpr(struct RefVarExpr *);
void compile_RefCallExpr(struct RefCallExpr *);
void compile_IdentExpr(struct IdentExpr *);
void compile_CallExpr(struct CallExpr *);
void compile_Arg(struct Arg *);
void compile_UnOp(struct UnOp *);
void compile_AddiOp(struct AddiOp *);
void compile_MultOp(struct MultOp *);
void compile_RelaOp(struct RelaOp *);
void compile_EqltOp(struct EqltOp *);

#endif