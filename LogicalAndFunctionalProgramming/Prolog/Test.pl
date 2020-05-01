%min(X:INT,Y:INT,Z:INT)
%(i,i,o)
min(X,Y,X):-X=<Y.
min(X,Y,Y):-Y<X.

%minL(L:LIST,X:INT)
%(i,o)
minL([H],H).
minL([H | T], X) :-minL(T, I),min(H, I, X).

%mainM(L:LIST,L2:LIST,R:LIST)
%(i,i,o)

mainM(L,L2,R):-minL(L,X),mainA(L,L2,R,X).

%mainA(L:LIST,L2:LIST,R:LIST,X:INT).
%(i,i,o,i)
mainA([],_,[],_).
mainA([H|T],L2,[L2|T1],X):-H==X,mainA(T,L2,T1,X).
mainA([H|T],L2,[H|T1],X):-H\=X,mainA(T,L2,T1,X).
