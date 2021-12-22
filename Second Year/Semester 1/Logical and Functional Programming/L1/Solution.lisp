; a) Write a function to eliminate the n-th element of a linear list.
(defun removeElementFromPos (l n)
    (cond
        ((null l) nil)
        ((= n 1) (cdr l))
        (T (cons (car l) (removeElementFromPos (cdr l) (- n 1))))
    )    
)

(print (removeElementFromPos '(1 2 3 4 5 6 7 8) 5))

;b) Write a function to determine the successor of a number represented digit by digit as a list, without transforming the representation of the number from list to number. 
;Example: (1 9 3 5 9 9) --> (1 9 3 6 0 0)

(defun reversed(l tail)
    (cond
        ((null l) tail)
        (T (reversed (cdr l) (cons (car l) tail)))
    )
)

(defun reverseElements(l)
    (reversed l nil)
)

(defun successorNb(l)
    (cond
        ((and (equal 9 (car l)) (not (equal nil (cdr l)))) (cons 0 (successorNb (cdr l))))     
        ((equal 9 (car l)) (cons 0 (cons 1 nil)))
        (t (cons (+ 1 (car l)) (cdr l)))
    )
)

(defun successor(l)
   (reverseElements (successorNb (reverseElements l))) 
)


(print (successor '(1 9 3 5 9 9)))
(print (successor'(9 9)))


;c) Write a function to return the set of all the atoms of a list.
;Example: (1 (2 (1 3 (2 4) 3) 1) (1 4)) --> (1 2 3 4)


(defun contains (l elem)
    (cond
        ((null l) nil)
        ((= (car l) elem) T)
        (T (contains (cdr l) elem))
    )
)

(defun contains (l elem)
    (cond
        ((null l) nil)
        ((equal (car l) elem) T)
        (T (contains (cdr l) elem))
    )
)

(defun concat(l1 l2)
    (cond
        ((null l1) l2)
        (T (cons (car l1) (concat (cdr l1) l2)))
    )
)

(defun createLinearList(l)
    (cond
        ((null l) nil)
        ((atom (car l)) (cons (car l) (createLinearList (cdr l))))
        ((listp (car l)) (concat (createLinearList (car l)) (createLinearList (cdr l))))
    )
)

(defun reversed(l tail)
    (cond
        ((null l) tail)
        (T (reversed (cdr l) (cons (car l) tail)))
    )
)

(defun reverseElements(l)
    (reversed l nil)
)

(defun setOfAtoms(l tail)
    (cond
        ((null l) tail)
        ((contains tail (car l)) (setOfAtoms (cdr l) tail))
        (T (setOfAtoms (cdr l) (cons (car l) tail)))
    )
)

(defun createSet(l)
    (setOfAtoms l nil)
)

(defun solve(l)
    (reverseElements (createSet (createLinearList l)))
)

(print (solve '(1 (2 (1 3 (2 4) 3) 1) (1 4))))
(print (solve '(1 "a" (2 "ab" (1 3 (2 4 A) 3) 1 A) (1 4))))


; d) Write a function to test whether a linear list is a set.
(defun contains (l elem)
    (cond
        ((null l) nil)
        ((= (car l) elem) T)
        (T (contains (cdr l) elem))
    )
)

(defun checkIfSet(l)
    (cond
        ((null l) T)
        ((contains (cdr l) (car l)) nil)
        (T (checkIfSet (cdr l)))
    )
)

(print (checkIfSet '(1 2 2 3 4)))
(print (checkIfSet '(1 2 3 4)))