#include <stdio.h>
#include <stdlib.h>

#include "AST.h"
#include "PRINT.h"
#include "parser.tab.h"
void yyerror(char *);


struct Program *alloc_Program(struct Class *_class, struct ClassMethodDef *classMethodDef, struct MainFunc *mainFunc)
{
	struct Program *prg = (struct Program *)malloc(sizeof(struct Program));
	prg->_class = _class;
	prg->classMethodDef = classMethodDef;
	prg->mainFunc = mainFunc;
	return prg;
}

struct Class *alloc_ClassList(struct Class *prev, struct Class *curr)
{
	struct Class *cls = (struct Class *)malloc(sizeof(struct Class));
	cls = curr;
	cls->prev = prev;
	return cls;
}

struct Class *alloc_Class(char *id, struct Member *priMember, struct Member *pubMember)
{
	struct Class *cls = (struct Class *)malloc(sizeof(struct Class));
	cls->id = id;
	cls->priMember = priMember;
	cls->pubMember = pubMember;
	cls->prev = NULL;
	return cls;
}

struct Member *alloc_Member(struct VarDecl *varDecl, struct MethodDecl *methodDecl, struct MethodDef *methodDef)
{
	struct Member *mb = (struct Member *)malloc(sizeof(struct Member));
	mb->varDecl = varDecl;
	mb->methodDecl = methodDecl;
	mb->methodDef = methodDef;
	returm mb;
}

struct VarDecl *alloc_VarDeclList(struct VarDecl *prev, struct VarDecl *curr)
{
	struct VarDecl *vdc = (struct VarDecl *)malloc(sizeof(struct VarDecl));
	vdc = curr;
	vdc->prev = prev;
	return vdc;
}

struct VarDecl *alloc_VarDecl(struct Type *type, struct Ident *ident, struct Expr *expr)
{
	struct VarDecl *vdc = (struct VarDecl *)malloc(sizeof(struct VarDecl));
	vdc->type = type;
	vdc->ident = ident;
	vdc->expr = expr;
	vdc->prev = NULL;
	return vdc;
}

struct MethodDecl *alloc_MethodDeclList(struct MethodDecl *prev, struct MethodDecl *curr)
{
	struct MethodDecl *mdc = (struct MethodDecl *)malloc(sizeof(struct MethodDecl));
	mdc = curr;
	mdc->prev = prev;
	return mdc;
}

struct MethodDecl *alloc_MethodDecl(char *id, struct Type *type, struct Param *param)
{
	struct MethodDecl *mdc = (struct MethodDecl *)malloc(sizeof(struct MethodDecl));
	mdc->id = id;
	mdc->type = type;
	mdc->param = param;
	mdc->prev = NULL;
	return mdcl;
}

struct MethodDef *alloc_MethodDefList(struct MethodDef *prev, struct MethodDef *curr)
{
	struct MethodDef *md = (struct MethodDef *)malloc(sizeof(struct MethodDef));
	md = curr;
	md->prev = prev;
	return md;
}

struct MethodDef *alloc_MethodDef(char *id, struct Type *type, struct Param *param, struct CompoundStmt *compoundStmt)
{
	struct MethodDef *md = (struct MethodDef *)malloc(sizeof(struct MethodDef));
	md->id = id;
	md->type = type;
	md->param = param;
	md->compoundStmt = compoundStmt;
	md->prev = NULL;
	return md;
}

struct ClassMethodDef *alloc_ClassMethodList(struct ClassMethodDef *prev, struct ClassMethodDef *curr)
{
	struct ClassMethodDef *cmd = (struct ClassMethodDef *)malloc(sizeof(struct ClassMethodDef));
	cmd = curr;
	cmd->prev = prev;
	return cmd;
}

struct ClassMethodDef *alloc_ClassMethodDef(struct Type *type, char *className, char *methodName, struct Param *param, struct CompoundStmt *compoundStmt)
{
	struct ClassMethodDef *cmd = (struct ClassMethodDef *)malloc(sizeof(struct ClassMethodDef));
	cmd->type = type;
	cmd->className = className;
	cmd->methodName = methodName;
	cmd->param = param;
	cmd->compoundStmt = compoundStmt;
	cmd->prev = NULL;
	return cmd;
}

