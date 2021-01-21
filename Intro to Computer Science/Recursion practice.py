#I pledege my honor that I have abided by the Stevens Honor System
#Matthew Vaysfeld

def dotProduct(L,K):

    '''the function outputs the dot product of both lists'''

    if L==[] or K==[]:
        return 0.0
    else: 
        return L[0]*K[0] + dotProduct(L[1:],K[1:])
   
def expand(S):

    '''outputs each element in the string as its own string'''

    if S==(""):
        return []
    else:
        return list(S[0])+expand(S[1:])

def deepMember(e,M):

    '''outputs true if the element e is in the list M, and false if it is not. It also checks sublists.'''

    if M==[]:
        return False
    else:
        if M[0]==e:
            return True
        else:
            if isinstance(M[0],list):
                return deepMember(e,M[0]) or deepMember(e,M[1:])
            else:
                return deepMember(e,M[1:])
            
            
def removeAll(e,M):

    '''removes all instances of e in the list M (e can be a list also)'''

    if M==[]:
        return []
    else:
        if not M[0]==e:
                return [M[0]]+(removeAll(e,M[1:]))
        if M[0]==e:
            return (removeAll(e,M[1:]))
        else:
                return removeAll(e,M[1:])

def deepReverse(L):

    '''takes the input of list L and reverses the order of the elements of the List (elements can be lists too)'''

    if L==[]:
        return []
    elif isinstance(L[0],list):
            return deepReverse(L[1:])+[deepReverse(L[0])]
    else:
        return deepReverse(L[1:]) + [L[0]]

    

    
