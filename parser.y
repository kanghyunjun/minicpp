
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AST.h"

int yylex();
void yyerror(char *);
%}

%union {
	struct Program *ptr_prg;	

	struct Class *ptr_cls;
	struct Member *ptr_mb;

	struct VarDecl *ptr_vdc;
	struct MethodDecl *ptr_mdc;
	struct MethodDef *ptr_md;
	struct ClassMethodDef *ptr_cmd;
	struct MainFunc *ptr_mf;

	struct Param *ptr_prm;
	struct Ident *ptr_idt;
	struct Type *ptr_typ;
	
	struct CompoundStmt *ptr_cps;
	struct Stmt *prt_stm;
	struct ExprStmt *ptr_eps;
	struct AssignStmt *ptr_ass;
	struct RetStmt *ptr_rts;
	struct WhileStmt *ptr_whs;
	struct DoStmt *ptr_dos;
	struct ForStmt *ptr_frs;
	struct IfStmt *ptr_ifs;
	
	struct Expr *ptr_exp;
	struct OperExpr *ptr_ope;
	struct RefExpr *ptr_rep;
	struct RefVarExpr *ptr_rve;
	struct RefCallExpr *ptr_rce;
	struct IdentExpr *ptr_ide;
	struct CallExpr *ptr_calle;
	struct Arg *ptr_arg;

	struct UnOp *prt_un;
	struct AddiOp *ptr_addi;
	struct MultOp *ptr_mult;
	struct RelaOp *ptr_rela;
	struct EqltOp *ptr_eqlt;	
	
	char op;
	string id;
	int intnum;
	float floatnum;
}

%token ADD SUB MUL DIV LT GT LE GE EQ NE
%token <op> UNOP ADDIOP MULTOP RELAOP EQLTOP
%token <id> ID <intnum> INTNUM <floatnum> FLOATNUM
%token CLASS PRIVATE PUBLIC
%token MAIN
%token INT FLOAT
%token IF ELSE
%token FOR
%token DO WHILE
%token RETURN

%type <ptr_prg> Program

%type <ptr_cls> Class
%type <ptr_mb> Member

%type <ptr_vdc> VarDecl
%type <ptr_mdc> MethodDecl
%type <ptr_md> MethodDef
%type <ptr_cmd> ClassMethodDef
%type <ptr_mf> MainFunc

%type <ptr_prm> Param
%type <ptr_idt> Ident
%type <ptr_typ> Type

%type <ptr_cps> CompoundStmt
%type <ptr_stm> Stmt
%type <ptr_eps> ExprStmt
%type <ptr_ass> AssignStmt
%type <ptr_rst> RetStmt
%type <ptr_whs> WhileStmt
%type <ptr_dos> DoStmt
%type <ptr_frs> ForStmt
%type <ptr_ifs> IfStmt

%type <ptr_exp> Expr
%type <ptr_ope> OperExpr
%type <ptr_rep> RefExpr
%type <ptr_rve> RefVarExpr
%type <ptr_rce> RefCallExpr
%type <ptr_ide> IdentExpr
%type <ptr_calle> CallExpr
%type <ptr_arg> Arg

%type <ptr_un> UnOp
%type <ptr_addi> AddiOp
%type <ptr_mult> MultOp
%type <ptr_rela> RelaOp
%type <ptr_eqlt> EqltOp

%%

Program: MainFunc				{ $$ = alloc_Program(NULL, NULL, $1); printf(dfs()); }
|	ClassList MainFunc			{ $$ = alloc_Program($1, NULL, $2); }
|	ClassMethodList MainFunc		{ $$ = alloc_Program(NULL, $1, $2); }
|	ClassList ClassMethodList MainFunc 	{ $$ = alloc_Program($1, $2, $3); }
;

ClassList: Class		{ $$ = $1; }
|	ClassList Class		{ $$ = alloc_ClassList($1, $2); }
;

Class: CLASS ID '{' '}'				{ $$ = alloc_Class($2, NULL, NULL); }
|	CLASS ID '{' PRIVATE ' : ' Member '}'	{ $$ = alloc_Class($2, $6, NULL); }
|	CLASS ID '{' PUBLIC ' : ' Member '}'	{ $$ = alloc_Class($2, NULL, $6); }
|	CLASS ID '{' PRIVATE ' : ' Member PUBLIC ' : ' Member '}'	{ $$ = alloc_Class($2, $6, $9); }
;

