; reversed(l1, l2, ..., ln, tail) = {
;	tail, if n = 0
;	reversed(l2, ..., ln, l1 ∪ tail), otherwise
;}
(defun reversed(l tail)
    (cond
        ((null l) tail)
        (T (reversed (cdr l) (cons (car l) tail)))
    )

)

; reverseElements(l1, l2, ..., ln) = reversed(l1, l2, ..., ln, nil)
(defun reverseElements(l)
    (reversed l nil)
)

; contains(l1, l2, ..., ln, e) = {
;	false, if n = 0
;	true, if l1 = e
;	contains(l2, ..., ln, e), otherwise
;}
(defun contains (l elem)
    (cond
        ((null l) nil)
        ((equal (car l) elem) T)
        (T (contains (cdr l) elem))
    )
)

; return the sublist that begins with the node for which we need to find the level
; getSubtree(e, l1, l2, ..., ln) = {
;	(l1, l2, ..., ln), if l1 = e
;	getSubtree(e, l2, ..., ln), otherwise
;}
(defun getSubtree(e l)
    (cond 
        ((equal (car l) e) l)
        (t (getSubtree e (cdr l)))
    )
)

; we remove from the list all the elements until we find the parent of the node for which we need to return the level 
; the sum of the numbers that represent the number of subtrees needs to be at least equal to the number of nodes 
; between parent and child(included)

;tree =(child, no_subtrees_of_previous_node, possible_parent)
;getParentSubtree(tree, nrSubtrees, nrNodes) = {
;	nil, if tree contains only the child
;	(possible_parent), if no_subtrees_of_previous_node + nrSubtrees >= nrNodes + 1
;	getParentSubtree(possible_parent, no_subtrees_of_previous_node + nrSubtrees, nrNodes + 1), otherwise
;}
(defun getParentSubtree(l nrSubtrees nrNodes)
   (cond
        ((equal (cdr l) nil) nil)
        ((>= (+ (car (cdr l)) nrSubtrees) (+ 1 nrNodes)) (cdr (cdr l)))
        (t (getParentSubtree (cdr (cdr l)) (+ (car (cdr l)) nrSubtrees) (+ 1 nrNodes)))        
   )
)

;getParentSubtreeWrapper(tree) = getParentSubtree(tree, 0, 0)
(defun getParentSubtreeWrapper(l)
    (getParentSubtree l 0 0)
)

; the level of the node is the level of the parent + 1
; level(e, l1, ..., ln) = {
;	-1, if e is not in the list
;	level(parent, getParentSubtree(getSubtree(e, l1, ..., ln)) + 1, 
;			where parent is the first element of getParentSubtree(getSubtree(e, l1, ..., ln)
;}
(defun level(e l)
   (cond
        ((not (contains l e)) '-1)
        (t (+ 1 (level (car (getParentSubtreeWrapper (getSubtree e l))) (getParentSubtreeWrapper (getSubtree e l)))))
    )
)

; levelOfNode(e, l1, ..., ln) = level(e, reverseElements(l1, ..., ln))
(defun levelOfNode(e l)
   (level e (reverseElements l))
)

(print(levelOfNode 'E '(A 2 B 0 C 2 D 0 E 0)))
(print(levelOfNode 'G '(A 2 B 2 C 1 I 0 F 1 G 0 D 2 E 0 H 0)))