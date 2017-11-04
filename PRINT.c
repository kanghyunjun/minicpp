#include <stdio.h>

#include "AST.h"
#include "PRINT.h"


void dfs() {
	if (head == NULL) {
		fprintf(stderr, "program does not exist.\n");
		return;
	}
	
	if (head->_class && head->classMethodDef)
	{
		compile_ClassList(head->_class);
		compile_ClassMethodDefList(head->classMethodDef);
	}
	else if (head->_class && !head->classMethodDef)
	{
		compile_ClassList(head->_class);
	}
	else if (!head->_class && head->classMethodDef)
	{
		compile_ClassMethodDefList(head->classMethodDef);
	}

	compile_MainFunc(head->mainFunc);
}

void compile_Class(struct Class *cls)
{
	if (cls == NULL)
		return;
	else
	{
		fprintf(fp, "class ");
		fprintf(fp, cls->id);
		fprintf(fp, " { ");
		if (cls->priMember && cls->pubMember)
		{
			compile_Member(cls->priMember);
			fprintf(fp, "\n");
			compile_Member(cls->pubMember);
		}
		else if (cls->priMember && !cls->pubMember)
		{
			compile_Member(cls->priMember);
		}
		else if (!cls->priMember && cls->pubMember)
		{
			compile_Member(cls->pubMember);
		}
		fprintf(fp, " }");
	}
}

void compile_ClassList(struct Class *clslist)
{
	if (clslist == NULL)
		return;
	else
	{
		if (clslist->prev)
		{
			compile_Class(clslist->prev);
			fprintf(fp, "\n");
		}
		compile_Class(clslist);
	}
}

void compile_Member(struct Member *mb)
{
	if (mb == NULL)
		return;
	else
	{
		if (mb->varDecl && mb->methodDecl && mb->methodDef)
		{
			compile_VarDeclList(mb->varDecl);
			fprintf(fp, "\n");
			compile_MethodDeclList(mb->methodDecl);
			fprintf(fp, "\n");
			compile_MethodDefList(mb->methodDef);
		}
		else if (!mb->varDecl && mb->methodDecl && mb->methodDef)
		{
			compile_MethodDeclList(mb->methodDecl);
			fprintf(fp, "\n");
			compile_MethodDefList(mb->methodDef);
		}
		else if (mb->varDecl && !mb->methodDecl && mb->methodDef)
		{
			compile_VarDeclList(mb->varDecl);
			fprintf(fp, "\n");
			compile_MethodDefList(mb->methodDef);
		}
		else if (mb->varDecl && mb->methodDecl && !mb->methodDef)
		{
			compile_VarDeclList(mb->varDecl);
			fprintf(fp, "\n");
			compile_MethodDeclList(mb->methodDecl);
		}
		else if (!mb->varDecl && !mb->methodDecl && mb->methodDef)
		{
			compile_MethodDefList(mb->methodDef);
		}
		else if (!mb->varDecl && mb->methodDecl && !mb->methodDef)
		{
			compile_MethodDeclList(mb->methodDecl);
		}
		else if (mb->varDecl && !mb->methodDecl && !mb->methodDef)
		{
			compile_VarDeclList(mb->varDecl);
		}
	}
}

void compile_VarDecl(struct VarDecl *vdc)
{
	if (vdc == NULL)
		return;
	else
	{
		compile_Type(vdc->type);
		fprintf(fp, " ");
		compile_Ident(vdc->ident);
		if (vdc->expr)
		{
			fprintf(fp, " = ");
			fprintf(fp, vdc->expr);
		}
		fprintf(fp, ";");
	}
}

void compile_VarDeclList(struct VarCecl *vdclist)
{
	if (vdclist == NULL)
		return;
	else
	{
		if (vdclist->prev)
		{
			compile_VarDecl(vdclist->prev);
			fprintf(fp, "\n");
		}
		compile_VarDecl(vdclist);
	}
}