Member: 			{ $$ = alloc_Member(NULL, NULL, NULL); }
|	VarDeclList		{ $$ = alloc_Member($1, NULL, NULL); }
|	MethodDeclList		{ $$ = alloc_Member(NULL, $1, NULL); }
|	MethodDefList		{ $$ = alloc_Member(NULL, NULL, $1); }
|	VarDeclList MethodDeclList	{ $$ = alloc_Member($1, $2, NULL); }
|	VarDeclList MethodDefList	{ $$ = alloc_Member($1, NULL, $2); }
|	MethodDeclList MethodDefList	{ $$ = alloc_Member(NULL, $1, $2); }
|	VarDeclList MethodDeclList MethodDefList	{ $$ = alloc_Member($1, $2, $3); }
;

VarDeclList: VarDecl		{ $$ = $1; }
|	VarDeclList VarDecl	{ $$ = alloc_VarDeclList($1, $2); }
;

VarDecl: Type Ident ';'			{ $$ = alloc_VarDecl($1, $2, NULL); }
|	Type Ident '=' INT ';'		{ $$ = alloc_VarDecl($1, $2, $4); }
|	Type Ident '=' FLOAT ';'	{ $$ = alloc_VarDecl($1, $2, $4); }
;

MethodDeclList: MethodDecl		{ $$ = $1; }
|	MethodDeclList MethodDecl	{ $$ = alloc_MethodDeclList($1, $2); }
;

MethodDecl: Type ID '(' ')' ';'		{ $$ = alloc_MethodDecl($2, $1, NULL); }
|	Type ID '(' ParamList ')' ';'	{ $$ = alloc_MethodDecl($2, $1, $4); }
;

MethodDefList: MethodDef		{ $$ = $1; }
|	MethodDefList MethodDef	{ $$ = alloc_MethodDefList($1, $2); }
;

MethodDef: Type ID '(' ')' CompoundStmt	{ $$ = alloc_MethodDef($2, $1, NULL, $5); }
|	Type ID '(' ParamList ')' CompoundStmt{ $$ = alloc_MethodDef($2, $1, $4, $6); }
;

ClassMethodList: ClassMethodDef		{ $$ = $1; }
|	ClassMethodList ClassMethodDef	{ $$ = alloc_ClassMethodList($1, $2); }
;

ClassMethodDef: Type ID '::' ID '(' ')' CompoundStmt	{ $$ = alloc_ClassMethoDef($1, $2, $4, NULL, $7); }
|	Type ID '::' ID '(' ParamList ')' CompoundStmt	{ $$ = alloc_ClassMethoDef($1, $2, $4, $6, $8); }
;

MainFunc: INT MAIN '(' ')' CompoundStmt	{ $$ = alloc_MainFunc($5); }
;

ParamList: Param		{ $$ = $1; }
|	Param ', ' ParamList	{ $$ = alloc_ParamList($1, $3): }
;

Param: Type Ident	{ $$ = alloc_Param($1, $2); }
;

Ident: ID			{ $$ = alloc_Ident($1, 0); }
|	ID '[' INTNUM ']'	{ $$ = alloc_Ident($1, $3); }
;

Type: INT	{ $$ = alloc_Type(NULL, eInt); }
|	FLOAT	{ $$ = alloc_Type(NULL, eFloat); }
|	ID	{ $$ = alloc_Type($1, eClass); }
;

CompoundStmt: '{' '}'			{ $$ = alloc_CompoundStmt(NULL, NULL); }
|	'{' VarDeclList '}'		{ $$ = alloc_CompoundStmt($2, NULL); }
|	'{' StmtList '}'			{ $$ = alloc_CompoundStmt(NULL, $2); }
|	'{' VarDeclList StmtList '}'	{ $$ = alloc_CompoundStmt($2, $3); }
;

StmtList: Stmt		{ $$ = $1; }
|	StmtList Stmt	{ $$ = alloc_StmtList($1, $2); }
;

Stmt: ExprStmt		{ $$ = alloc_Stmt(eExpr, $1); }
|	AssignStmt	{ $$ = alloc_Stmt(eAssign, $1); }
|	RetStmt	{ $$ = alloc_Stmt(eRet, $1); }
|	WhileStmt	{ $$ = alloc_Stmt(eWhile, $1); }
|	DoStmt		{ $$ = alloc_Stmt(eDo, $1); }
|	ForStmt	{ $$ = alloc_Stmt(eFor, $1); }
|	IfStmt		{ $$ = alloc_Stmt(eIf, $1); }
|	CompoundStmt	{ $$ = alloc_Stmt(eCompound, $1); }
|	';'		{ $$ = alloc_Stmt(eSemi); }
;

