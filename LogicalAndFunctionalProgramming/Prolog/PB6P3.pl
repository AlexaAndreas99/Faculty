aux([H|_],1,[H]).

aux([_|L],N,L1):-
    aux(L,N,L1).

aux(L,N,[H|T]):-
    N>1,
    select(H,L,M),
    N1 is N-1,
    aux(M,N1,T).

aux(L,1,[X]):-
    member(X,L).

arran(L,N,R):-
    findall(X,aux(L,N,X),R).
