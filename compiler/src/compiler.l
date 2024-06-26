%{
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include<cstring>
#include "../include/compiler.hh"
#include "../include/compiler.h"
#include<iostream>
void yyerror(char *);
char c;
%}

%option noyywrap
digit	[0-9]
letter	[a-zA-Z]

%%
AND {return LOGICAL_AND;}
OR {return LOGICAL_OR;}
NOT {return LOGICAL_NOT;}
decl {
    return  DECL;
	}
enddecl {
    return ENDDECL;
  }
integer {
    return T_INT;
  }
print {
    return WRITE;
  }
if				{
    return IF; 
				}
then				{
    return THEN;
					}	
else				{
    return ELSE;
					}	
endif				{
    return ENDIF;
				}
for 				{
  return FOR;
				}		
while 				{
  return WHILE;
				}		
break 				{
  return BREAK;
        }
begin {
  return BEG;
}

return {
  return RETURN;
}

end {
  return END;
}


{digit}+  { 	
//             yylval.val = atoi(yytext);
            yylval.Node->value = atoi(yytext);
            return NUM;
				  }

{letter}({letter}|{digit})*	{ 	
    yylval.Node = (node*)malloc(sizeof(node)); 
    yylval.Node -> name = strdup(yytext);
    return VAR;
  }
"==" {return EQUALEQUAL;}
"<=" {return LESSTHANOREQUAL;}
">=" {return GREATERTHANOREQUAL;}
"!=" {return NOTEQUAL;}
"++"  { return T_PLUS_PLUS; }
[-+*/=()><;,\{\}\[\]\%] { return *yytext; }
["]                             { }
"\\n"                           {
                                }
\n

[ \t]				
.				{
				}		

%%