void compile_MethodDecl(struct MethodDecl *mdc)
{
	if (mdc == NULL)
		return;
	else
	{
		compile_Type(mdc->type);
		fprintf(fp, " ");
		fprintf(fp, mdc->id);
		fprintf(fp, "(")
		if (mdc->param)
			compile_ParamList(mdc->param);
		fprintf(fp, ");");
	}
}

void compile_MethodDeclList(struct MethodDecl *mdclist)
{
	if (mdclist == NULL)
		return;
	else
	{
		if (mdclist->prev)
		{
			compile_MethodDecl(mdclist->prev);
			fprintf(fp, "\n");
		}
		compile_MethodDecl(mdclist);
	}
}

void compile_MethodDef(struct MethodDef *md)
{
	if (md == NULL)
		return;
	else
	{
		compile_Type(md->type);
		fprintf(fp, " ");
		fprintf(fp, md->id);
		fprintf(fp, "(");
		if (mdc->param)
			compile_ParamList(md->param);
		fprintf(fp, ") ");
		fprintf(fp, compoundStmt);
	}
}

void compile_MethodDefList(struct MethodDef *mdlist)
{
	if (mdlist == NULL)
		return;
	else
	{
		if (mdlist->prev)
		{
			compile_MethodDef(mdlist->prev);
			fprintf(fp, "\n");
		}
		compile_MethodDef(mdlist);
	}
}

void compile_ClassMethodDef(struct ClassMethodDef *cmd)
{
	if (cmd == NULL)
		return;
	else
	{
		compile_Type(cmd->type);
		fprintf(fp, " ");
		fprintf(fp, cmd->className);
		fprintf(fp, "::");
		fprintf(fp, cmd->methodName);
		fprintf(fp, "(");
		if (cmd->param)
			compile_ParamList(cmd->param);
		fprintf(fp, ") ");
		compile_CompoundStmt(cmd->compoundStmt);
	}
}

void compile_ClassMethodList(struct ClassMethodDef *cmdlist)
{
	if (cmdlist == NULL)
		return;
	else
	{
		if (cmdlist->prev)
		{
			compile_ClassMethodDef(cmdlist->prev);
			fprintf(fp, "\n");
		}
		compile_ClassMethodDef(cmdlist);
	}
}

void compile_MainFunc(struct MainFunc *mf)
{
	if (mf == NULL)
		return;
	else
	{
		fprintf(fp, "int main () ");
		compile_CompoundStmt(mf->compoundStmt);
	}
}

void compile_Param(struct Param *prm)
{
	if (prm == NULL)
		return;
	else
	{
		compile_Type(prm->type);
		fprintf(fp, " ");
		compile_Ident(prm->ident);
	}
}

void compile_ParamList(struct ParamDecl *prmlist)
{
	if (prmlist == NULL)
		return;
	else
	{
		if (prmlist->prev)
		{
			compile_Param(prmlist->prev);
			fprintf(fp, "\n");
		}
		compile_Param(prmlist);
	}
}

void compile_Ident(struct Ident *idt)
{
	if (idt == NULL)
		return;
	else
	{
		fprintf(fp, idt->id);
		if (idt->len != 0)
		{
			fprintf(fp, " [");
			fprintf(fp, idt->len);
			fprintf(fp, "]");
		}
	}
}

void compile_Type(struct Type *typ)
{
	if (typ == NULL)
		return;
	else
	{
		if (typ->e == eInt)
			fprintf(fp, "int");
		else if (typ->e == eFloat)
			fprintf(fp, "float");
		else if (type->e == eClass)
			fprintf(fp, type->id);
	}
}

void compile_CompoundStmt(struct CompoundStmt *cps)
{
	if (cps == NULL)
		return;
	else
	{
		fprintf(fp, "{ ");
		if (cps->varDecl && cps->stmt)
		{
			compile_VarDeclList(cps->varDecl);
			fprintf(fp, "\n");
			compile_StmtList(cps->stmt);
		}
		else if (!cps->varDecl && cps->stmt)
		{
			compile_StmtList(cps->stmt);
		}
		else if (cps->varDecl && !cps->stmt)
		{
			compile_VarDeclList(cps->varDecl);
		}
		fprintf(fp, " }");
	}
}