struct MainFunc *alloc_MainFunc(struct CompoundStmt *compoundStmt)
{
	struct MainFunc *mf = (struct MainFunc *)malloc(sizeof(struct MainFunc));
	mf->compoundStmt = compoundStmt;
	return mf;
}

struct Param *alloc_ParamList(struct Param *prev, struct Param *curr)
{
	struct Param *prmlist = (struct Param *)malloc(sizeof(struct Parma));
	prmlist = curr;
	prmlist->prev = prev;
	return prmlist;
}

struct Param *alloc_Param(struct Type *type, struct Ident *ident)
{
	struct Param *prm = (struct Param *)malloc(sizeof(struct Parma));
	prm->type = type;
	prm->ident = ident;
	prm->prev = NULL;
	return prm;
}

struct Ident *alloc_Ident(char *id, int len)
{
	struct Ident *idt = (struct Ident *)malloc(sizeof(struct Ident));
	idt->id = id;
	idt->len = len;
	return idt;
}

struct Type *alloc_Type(char *id, enum Type_e e)
{
	struct Type *typ = (struct Type *)malloc(sizeof(struct Type));
	typ->id = id;
	typ->e = e;
	return typ;
}

struct CompoundStmt *alloc_CompoundStmt(struct VarDecl *varDecl, struct Stmt *stmt)
{
	struct CompoundStmt *cps = (struct CompoundStmt *)malloc(sizeof(struct CompoundStmt));
	cps->varDecl = varDecl;
	cps->stmt = stmt;
	return cps;
}

struct Stmt *alloc_StmtList(struct Stmt *prev, struct Stmt *curr)
{
	struct Stmt *stm = (struct Stmt *)malloc(sizeof(struct Stmt));
	stm = curr;
	stm->prev = prev;
	return stm;
}

struct Stmt *alloc_Stmt(enum Stmt_e e, struct ExprStmt *exprStmt)
{
	struct Stmt *stm = (struct Stmt *)malloc(sizeof(struct Stmt));
	stm->e = e;
	stm->type.exprStmt = exprStmt;
	stm->prev = NULL;
	return stm;
}

struct Stmt *alloc_Stmt(enum Stmt_e e, struct AssignStmt *assignStmt)
{
	struct Stmt *stm = (struct Stmt *)malloc(sizeof(struct Stmt));
	stm->e = e;
	stm->type.assignStmt = assignStmt;
	stm->prev = NULL;
	return stm;
}

struct Stmt *alloc_Stmt(enum Stmt_e e, struct RetStmt *retStmt)
{
	struct Stmt *stm = (struct Stmt *)malloc(sizeof(struct Stmt));
	stm->e = e;
	stm->type.retStmt = retStmt;
	stm->prev = NULL;
	return stm;
}

struct Stmt *alloc_Stmt(enum Stmt_e e, struct WhileStmt *whileStmt)
{
	struct Stmt *stm = (struct Stmt *)malloc(sizeof(struct Stmt));
	stm->e = e;
	stm->type.whileStmt = whileStmt;
	stm->prev = NULL;
	return stm;
}

struct Stmt *alloc_Stmt(enum Stmt_e e, struct DoStmt *doStmt)
{
	struct Stmt *stm = (struct Stmt *)malloc(sizeof(struct Stmt));
	stm->e = e;
	stm->type.doStmt = doStmt;
	stm->prev = NULL;
	return stm;
}

struct Stmt *alloc_Stmt(enum Stmt_e e, struct ForStmt *forStmt)
{
	struct Stmt *stm = (struct Stmt *)malloc(sizeof(struct Stmt));
	stm->e = e;
	stm->type.forStmt = forStmt;
	stm->prev = NULL;
	return stm;
}

struct Stmt *alloc_Stmt(enum Stmt_e e, struct IfStmt *ifStmt)
{
	struct Stmt *stm = (struct Stmt *)malloc(sizeof(struct Stmt));
	stm->e = e;
	stm->type.ifStmt = ifStmt;
	stm->prev = NULL;
	return stm;
}

struct Stmt *alloc_Stmt(enum Stmt_e e, struct CompoundStmt *compoundStmt)
{
	struct Stmt *stm = (struct Stmt *)malloc(sizeof(struct Stmt));
	stm->e = e;
	stm->type.compoundStmt = compoundStmt;
	stm->prev = NULL;
	return stm;
}

