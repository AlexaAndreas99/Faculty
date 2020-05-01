%remove (L1:list,L2:list,%A
%occ(L:list,E:element,V:int)
%flow model(i,i,o)
occ([],_,0).
occ([H|T],E,R):-H=E, occ(T,E,R1), R is R1+1.
occ([H|T],E,R):-H\=E, occ(T,E,R).
%remove2 (L1:list,L2:list)
%flow (i,o)
remove2([],[]).
remove2([H|T],[H|T1]):-occ(T,H,R),R==0,remove2(T,T1).
remove2([H|T],L2):-occ(T,H,R),R>0,remove2(T,L2).

%B
%gcd(A:elem,B:elem,C:elem)
%flow(i,i,o)
gcd1(A,0,A).
gcd1(A,B,C):-B>A,gcd1(B,A,C).
gcd1(A,B,C):-A>=B,A1 is A mod B,gcd1(B,A1,C).

%gcdL(L1:list,Z:elem)
%flow(i,o)
gcdL([H],H).
gcdL([H,H1|T],Z):-gcd1(H,H1,X),gcdL([X|T],Z).
gcdL([H1,H2],Z):-gcd1(H1,H2,Z).











