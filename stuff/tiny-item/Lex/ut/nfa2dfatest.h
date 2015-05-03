void nfa2dfatest()
{
	struct tok_re tr = get_userdef("lang.l");
	char *p = fmt_re((char *)tr.re->value);
	struct nfa *nfa = re2nfa(p, 2);
	//struct set *s = newset(MAX_SETSIZE);
	struct dfa *dfa;
	//addset(s, nfa->start);
	//printf("%s\n", (char *)tr.re->value);
	//printf("nr: %d\n", nfa->blackbox->node_nr);
	//pfmt_string(p);
	//graphdump(nfa->blackbox, pgnode, pedge);
	//pgnode(nfa->start);
	//pfmt_string(p);
	//printf("%p %p\n", Char(EMPTY), Char(EMPTY));
	dfa = nfa2dfa(nfa);
	//pdfa(dfa);
	//s = closure(s);
	//setdump(s, pgnode);
	//s = dfa_edge(s, 'a');
	//setdump(s, pgnode);
}