struct Stmt *alloc_Stmt(enum Stmt_e e)
{
	struct Stmt *stm = (struct Stmt *)malloc(sizeof(struct Stmt));
	stm->e = e;
	stm->prev = NULL;
	return stm;
}

struct ExprStmt *alloc_ExprStmt(struct Expr *expr)
{
	struct ExprStmt *eps = (struct ExprStmt *)malloc(sizeof(struct ExprStmt));
	eps->expr = expr;
	return eps;
}

struct AssignStmt *alloc_AssignStmt(struct RefVarExpr *refVarExpr, struct Expr *expr)
{
	struct AssignStmt *ass = (struct AssignStmt *)malloc(sizeof(struct AssignStmt));
	ass->refVarExpr = refVarExpr;
	ass->expr = expr;
	return ass;
}

struct RetStmt *alloc_RetStmt(struct Expr *expr)
{
	struct RetStmt *rts = (struct RetStmt *)malloc(sizeof(struct RetStmt));
	rts->expr = expr;
	return rts;
}

struct WhileStmt *alloc_WhileStmt(struct Expr *cond, struct Stmt *body)
{
	struct WhileStmt *whs = (struct WhileStmt *)malloc(sizeof(struct WhileStmt));
	whs->cond = cond;
	whs->body = body;
	return whs;
}

struct DoStmt *alloc_DoStmt(struct Expr *cond, struct Stmt *body)
{
	struct DoStmt *dos = (struct DoStmt *)malloc(sizeof(struct DoStmt));
	dos->cond = cond;
	dos->body = body;
	return dos;
}

struct ForStmt *alloc_ForStmt(struct Expr *init, struct Expr *cond, struct Expr *incr, struct Stmt *body)
{
	struct ForStmt *frs = (struct ForStmt *)malloc(sizeof(struct ForStmt));
	frs->init = init;
	frs->cond = cond;
	frs->incr = incr;
	frs->body = body;
	return frs;
}

struct IfStmt *alloc_IfStmt(struct Expr *cond, struct Stmt *ifbody, struct Stmt *elsebody)
{
	struct IfStmt *ifs = (struct IfStmt *)malloc(sizeof(struct IfStmt));
	ifs->cond = cond;
	ifs->ifBody = ifBody;
	ifs->elseBody = elseBody;
	return ifs;
}

struct Expr *alloc_Expr(enum Expr_e e, struct OperExpr *operExpr)
{
	struct Expr *exp = (struct Expr *)malloc(sizeof(struct Expr));
	exp->e = e;
	exp->type.operExpr = operExpr;
	return exp;
}

struct Expr *alloc_Expr(enum Expr_e e, struct RefExpr *refExpr)
{
	struct Expr *exp = (struct Expr *)malloc(sizeof(struct Expr));
	exp->e = e;
	exp->type.refExpr = refExpr;
	return exp;
}

struct Expr *alloc_Expr(enum Expr_e e, int intnum)
{
	struct Expr *exp = (struct Expr *)malloc(sizeof(struct Expr));
	exp->e = e;
	exp->type.intnum = intnum;
	return exp;
}

struct Expr *alloc_Expr(enum Expr_e e, float floatnum)
{
	struct Expr *exp = (struct Expr *)malloc(sizeof(struct Expr));
	exp->e = e;
	exp->type.floatnum = floatnum;
	return exp;
}

struct OperExpr *alloc_OperExpr(enum Oper_e e, struct UnOp *un)
{
	struct OperExpr *ope = (struct OperExpr *)malloc(sizeof(struct OperExpr));
	ope->e = e;
	ope->type.un = un;
	return ope;
}

struct OperExpr *alloc_OperExpr(enum Oper_e e, struct AddiOp *addi)
{
	struct OperExpr *ope = (struct OperExpr *)malloc(sizeof(struct OperExpr));
	ope->e = e;
	ope->type.addi = addi;
	return ope;
}

struct OperExpr *alloc_OperExpr(enum Oper_e e, struct MultOp *mult)
{
	struct OperExpr *ope = (struct OperExpr *)malloc(sizeof(struct OperExpr));
	ope->e = e;
	ope->type.mult = mult;
	return ope;
}

struct OperExpr *alloc_OperExpr(enum Oper_e e, struct RelaOp *rela)
{
	struct OperExpr *ope = (struct OperExpr *)malloc(sizeof(struct OperExpr));
	ope->e = e;
	ope->type.rela = rela;
	return ope;
}

