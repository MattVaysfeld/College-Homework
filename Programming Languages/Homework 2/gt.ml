(* 

   Stub for HW2 
   Please
   1. Rename to gt.ml
   2. Place the names of the group members here:

    Name1: Matthew Vaysfeld
    Name2: Lukasz Asztemborski
	
	I pledge my honor that I have abided by the Stevens Honor System.

*)



type 'a gt = Node of 'a*('a gt) list

let mk_leaf (n:'a) : 'a gt =
  Node(n,[])
    
let t : int gt =
 Node (33,
       [Node (12,[]);
        Node (77, 
              [Node (37, 
                     [Node (14, [])]); 
               Node (48, []); 
               Node (103, [])])
       ])
	   
(*Test Trees*)
let t2 : int gt =
 Node (33,
       [Node (12,[]);
        Node (77, 
              [Node (37, 
                     [Node (14, [
					 Node(11, [])])]); 
               Node (48, []); 
               Node (103, [])])
       ])

let root_tree : int gt =
	Node (33, [])
	
let perf_tree : int gt =
	Node (33, 
		  [Node(7,[]); Node(9,[])]
	)
	
let hang_tree : int gt = 
	Node (33,
		[Node(7,[])]
		)
let comp_tree : int gt =
	Node(15,
[
Node(20,[
Node(1, [
Node(19,[]);
Node(14,[])
]);
Node(2, [
Node(12,[])
]);
Node(3, [Node(13,[])]);
Node(4, [Node(17,[])])
]);Node(30,[
Node(7,[
Node(21,[])
]);
Node(8, [Node(22,[])])
])

])

(* Height *)

let max_l l =
	match l with
    | [] -> failwith "empty"
	| h::t -> List.fold_left max h t
	
  
let rec height t =
	match t with
	| Node(v, []) -> 1
	| Node(v, x) -> 1 + max_l (List.map height x)
 
(*Size*)
  
let rec sum l =
	match l with
	| [] -> 0
	| h::t -> h + sum t
  
let rec size t =
	match t with
	| Node(v, []) -> 1
	| Node(v, x) -> 1 + sum (List.map size x)
	
(*Paths to leaves*)

let rec paths_to_leaves t =
   match t with
   | Node(v, []) -> [[]]
   | Node(v, x) ->
	List.flatten (List.mapi (fun i n -> (List.map (fun l -> i::l) (paths_to_leaves n))) x)
	
(*Is_perfect
Based off Code in class*)

let rec perfect' l =
	match l with
	| [] | [_] -> true
	| n::m::t -> n=m && perfect' (m::t)
	
let is_perfect t =
	perfect' (List.map List.length (paths_to_leaves t))
	
(*Preorder*)

let rec preorder (Node(d,ch)) =
	match ch with
	| [] -> [d]
	| _ -> [d] @ (List.flatten (List.map preorder ch))

(*Mirror*)
let rec mirror (Node(d,ch)) =
	match ch with 
	| [] -> mk_leaf d
	| _ -> Node(d, (List.map mirror (List.rev ch)))
	

(*Map*)
let rec mapt f (Node(d,ch)) =
	match ch with 
	| [] -> Node(f d, [])
	| _ -> Node(f d, (List.map (mapt f) ch))
 
(*Fold*)
let rec foldt : ('a -> 'b list -> 'b) -> 'a gt -> 'b =
fun f (Node(d,ch)) ->
  match ch with
  | [] -> (f d [])
  | _ -> f d (List.map (foldt f) ch)

let sumt t =
  foldt (fun i rs -> i + List.fold_left (fun i j -> i+j) 0 rs) t

let memt t e = 
  foldt (fun i rs -> i=e || List.exists (fun i -> i) rs) t

(*Mirror using Fold*)
let mirror' t  = 
  foldt (fun i rs -> Node(i, List.rev rs)) t
