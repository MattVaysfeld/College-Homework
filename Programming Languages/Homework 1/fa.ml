
(* ******************************************** *)
(** Basic functions on finite automata *)
(* ******************************************** *)
(**
   Matthew Vaysfeld
   I pledge my honor that I have abided by the Stevens Honor System.
*)

type symbol = char
type input = char list

type state = string

(* transition function *)
type tf = (state * symbol * state) list

(* initial state * transition function * end state *)
type fa = { states: state list; start:state; tf: tf; final: state list}


(* ******************************************** *)
(* Examples of automata *)
(* ******************************************** *)

let a = {states = ["q0";"q1";"q2"];
         start = "q0";
         tf = [("q0",'a',"q1"); ("q1",'b',"q1"); ("q1",'c',"q2")];
         final = ["q2"]}

let a2 = {states = ["q0";"q1";"q2";"q3";"q4"];
          start = "q0";
          tf = [("q0",'a',"q1"); ("q1",'b',"q1")
               ; ("q1",'c',"q2");  ("q3",'a',"q4")];
          final= ["q2"]
         }
let tf_of_a = [("q0",'a',"q1"); ("q1",'b',"q1"); ("q1",'c',"q2")]


let b = {states = ["q0";"q1";"q2";"q3"];
         start = "q0";
         tf = [("q0",'a',"q1"); ("q0",'a',"q3"); ("q1",'b',"q1"); ("q1",'c',"q2")];
         final = ["q2";"q3"]}
		 
let tf_of_b = [("q0",'a',"q1"); ("q0",'a',"q3"); ("q1",'b',"q1"); ("q1",'c',"q2")]


let c = {states = ["q0";"q1";"q2";"q3";"q4";"q5"];
         start = "q0";
         tf = [("q0",'a',"q1"); ("q0",'a',"q3"); ("q1",'b',"q1"); ("q1",'c',"q2");("q4",'a',"q5")];
         final = ["q2";"q3";"q4"]}
		 
let tf_of_c = [("q0",'a',"q1"); ("q0",'a',"q3"); ("q1",'b',"q1"); ("q1",'c',"q2");("q4",'a',"q5")]


let d = {states = ["q0";"q1";"q2"];
         start ="q0";
         tf = [("q0",'a',"q1"); ("q1",'a',"q2"); ("q2",'b',"q0");];
         final = ["q2"]}
		 
let e = {states = ["q0";"q1";"q2";"q4";"q3"];
         start ="q3";
         tf = [("q3",'a',"q2"); ("q3",'a',"q1"); ("q3",'c',"q4"); ("q4",'b',"q0")];
         final = ["q2";"q3"]}

(* ******************************************** *)
(* Helper functions *)
(* ******************************************** *)

let input_of_string s =
  let rec exp i l =
    if i < 0 then l else exp (i - 1) (s.[i] :: l) in
  exp (String.length s - 1) []


(* ******************************************** *)
(* Simulating automata *)
(* ******************************************** *)

(*Nice utility functions*)

let f1 (x,_,_) = x
let f2 (_,x,_) = x
let f3 (_,_,x) = x

let in_option i =
	match i with
	|Some i -> i

let rec alphabet tf=
	match tf with
	|[] -> []
	|h::t -> f2 h :: alphabet t
	
(*Homework answers*)	

(*Apply Transition*)
let rec apply_transition_function f st sy =
	match f with
	| [] -> None
	| h::t -> if ((f1 h = st) && (f2 h = sy)) then Some (f3 h) else apply_transition_function t st sy
	

(*Accept*)	
let rec accepth fa input st=
	match input with
	|[] -> (true,st)
	|h::t -> if (apply_transition_function fa.tf st h) = None then (false,"none") else (accepth fa t (in_option (apply_transition_function fa.tf st h)))
	
let accept fa input =
	(fst (accepth fa input fa.start)) && (List.mem (snd (accepth fa input fa.start)) fa.final)


(*Deterministic*)
let rec next f st sy=
	match f with
	| [] -> []
	| h::t -> if ((f1 h = st) && (f2 h = sy)) then f3 h :: next t st sy else next t st sy

let rec deterministich fa sy states=
	match states with
	|[] -> true
	|h::t -> if ((List.length (next fa.tf h sy)) > 1) then false else deterministich fa sy t
	
let rec deterministich2 fa alphabet=
	match alphabet with
	|[] -> true
	|h::t -> if deterministich fa h fa.states = false then false else deterministich2 fa t

let rec deterministic fa =
	deterministich2 fa (alphabet fa.tf)
	

(*Valid*)

let rec finalstatecheck a b =
	match a with
	|[] -> true
	|h::t -> if List.mem h b then finalstatecheck t b else false

let valid fa = 
	(List.mem fa.start fa.states) && (deterministic fa) && (finalstatecheck fa.final fa.states)
	
(*Reachable*)

let rec next_nosy f st=
	match f with
	| [] -> [] 
	| h::t -> if (f1 h = st) then f3 h :: next_nosy t st else next_nosy t st

let rec next_oflist fa lst=
	match lst with
	| [] ->[]
	| h::t -> (next_nosy fa.tf h) @ next_oflist fa t 

let rec remove_dups lst=
	match lst with
	|[] -> []
	|h::t -> if (List.mem h t) then remove_dups t else h :: remove_dups t
  
let rec reachableh fa sts st visited=
	match sts with
	|[] -> visited
	|h::t -> reachableh fa t h ((next_oflist fa visited)@visited)

let rec reachable fa =
	remove_dups (reachableh fa fa.states fa.start [fa.start])
	
(*Remove Dead States*)

let rec diff l1 l2=
	match l1 with
	|[] ->[]
	|h::t when List.mem h l2 -> diff t l2
	|h::t -> h:: diff t l2
	
let rec removestates sts rsts=
	match sts with
	|[] -> []
	|h::t -> if (List.mem h rsts) then h::(removestates t rsts) else removestates t rsts

let rec removetf f rsts=
	match f with
	|[] -> []
	|h::t -> if (List.mem (f1 h) rsts) && (List.mem (f3 h) rsts) then h::(removetf t rsts) else removetf t rsts

let rec remove_dead_states fa =
	{states = removestates fa.states (reachable fa);
	start = fa.start;
	tf = removetf fa.tf (reachable fa);
	final = removestates fa.final (reachable fa)
	}
	
