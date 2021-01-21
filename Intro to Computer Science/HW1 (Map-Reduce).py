#
#  Matthew Vaysfeld
#
#  CS115-B/C HW1 ~ Applications of Map & Reduce
#
#  Due : Sep. 20th, 2019
#
#  Pledge : I pledege my honor that I have abided by the Stevens Honor System
#

from functools import reduce
from math import factorial, sqrt

def taylorApproxE(lastIter):
    '''this function computes an approximation of e using the taylor series'''
    def oneoverFact(r):
        return 1/(factorial(r))
    def add(lastIter,r):
        return r+lastIter
    return reduce(add,list(map(oneoverFact,list(range(lastIter+1)))))

def vectorNorm(vect1):
    '''this function computes the magnitude of a list by adding the squares of each value of a list and the taking the square root of the sum'''
    def square(x):
        return (x**2)
    def add(x,y):
        return x+y
    return sqrt(reduce(add,(list(map(square, vect1)))))
    
def arithMean(vect1):
    '''this function computes the mean of a list by taking the sum and dividing it by the length of the list'''
    def add(x,y):
        return x+y
    meanlen=len(vect1)
    return (reduce(add,vect1))/meanlen



