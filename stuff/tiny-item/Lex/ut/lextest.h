extern FILE *fp;
extern char *err_string;
extern struct dfa *dfa_machine;

void lextest()
{/*
	struct nfa *nfa, nfa1, nfa2, nfa3;
	struct dfa *dfa;
	struct tok_re ll;
	char *fmt;
	int i = 1, ret = 0;
	lex_automaton("lang.l");
	lexin("fmt.l");
	while (1) {
		ret = lex();
		if (ret == UNMATCHED) goto unm;
		if (ret == FILEEND) goto end;
		plexu();
		printf("# str len:%d\n", ret);
	}
unm:printf("`%s`: error\n", err_string);
end:fclose(fp);
	*/
}