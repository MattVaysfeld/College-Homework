#Name:Matthew Vaysfeld
#
#Date: 9/30
#
#CS115 - HW 2 ~ Recursion
#
#Pledge: I pledge my honor that I have abided by the Stevens Honor System


## Part 1 ~ Change

def makeChange(val, coins):
    '''takes the input of the value and coins and gives the number of the least amoount of coins to make the value and a list of them'''
    if coins==[] or val<0:
        return [float('inf'),[]]
    if val==0:
        return [0,[]]
    useIt= makeChange(val-coins[0],coins)
    useIt[0]+= 1
    useIt[1]+= [coins[0]]
    loseIt=makeChange(val,coins[1:])

    if useIt[0]<loseIt[0]:
        return useIt
    else:
        return loseIt

## Part 2 ~ Least Common Substrings

def LCS(a, b):
    '''takes the two strings and gives the longest common substring between them'''
    if not (a and b):
        return ''
    if a[0]==b[0]:
        return a[0]+LCS(a[1:],b[1:])
    else:
        useIt= LCS(a[0:],b[1:])
        loseIt= LCS(a[1:],b[0:])
    if len(useIt)<len(loseIt):
        return loseIt
    else:
        return useIt

def LLCS (a , b ):
    '''gives the length of the longest common substring'''
    if not ( a and b ):
        return 0
    if ( a[0]==b[0]):
        return 1 + LLCS ( a[1:], b[1:])
    return max( LLCS ( a[1:],b ) , LLCS (a , b[1:]) )



def PLCS(a, b):
    '''gives the indexes of both strings that match with longest common substring'''
    s=LCS(a,b)
    if s=='':
        return [[-1],[-1]]
    return [helper(a,s,0)]+[helper(b,s,0)]

def helper(s1,s2,counter):
    '''helper function for PCS, compares the string to the longest common substring'''
    if not ( s1 and s2 ):
        return []
    if (s1[0]!=s2[0]):
        return helper(s1[1:],s2,counter+1)
    else:
        useIt= [counter]+helper(s1[1:],s2[1:],counter+1)
        loseIt= helper(s1[1:],s2,counter+1)
        if len(useIt)== LLCS(s1,s2):
            return useIt
        else:
            return loseIt

        
    















