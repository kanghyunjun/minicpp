/**
 * Copyright (C) 2017 ARCS lab - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the ARCS license
 *
 * You should have received a copy of the ARCS license with
 * this file. If not, please write to: jhpark@arcs.skku.edu
 *
 * Freely use this source code, but not allowed for any
 * commercial uses.
 */

#ifndef AST_H
#define AST_H

typedef char bool;
#define true 1
#define false 0

/**
 * Before you started..
 *
 * This file is a header file to implement the Abstract Syntax Tree(AST).
 * You have to use the following structs as the nodes of the tree.
 * This file will be included in bison implementation and tree walker.
 * There are some informations that helps you using this header easly.
 * So we recommend you to read carefully not olny this comment,
 * but also those written in each line.
 * 
 * First of all, all nodes are designed to target the visitor model.
 * There are two models of tree walkers; visitor and listener.
 * In visitor model, the developer controls the order of tree walks one by one.
 * You are developer in this case.
 * For example, when the tree walker program meets "Expr - Expr",
 * you have to make the program visit the right-hand side first at this time.
 *
 * The next information is how to implement "List" structs.
 * All structs of List is implemented in linked list.
 * The variable named "prev" connect between node.
 * The reason not using "next" variable is related to the execution model of Bison.
 * Bison tool is designed for visiting leaf node first.
 * It means that the parser will stack the nodes up while generating AST.
 */

typedef enum
{eInt, eFloat, eClass} Type_e;
typedef enum
{eExpr, eAssign, eRet, eWhile, eDo, eFor, eIf, eCompound, eSemi} Stmt_e;
typedef enum
{eOper, eRef, eIntnum, eFloatnum} Expr_e;
typedef enum
{eUn, eAddi, eMult, eRela, eEqlt, eBracket} Oper_e;
typedef enum
{eVar, eCall} Ref_e;
typedef enum
{eNegative} Unop_e;
typedef enum
{ePlus, eMinus} Addi_e;
typedef enum
{eMul, eDiv} Mult_e;
typedef enum
{eLT, eGT, eLE, eGE} Rela_e;
typedef enum
{eEQ, eNE} Eqlt_e;

// Program := (ClassList)? (ClassMethod)? MainFunc
struct Program {
	struct Class *_class;
	struct ClassMethodDef *classMethodDef;
	struct MainFunc *mainFunc;
};

struct Program *alloc_Program(struct Class *, struct ClassMethodDef *, struct MainFunc *);

// ClassList := (Class)+
// Class := class id { (private : Member)? (public : Member)? }
struct Class {
	char *id;
	struct Member *priMember;
	struct Member *pubMember;
	struct Class *prev;
};

struct Class *alloc_ClassList(struct Class *, struct Class *);

struct Class *alloc_Class(char *, struct Member *, struct Member *);

// Member := (VarDeclList)? (MethodDeclList)? (MethodDefList)?
struct Member {
	struct VarDecl *varDecl;
	struct MethodDecl *methodDecl;
	struct MethodDef *methodDef;
};

struct Member *alloc_Member(struct VarDecl *, struct MethodDecl *, struct MethodDef);

// VarDeclList := (VarDecl)+
// VarDecl := Type Ident (= (int|float))? ;
struct VarDecl {
	struct Type *type;
	struct Ident *ident;
	struct Expr *expr;
	struct VarDecl *prev;
};

struct VarDecl *alloc_VarDeclList(struct VarDecl *, struct VarDecl *);

struct VarDecl *alloc_VarDecl(struct Type *, struct Ident *, struct Expr *);

// MethodDeclList := (MethodDecl)+
// MethodDecl := Type id ( (ParamList)? ) ;
struct MethodDecl {
	char *id;
	struct Type *type;
	struct Param *param;
	struct MethodDecl *prev;
};

struct MethodDecl *alloc_MethodDeclList(struct MethodDecl *, struct MethodDecl *);

struct MethodDecl *alloc_MethodDecl(char *, struct Type *, struct Param *);

// MethodDefList := (MethodDef)+
// MethodDef := Type id ( (ParamList)? ) CompoundStmt
struct MethodDef {
	char *id;
	struct Type *type;
	struct Param *param;
	struct CompoundStmt *compoundStmt;
	struct MethodDef *prev;
};

struct MethodDef *alloc_MethodDefList(struct MethodDef *, struct MethodDef *);

struct MethodDef *alloc_MethodDef(char *, struct Type *, struct Param *, struct CompoundStmt *);