struct OperExpr *alloc_OperExpr(enum Oper_e e, struct EqltOp *eqlt)
{
	struct OperExpr *ope = (struct OperExpr *)malloc(sizeof(struct OperExpr));
	ope->e = e;
	ope->type.eqlt = eqlt;
	return ope;
}

struct OperExpr *alloc_OperExpr(enum Oper_e e, struct Expr *bracket)
{
	struct OperExpr *ope = (struct OperExpr *)malloc(sizeof(struct OperExpr));
	ope->e = e;
	ope->type.bracket = bracket;
	return ope;
}

struct RefExpr *alloc_RefExpr(enum Ref_e e, struct RefVarExpr *refVarExpr)
{
	struct RefExpr *rep = (struct RefExpr *)malloc(sizeof(struct RefExpr));
	rep->e = e;
	rep->type.refVarExpr = refVarExpr;
	return rep;
}

struct RefExpr *alloc_RefExpr(enum Ref_e e, struct RefCallExpr *refCallExpr)
{
	struct RefExpr *rep = (struct RefExpr *)malloc(sizeof(struct RefExpr));
	rep->e = e;
	rep->type.refCallExpr = refCallExpr;
	return rep;
}

struct RefVarExpr *alloc_RefVarExpr(struct RefExpr *refExpr, struct IdentExpr *identExpr)
{
	struct RefVarExpr *rve = (struct RefVarExpr *)malloc(sizeof(struct RefVarExpr));
	rve->refExpr = refExpr;
	rve->identExpr = identExpr;
	return rve;
}

struct RefCallExpr *alloc_RefCallExpr(struct RefExpr *refExpr, struct CallExpr *callExpr)
{
	struct RefVarExpr *rve = (struct RefVarExpr *)malloc(sizeof(struct RefVarExpr));
	rve->refExpr = refExpr;
	rve->identExpr = identExpr;
	return rve;
}

struct IdentExpr *alloc_IdentExpr(char *id, struct Expr *expr)
{
	struct IdentExpr *ide = (struct IdentExpr *)malloc(sizeof(struct IdentExpr));
	ide->id = id;
	ide->expr = expr;
	return ide;
}

struct CallExpr *alloc_CallExpr(char *id, struct Arg *arg)
{
	struct CallExpr *calle = (struct CallExpr *)malloc(sizeof(struct CallExpr));
	calle->id = id;
	calle->arg = arg;
	return calle;
}

struct Arg *alloc_Arg(struct Expr *expr, struct Arg *prev)
{
	struct Arg *arg = (struct Arg *)malloc(sizeof(struct Arg));
	arg->expr = expr;
	arg->prev = prev;
	return arg;
}

struct UnOp *alloc_UnOp(enum Unop_e e, struct Expr *expr)
{
	struct UnOp *un = (struct UnOp *)malloc(sizeof(struct UnOp));
	un->e = e;
	un->expr = expr;
	return un;
}

struct AddiOp *alloc_AddiOp(enum Addi_e e, struct Expr *lhs, struct Expr *rhs)
{
	struct AddiOp *addi = (struct AddiOp *)malloc(sizeof(struct AddiOp));
	addi->lhs = lhs;
	addi->e = e;
	addi->rhs = rhs;
	return addi;
}

struct MultOp *alloc_MultOp(enum Mult_e e, struct Expr *lhs, struct Expr *rhs)
{
	struct MultOp *mult = (struct MultOp *)malloc(sizeof(struct MultOp));
	mult->lhs = lhs;
	mult->e = e;
	mult->rhs =rhs;
	return mult;
}

struct RelaOp *alloc_RelaOp(enum Rela_e e, struct Expr *lhs, struct Expr *rhs)
{
	struct RelaOp *rela = (struct RelaOp *)malloc(sizeof(struct RelaOp));
	rela->lhs = lhs;
	rela->e = e;
	rela->rls = rls;
	return rela;
}

struct EqltOp *alloc_EqltOp(enum Eqlt_e e, struct Expr *lhs, struct Expr *rhs)
{
	struct EqltOp *eqlt = (struct EqltOp *)malloc(sizeof(struct EqltOp));
	eqlt->lhs = lhs;
	eqlt->e = e;
	eqult->rhs = rhs;
	return eqlt;
}