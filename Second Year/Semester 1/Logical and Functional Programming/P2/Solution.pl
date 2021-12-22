% 5.a. Substitute all occurrences of an element of a list with all the elements of another list. 
% Eg. subst([1,2,1,3,1,4],1,[10,11],X) produces X=[10,11,2,10,11,3,10,11,4].

% concat(List: list, InitialList: list, Result: list)
% flow model: (i, o), (i, i), (o, i)
% List - list with the elements that have to be concatenated
% InitialList - the list with which we have to concatenate the new elements
% Result - the concatenation of the two lists
concat([], E, E).
concat([H|T], E, [H|T2]) :-
    concat(T, E, T2).

% subst(List: list, Element: int, ReplacementList: list, Result: list)
% flow model: (i, i, i, o), (i, i, i, i), (i, i, o, i)
% List - the initial list
% Element - the element to be replaced
% ReplacementList - the list that will replace the element
% Result - the final list
subst([], _, _, []).
subst([H|T], Elem, RList, Res) :-
    H =:= Elem,
    subst(T, Elem, RList, Temp),
    concat(RList, Temp, Res).
subst([H|T], Elem, RList, [H|T2]) :-
    H =\= Elem,
    subst(T, Elem, RList, T2).

b. For a heterogeneous list, formed from integer numbers and list of numbers, replace in every sublist all 
occurrences of the first element from sublist with a new given list.
Eg.: [1, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] si [11, 11] =>
[1, [11, 11, 1, 11, 11], 3, 6, [11, 11, 10, 1, 3, 9], 5, [11 11 11 11 11 11], 7]

% concat(List: list, InitialList: list, Result: list)
% flow model: (i, o), (i, i), (o, i)
% List - list with the elements that have to be concatenated
% InitialList - the list with which we have to concatenate the new elements
% Result - the concatenation of the two lists
concat([], E, E).
concat([H|T], E, [H|T2]) :-
    concat(T, E, T2).

% subst(List: list, Element: int, ReplacementList: list, Result: list)
% flow model: (i, i, i, o), (i, i, i, i), (i, i, o, i)
% List - the initial list
% Element - the element to be replaced
% ReplacementList - the list that will replace the element
% Result - the final list
subst([], _, _, []).
subst([H|T], Elem, RList, Res) :-
    H =:= Elem,
    subst(T, Elem, RList, Temp),
    concat(RList, Temp, Res).
subst([H|T], Elem, RList, [H|T2]) :-
    H =\= Elem,
    subst(T, Elem, RList, T2).

% replaceFirstElementInSublist(List: list, ReplacementList: list, Result: list)
% flow model: (i, i, o), (i, i, i), (i, o, i)
% List - initial list
% ReplacementList - the list that will replace all occurences the first element from the sublists
% Result - final list
replaceFirstElementInSublist([], _, []).
replaceFirstElementInSublist([H|T], RList, [Res1|Res2]) :-
    is_list(H),
    H = [F|_],
    subst(H, F, RList, Res1),
    replaceFirstElementInSublist(T, RList, Res2).
replaceFirstElementInSublist([H|T], RList, [H|Res]) :-
    replaceFirstElementInSublist(T, RList, Res).