// ClassMethodList := (ClassMethodDef)+
// ClassMethodDef := Type id :: id ( (ParamList)? ) CompoundStmt
struct ClassMethodDef {
	struct Type *type;
	char *className;
	char *methodName;
	struct Param *param;
	struct CompoundStmt *compoundStmt;
	struct ClassMethodDef *prev;
};

struct ClassMethodDef *alloc_ClassMethodList(struct ClassMethodDef *, struct ClassMethodDef *);

struct ClassMethodDef *alloc_ClassMethodDef(char *, char *, struct Param *, struct CompoundStmt *);

// MainFunc := int main ( ) CompoundStmt
struct MainFunc {
	struct CompoundStmt *compoundStmt;
};

struct MainFunc *alloc_MainFunc(struct CompoundStmt *);

// ParamList := Param (, Param)*
// Param := Type Ident
struct Param {
	struct Type *type;
	struct Ident *ident;
	struct Param *prev;
};

struct Param *alloc_ParamList(struct Param *, struct Param *);

struct Param *alloc_Param(struct Type *, struct Ident *);

// Ident := id
//        | id [ intnum ]
struct Ident {
	char *id;
	int len; // 0 if scalar
};

struct Ident *alloc_Ident(char*, int);

// Type := int
//       | float
//       | id
struct Type {
	char *id; // NULL unless class type
	Type_e e;
};

struct Type *alloc_Type(char*, enum Type_e);

// CompoundStmt := { (VarDeclList)? (StmtList)? }
struct CompoundStmt {
	struct VarDecl *varDecl;
	struct Stmt *stmt;
};

struct CompoundStmt *alloc_CompoundStmt(struct VarDecl *, struct Stmt *);

// StmtList := (Stmt)+
// Stmt := ExprStmt
//       | AssignStmt
//       | RetStmt
//       | WhileStmt
//       | DoStmt
//       | ForStmt
//       | IfStmt
//       | CompoundStmt
//       | ;
struct Stmt {
	Stmt_e e;
	union {
		struct ExprStmt *exprStmt;
		struct AssignStmt *assignStmt;
		struct RetStmt *retStmt;
		struct WhileStmt *whileStmt;
		struct DoStmt *doStmt;
		struct ForStmt *forStmt;
		struct IfStmt *ifStmt;
		struct CompoundStmt *compoundStmt;
	} type;
	struct Stmt *prev;
};

struct Stmt *alloc_StmtList(struct Stmt *, struct Stmt *);

struct Stmt *alloc_Stmt(enum Stmt_e, struct ExprStmt *);
struct Stmt *alloc_Stmt(enum Stmt_e, struct AssignStmt *);
struct Stmt *alloc_Stmt(enum Stmt_e, struct RetStmt *);
struct Stmt *alloc_Stmt(enum Stmt_e, struct WhileStmt *);
struct Stmt *alloc_Stmt(enum Stmt_e, struct DoStmt *);
struct Stmt *alloc_Stmt(enum Stmt_e, struct ForStmt *);
struct Stmt *alloc_Stmt(enum Stmt_e, struct IfStmt *);
struct Stmt *alloc_Stmt(enum Stmt_e, struct CompoundStmt *);
struct Stmt *alloc_Stmt(enum Stmt_e);


// ExprStmt := Expr ;
struct ExprStmt {
	struct Expr *expr;
};

struct ExprStmt *alloc_ExprStmt(struct Expr *);


// AssignStmt := RefVarExpr = Expr ;
struct AssignStmt {
	struct RefVarExpr *refVarExpr;
	struct Expr *expr;
};

struct AssignStmt *alloc_AssignStmt(struct RefVarExpr *, struct Expr *);

// RetStmt := return (Expr)? ;
struct RetStmt {
	struct Expr *expr;
};

struct RetStmt *alloc_RetStmt(struct Expr *);

// WhileStmt := while ( Expr ) Stmt
struct WhileStmt {
	struct Expr *cond;
	struct Stmt *body;
};

struct WhileStmt *alloc_WhileStmt(struct Expr *, struct Stmt *);

// DoStmt := do Stmt while ( Expr ) ;
struct DoStmt {
	struct Expr *cond;
	struct Stmt *body;
};

struct DoStmt *alloc_DoStmt(struct Expr *, struct Stmt *);

// ForStmt := for ( Expr ; Expr ; Expr ) Stmt
struct ForStmt {
	struct Expr *init, *cond, *incr;
	struct Stmt *body;
};

struct ForStmt *alloc_ForStmt(struct Expr *, struct Expr *, struct Expr *, struct Stmt *);

