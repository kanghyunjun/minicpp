%{
#include <stdlib.h>
#include <string h>

#include "parser.tab.h"
%}

unop		[-]
addiop		[\+\-]
multop		[\*\/]
relaop		[\<\>\<=\>=]
eqltop		[\==\!=]
id		[A-Za-z_][A-Za-z0-9_]*
intnum		[0-9]+
floatnum	[0-9]+.[0-9]+

%%

'+'		{ return ADD; }
'-'		{ return SUB; }
'*'		{ return MUL; }
'/'		{ return DIV; }
'<'		{ return LT; }
'>'		{ return GT; }
'<='		{ return LE; }
'>='		{ return GE; }
'=='		{ return EQ; }
'!='		{ return NE; }

{unop}	{ yylval.op = yytext[0]; return UNOP; }
{addiop}	{ yylval.op = yytext[0]; return ADDIOP; }
{multop}	{ yylval.op = yytext[0]; return MULTOP; }
{relaop}	{ yylval.op = yytext[0]; return RELAOP; }
{eqltop}	{ yylval.op = yytext[0]; return EQLTOP; }
{id}		{ yylval.id = atoi(yytext); return ID; }
{intnum}	{ yylval.intnum = atoi(yytext); return INTNUM; }
{floatnum}	{ yylval.floatnum = atoi(yytext); return FLOATNUM; }

class		{ return CLASS; }
private		{ return PRIVATE; }
public		{ return PUBLIC: }

main		{ return MAIN; }
int		{ return INT; }
float		{ return FLOAT; }

if		{ return IF; }
else		{ return ELSE; }
for		{ return FOR; }
do		{ return DO; }
while		{ return WHILE; }
return		{ return RETURN; }

%%
