SPACE [ \t]*

DEF "source"|"include"|"object"|"bin"|"name"|"Source"|"Include"|"Object"|"Bin"|"Name"|"Extensions"|"extensions"

ID [_a-zA-Z0-9\/\.$]+

CMD $\{[ _a-zA-Z\|\"\-$\+\.\(\)\/]+\}

%%

{SPACE}{DEF}{SPACE}={SPACE}{ID}{SPACE}     printf("%s", yytext);
{SPACE}{DEF}{SPACE}={SPACE}{CMD}{SPACE}    printf("%s", yytext);
{SPACE}{DEF}{SPACE}=[ \t]*                 printf("%s $void", yytext);

{SPACE}{ID}{SPACE}=  {
	fprintf(stderr, "\033[1;31merror\033[0m: Unrecognized definition.\n\t%s\n",
		yytext);
	exit (EXIT_FAILURE);
}

[.*]\n     printf("%s", yytext);

%%