ExprStmt: Expr ';'	{ $$ = alloc_ExprStmt($1); }
;

AssignStmt: RefVarExpr '=' Expr ';'	{ $$ = alloc_AssignStmt($1, $3); }
;

RetStmt: RETURN ';'	{ $$ = alloc_RetStmt(NULL); }
| RETURN Expr ';'	{ $$ = alloc_RetStmt($2); }
;

WhileStmt: WHILE '(' Expr ')' Stmt	{ $$ = alloc_WhileStmt($3, $5); }
;

DoStmt: DO Stmt WHILE '(' Expr ')' ';'		{ $$ = alloc_DoStmt($2, $5); }
;

ForStmt: FOR '(' Expr ';' Expr ';' Expr ')' Stmt	{ $$ = alloc_ForStmt($3, $5, $7, $9); }
;

IfStmt: IF '(' Expr ')' Stmt		{ $$ = alloc_IfStmt($3, $5, NULL); }
|	IF '(' Expr ')' Stmt ELSE Stmt	{ $$ = alloc_IfStmt($3, $5, $7); }
;

Expr: OperExpr		{ $$ = alloc_Expr(eOper, $1); }
|	RefExpr	{ $$ = alloc_Expr(eRef, $1); }
|	INTNUM	{ $$ = alloc_Expr(eIntnum, $1); }
|	FLOATNUM	{ $$ = alloc_Expr(eFloatnum, $1); }
;

OperExpr: UNOP Expr		{ $$ = alloc_OperExpr(eUn, $1); }
|	Expr ADDIOP Expr	{ $$ = alloc_OperExpr(eAddi, $2); }
|	Expr MULTOP Expr	{ $$ = alloc_OperExpr(eMult, $2); }
|	Expr RELAOP Expr	{ $$ = alloc_OperExpr(eRela, $2); }
|	Expr EQLTOP Expr	{ $$ = alloc_OperExpr(eEqlt, $2); }
|	'(' Expr ')'		{ $$ = alloc_OperExpr(eBracket, $2); }
;

RefExpr: RefVarExpr	{ $$ = alloc_RefExpr(eVar, $1); }
|	RefCallExpr	{ $$ = alloc_RefExpr(eCall, $1); }
;

RefVarExpr: IdentExpr		{ $$ = alloc_RefVarExpr(NULL, $1); }
|	RefExpr '.' IdentExpr	{ $$ = alloc_RefVarExpr($1, $3); }
;


RefCallExpr: CallExpr		{ $$ = alloc_RefCallExpr(NULL, $1); }
|	RefExpr '.' CallExpr	{ $$ = alloc_RefVarExpr($1, $3); }
;

IdentExpr: ID '[' Expr ']'	{ $$ = alloc_IdentExpr($1, $3); }
|	ID			{ $$ = alloc_IdentExpr($1, NULL); }
;

CallExpr: ID '(' ')'		{ $$ = alloc_CallExpr($1, NULL); }
|	ID '(' ArgList ')'		{ $$ = alloc_CallExpr($1, $3); }

;

Arg: Expr		{ $$ = alloc_Arg($1, NULL); }
|	Arg ', ' Expr	{ $$ = alloc_Arg($3, $1); }
;

Unop: '-' Expr	{ $$ = alloc_UnOp(eNegative, $2); }
;

AddiOp: Expr ADD Expr	{ $$ = alloc_AddiOp($1, ePlus, $3); }
|	Expr SUB Expr	{ $$ = alloc_AddiOp($1, eMinus, $3); }
;

Multop: Expr MUL Expr	{ $$ = alloc_MultOp($1, eMul, $3); }
|	Expr DIV Expr	{ $$ = alloc_MultOp($1, eDiv, $3); }
;

Relaop: Expr LT Expr	{ $$ = alloc_RelaOp($1, eLT, $3); }
|	Expr GT Expr	{ $$ = alloc_RelaOp($1, eGT, $3); }
|	Expr LE Expr	{ $$ = alloc_RelaOp($1, eLE, $3); }
|	Expr GE Expr	{ $$ = alloc_RelaOp($1, eGE, $3); }
;

Eqltop: Expr EQ Expr	{ $$ = alloc_EqltOp($1, EQ, $3); }
|	Expr NE Expr	{ $$ = alloc_EqltOp($1, NE, $3); }
;

%%

int main(void) {
	yyparse();
	return 0;
}

void yyerror(char *s) {
	fprintf(stderr, "error: %s\n", s);
}