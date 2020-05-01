%uni(l1,l1,l3)
%flow(i,i,o)
uni([],[],[]).
uni([H|T],L,[H|T1]):-uni(T,L,T1),!.
uni(L,[H|T],[H|T1]):-uni(L,T,T1).

%aux(e,l,l)
%flow(i,i,o)
aux(_,[],[]).
aux(E,[H|T],[[E,H]|T1]):-aux(E,T,T1).

%main(l,l)
%(i,o)
main([],[]).
main([H|T],[X|T1]):-aux(H,T,X),main(T,T1).

%3
%rem(
