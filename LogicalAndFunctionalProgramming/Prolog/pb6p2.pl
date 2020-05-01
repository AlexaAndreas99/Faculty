%a. Determine the product of a number represented as digits in a list to
% a given digit. Eg.: [1 9 3 5 9 9] * 2 => [3 8 7 1 9 8]
% multiply(L1:List,N:number,Result:List)
% flow(i,i,o)
multiply(L1,N,Result):-reverse(L1,Res),multiply(Res,N,0,T),reverse(T,Result).

multiply([],_,C,[]):-C=<0.
multiply([],_,C,[C]):-C>0,C<10.
multiply([],_,C,[R|Rs]):-C>=10,R is C rem 10,Q is C div 10,multiply([],_,Q,Rs).
multiply([D|Ds],N,C,[R|Rs]):-T is D*N+C, R is T rem 10, Q is T div 10, multiply(Ds,N,Q,Rs).

%B
%replace1(L1:list,K:number,L2:list)
%flow(i,i,o)
replace1([],_,[]).
replace1([H|T],K,[R|T1]):-is_list(H),multiply(H,K,R),K1 is K+1,replace1(T,K1,T1),!.
replace1([H|T],K,[H|T1]):-replace1(T,K,T1).
replace1M(L1,R):-replace1(L1,1,R).

%B
%maxofTwo(X:elem,Y:elem,Z:elem)
%flow(i,i,o)
%maxOfTwo(X, Y, X) :-X >= Y.
%maxOfTwo(X, Y, Y) :-X < Y.
%maxL(L1:list,E:elem)
%flow(i,o)
%maxL([H], H).
%maxL([H | T], X) :-maxL(T, I),maxOfTwo(H, I, X).

%maxpos(L1:List,L2:List,K:elem,Res:List)
%flow(i,i,i,o)
%maxpos1([],_,_,[]).
% maxpos1([H|T],L2,K,[K|T1]):-maxL(L2,X),H==X,K1 is
% K+1,maxpos1(T,L2,K1,T1).
%maxpos1([H|T],L2,K,L3):-K1 is K+1,maxpos1(T,L2,K1,L3).
%maxposM(L1,X):-maxpos1(L1,L1,0,X).