void compile_Stmt(struct Stmt *stm)
{
	if (stm == NULL)
		return;
	else
	{
		switch (stm->e)
		{
		case eExpr:
			compile_ExprStmt(stm->type.exprStmt);
			break;
		case eAssign:
			compile_AssignStmt(stm->type.assignStmt);
			break;
		case eRet:
			compile_RetStmt(stm->type.retStmt);
			break;
		case eWhile:
			compile_WhileStmt(stm->type.whileStmt);
			break;
		case eDo:
			compile_DoStmt(stm->type.doStmt);
			break;
		case eFor:
			compile_ForStmt(stm->type.forStmt);
			break;
		case eIf:
			compile_IfStmt(stm->type.ifStmt);
			break;
		case eCompound:
			compile_CompoundStmt(stm->type.compoundStmt);
			break;
		case eSemi:
			fprintf(fp, ";");
			break;
		}
	}
}

void compile_StmtList(struct Stmt *stmlist)
{
	if (stmlist == NULL)
		return;
	else
	{
		if (stmlist->prev)
		{
			compile_Stmt(stmlist->prev);
			fprintf(fp, "\n");
		}
		compile_Stmt(stmlist);
	}
}

void compile_ExprStmt(struct ExprStmt *eps)
{
	if (eps == NULL)
		return;
	else
	{
		compile_Expr(eps->expr);
		fprintf(fp, ";");
	}
}

void compile_AssignStmt(struct AssignStmt *ass)
{
	if (ass == NULL)
		return;
	else
	{
		compile_RefVarExpr(ass->refVarExpr);
		fprintf(fp, " = ");
		compile_Expr(ass->expr);
	}
}

void compile_RetStmt(struct RetStmt *rts)
{
	if (rts == NULL)
		return;
	else
	{
		fprintf(fp, "return");
		if (rts->expr)
		{
			fprintf(fp, " ");
			compile_Expr(rts->expr);
		}
		fprintf(fp, ";");
	}
}

void compile_WhileStmt(struct WhileStmt *whs)
{
	if (whs == NULL)
		return;
	else
	{
		fprintf(fp, "while (");
		compile_Expr(whs->cond);
		fprintf(fp, ") ");
		compile_Stmt(whs->body);
	}
}

void compile_DoStmt(struct DoStmt *dos)
{
	if (dos == NULL)
		return;
	else
	{
		fprintf(fp, "do ");
		compile_Stmt(dos->body);
		fprintf(fp, " while (");
		compile_Expr(dos->cond);
		fprintf(fp, ");");
	}
}

void compile_ForStmt(struct FoRStmt *frs)
{
	if (frs == NULL)
		return;
	else
	{
		fprintf(fp, "for (");
		compile_Expr(frs->init);
		fprintf(fp, "; ");
		compile_Expr(frs->cond);
		fprintf(fp, "; ");
		compile_Expr(frs->body);
		fprintf(fp, ") ");
		compile_Stmt(frs->body);
	}
}

void compile_IfStmt(struct IfStmt *ifs)
{
	if (ifs == NULL)
		return;
	else
	{
		fprintf(fp, "if (");
		compile_Expr(ifs->cond);
		fprintf(fp, ") ");
		compile_Stmt(ifs->ifBody);
		if (ifs->elseBody)
		{
			fprintf(fp, " else ");
			compile->Stmt(ifs->elseBody);
		}
	}
}

