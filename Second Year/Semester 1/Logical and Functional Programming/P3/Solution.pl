%contains(E: int, L: list)
%flow model: (i, i), (o, i)
%E - the element to be checked if it is in the list
%L - the list
contains(E, [E|_]).
contains(E, [_|T]) :-
	contains(E, T).

%candidate(E1: int, E: int)
%flow model: (o, i), (i, i), (i, o)
%E - possible candidate value
%L - value from the next position
candidate(E1, E) :-
	contains(E, [-1, 0, 1]),
	contains(E1, [-1, 0, 1]),
	E =\= E1.

%generate(N: int, Pos:int, L: list)
%flow model: (i, i, o), (i, i, i)
%N - given number
%Pos - current position in the list
%L - resulted list
generate(N, Pos, [0]) :-
	Finish is 2 * N + 1,
	Pos =:= Finish,
	!.
generate(N, Pos, [E|T]) :-
	NewPos is Pos + 1,
	generate(N, NewPos, T),
    	T = [E1|_],
	candidate(E1, E).

allSolutions(N, SL) :-
	findall(S, generate(N,1,S), SL).