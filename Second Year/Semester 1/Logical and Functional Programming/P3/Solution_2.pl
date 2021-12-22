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
%E1 - the value of the element on the next position
candidate(E1, E) :-
	contains(E, [-1, 0, 1]),
	contains(E1, [-1, 0, 1]),
	E =\= E1.

%generate(N: int, L: list)
%flow model: (i, o), (i, i)
%N - length
%L - resulted list
generate(1, [0]) :- !.
generate(Length, [E|T]) :-
    	NewLength is Length - 1,
	generate(NewLength, T),
    	T = [E1|_],
	candidate(E1, E).

allSolutions(N, SL) :-
   	Length is 2*N + 1,
	findall(S, generate(Length, S), SL).