void compile_Expr(struct Expr *exp)
{
	if (exp == NULL)
		return;
	else
	{
		switch (exp->e)
		{
		case eOper:
			compile_OperExpr(exp->type.operExpr);
			break;
		case eRef:
			compile_RefExpr(exp->type.refExpr);
			break;
		case eIntnum:
			fprintf(fp, exp->type.intnum);
			break;
		case eFloatnum:
			fprintf(fp, exp->type.floatnum);
			break;
		}
	}
}

void compile_OperExpr(struct OperExpr *ope)
{
	if (ope == NULL)
		return;
	else
	{
		switch (ope->e)
		{
		case eUn:
			if (ope->type.un->e == eNegative)
				fprintf(fp, "-");
			compile_Expr(ope->type.un->expr);
			break;
		case eAddi:
			compile_Expr(ope->type.addi->lhs);
			if (ope->type.addi->e == ePlus)
				fprintf(fp, " + ");
			else
				fprintf(fp, " - ");
			compile_Expr(ope->type.addi->rhs);
			break;
		case eMult:
			compile_Expr(ope->type.mult->lhs);
			if (ope->type.mult->e == eMul)
				fprintf(fp, " * ");
			else
				fprintf(fp, " / ");
			compile_Expr(ope->type.mult->rhs);
			break;
		case eRela:
			compile_Expr(ope->type.rela->lhs);
			if (ope->type.rela->e == eLT)
				fprintf(fp, " < ");
			else if (ope->type.rela->e == eGT)
				fprintf(fp, " > ");
			else if (ope->type.rela->e == eLE)
				fprintf(fp, " <= ");
			else
				fprintf(fp, " >= ");
			compile_Expr(ope->type.rela->rhs);
			break;
		case eEqlt:
			compile_Expr(ope->type.eqlt->lhs);
			if (ope->type.eqlt->e == eEQ)
				fprintf(fp, " == ");
			else
				fprintf(fp, " != ");
			compile_Expr(ope->type.eqlt->rhs);
			break;
		case eBracket:
			fprintf(fp, "(");
			compile_Expr(ope->type.bracket)
			fprintf(fp, ")");
			break;
		}
	}
}

void compile_RefExpr(struct RefExpr *rep)
{
	if (rep == NULL)
		return;
	else
	{
		switch (rep->e)
		{
		case eVar:
			compile_RefVarExpr(rep->type.refVarExpr);
			break;
		case eCall:
			compile_RefCallExpr(rep->type.refCallExpr);
			break;
		}
	}
}

void compile_RefVarExpr(struct RefVarExpr *rve)
{
	if (rve == NULL)
		return;
	else
	{
		if (!rve->refExpr)
		{
			compile_IdentExpr(rve->identExpr);
		}
		else
		{
			compile_RefExpr(rve->refExpr);
			fprintf(fp, ".");
			compile_IdentExpr(rve->identExpr);
		}
	}
}

void compile_RefCallExpr(struct RefCallExpr *rce)
{
	if (rce == NULL)
		return;
	else
	{
		if (!rce->refExpr)
		{
			compile_CallExpr(rce->callExpr);
		}
		else
		{
			compile_RefExpr(rce->refExpr);
			fprintf(fp, ".");
			compile_CallExpr(rce->callExpr);
		}
	}
}

void compile_IdentExpr(struct IdentExpr *ide)
{
	if (ide == NULL)
		return;
	else
	{
		fprintf(fp, ide->id);
		if (ide->expr)
		{
			fprintf(fp, "[");
			compile_Expr(ide->expr);
			fprintf(fp, "]");
		}
	}
}

void compile_CallExpr(struct CallExpr *calle)
{
	if (calle == NULL)
		return;
	else
	{
		fprintf(fp, calle->id);
		fprinf(fp, "(");
		if (calle->arg)
			compile_ArgList(calle->arg);
		fprinf(fp, ")");
	}
}

void compile_Arg(struct Arg *arg)
{
	if (arg == NULL)
		return;
	else
	{
		if (arg->prev)
		{
			compile_Arg(arg->prev);
			fprintf(fp, ", ");
		}
		compile_Expr(arg->expr);
	}
}