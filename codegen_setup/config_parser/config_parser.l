%{
	/**
	* This lex file is used to parse the options of codegen_config.txt.
	* The grammar and all the important work linked to the token 
	* recognition defined here, is in config_parser.y
	*/

	#include "y.tab.h"
%}

SPACE [ \t]*

CMD $\{[ _a-zA-Z\|\"\-$\+\.\)\(\/]+\}

%%

[ \t\r\n]*   ;

"source"{SPACE}"="|"Source"{SPACE}"="   return SOURCE;

"include"{SPACE}"="|"Include"{SPACE}"=" return INCLUDE;

"object"{SPACE}"="|"Object"{SPACE}"="   return OBJECT;

"bin"{SPACE}"="|"Bin"{SPACE}"="         return BIN;

"name"{SPACE}"="|"Name"{SPACE}"="       return NAME;

"extensions"{SPACE}"="|"Extensions"{SPACE}"=" return EXTENSIONS;

{CMD}                { strcpy(yylval.str, yytext); return CMD; }

[_a-zA-Z0-9\/\.$]*   { strcpy(yylval.str, yytext); return ID;  }

. { fprintf(stderr, "error: unrecognized token \'%s\'\n", yytext); exit(1);}

%%