// IfStmt := if ( Expr ) Stmt (else Stmt)?
struct IfStmt {
	struct Expr *cond;
	struct Stmt *ifBody;
	struct Stmt *elseBody;
};

struct IfStmt *alloc_IfStmt(struct Expr *, struct Stmt *, struct Stmt *);


// Expr := OperExpr
//       | RefExpr
//       | intnum
//       | floatnum
struct Expr {
	Expr_e e;
	union {
		struct OperExpr *operExpr;
		struct RefExpr *refExpr;
		int intnum;
		float floatnum;
	} type;
};

struct Expr *alloc_Expr(enum Expr_e, struct OperExpr *);
struct Expr *alloc_Expr(enum Expr_e, struct RefExpr *);
struct Expr *alloc_Expr(enum Expr_e, int);
struct Expr *alloc_Expr(enum Expr_e, float);


// OperExpr := unop Expr
//           | Expr addiop Expr
//           | Expr multop Expr
//           | Expr relaop Expr
//           | Expr eqltop Expr
//           | ( Expr )
struct OperExpr {
	Oper_e e;
	union {
		struct UnOp *un;
		struct AddiOp *addi;
		struct MultOp *mult;
		struct RelaOp *rela;
		struct EqltOp *eqlt;
		struct Expr *bracket;
	} type;
};

struct OperExpr *alloc_OperExpr(enum Oper_e, struct UnOp *);
struct OperExpr *alloc_OperExpr(enum Oper_e, struct AddiOp *);
struct OperExpr *alloc_OperExpr(enum Oper_e, struct MultOp *);
struct OperExpr *alloc_OperExpr(enum Oper_e, struct RelaOp *);
struct OperExpr *alloc_OperExpr(enum Oper_e, struct EqltOp *);
struct OperExpr *alloc_OperExpr(enum Oper_e, struct Expr *);

// RefExpr := RefVarExpr
//          | RefCallExpr
struct RefExpr {
	Ref_e e;
	union {
		struct RefVarExpr *refVarExpr;
		struct RefCallExpr *refCallExpr;
	} type;
};

struct RefExpr *alloc_RefExpr(enum Ref_e, struct RefVarExpr *);
struct RefExpr *alloc_RefExpr(enum Ref_e, struct RefCallExpr *);

// RefVarExpr := (RefExpr .)? IdentExpr
struct RefVarExpr {
	struct RefExpr *refExpr;
	struct IdentExpr *identExpr;
};

struct RefVarExpr *alloc_RefVarExpr(struct RefExpr *, struct IdentExpr *);

// RefCallExpr := (RefExpr .)? CallExpr
struct RefCallExpr {
	struct RefExpr *refExpr;
	struct CallExpr *callExpr;
};

struct RefCallExpr *alloc_RefCallExpr(struct RefExpr *, struct CallExpr *);

// IdentExpr := id [ Expr ]
//            | id
struct IdentExpr {
	char *id;
	struct Expr *expr; // NULL if scalar
};

struct IdentExpr *alloc_IdentExpr(char *, struct Expr *);

// CallExpr := id ( (ArgList)? )
struct CallExpr {
	char *id;
	struct Arg *arg;
};

struct CallExpr *alloc_CallExpr(char *, struct Arg *);

// ArgList := Expr (, Expr)*
struct Arg {
	struct Expr *expr;
	struct Arg *prev;
};

struct Arg *alloc_Arg(struct Expr *, struct Arg *);

/** Following definitions are additional structs for OperExpr. **/
struct UnOp {
	Unop_e e;
	struct Expr *expr;
};

struct UnOp *alloc_UnOp(enum Unop_e, struct Expr *);

struct AddiOp {
	Addi_e e;
	struct Expr *lhs;
	struct Expr *rhs;
};

struct AddiOp *alloc_AddiOp(enum Addi_e, struct Expr *, struct Expr *);

struct MultOp {
	Mult_e e;
	struct Expr *lhs;
	struct Expr *rhs;
};

struct MultOp *alloc_MultOp(enum Mult_e, struct Expr *, struct Expr *);

struct RelaOp {
	Rela_e e;
	struct Expr *lhs;
	struct Expr *rhs;
};

struct RelaOp *alloc_RelaOp(enum Rela_e, struct Expr *, struct Expr *);

struct EqltOp {
	Eqlt_e e;
	struct Expr *lhs;
	struct Expr *rhs;
};

struct EqltOp *alloc_EqltOp(enum Eqlt_e, struct Expr *, struct Expr *);

#endif
