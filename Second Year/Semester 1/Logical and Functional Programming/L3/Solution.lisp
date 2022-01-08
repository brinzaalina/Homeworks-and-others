; countNodesOnLevel(tree, levelCounter) = {
;	1, if the root of the tree is an atom and levelCounter = 0
;	sum(countNodesOnLevel(ti, level - 1)), i=1,n, where tree = root t1 t2 ...tn (ti - subtree i of the root) and levelCounter != 0 
;}
(defun countNodesOnLevel(tree levelCounter)
    (cond
        ((and (atom (car tree)) (= levelCounter 0)) 1)
        (t (apply '+ (mapcar #'(lambda (a) (countNodesOnLevel a (- levelCounter 1))) (cdr tree))))
    )
)

(print(countNodesOnLevel '(A (B (C)) (D) (E (F))) 0))
(print(countNodesOnLevel '(A (B (C)) (D) (E (F))) 1))
(print(countNodesOnLevel '(A (B (C)) (D) (E (F))) 2))
(terpri)
(print(countNodesOnLevel '(A (B (D (G) (H)) (E (I))) (C (F (J (L)) (K)))) 0))
(print(countNodesOnLevel '(A (B (D (G) (H)) (E (I))) (C (F (J (L)) (K)))) 1))
(print(countNodesOnLevel '(A (B (D (G) (H)) (E (I))) (C (F (J (L)) (K)))) 2))
(print(countNodesOnLevel '(A (B (D (G) (H)) (E (I))) (C (F (J (L)) (K)))) 3))
(print(countNodesOnLevel '(A (B (D (G) (H)) (E (I))) (C (F (J (L)) (K)))) 4))
