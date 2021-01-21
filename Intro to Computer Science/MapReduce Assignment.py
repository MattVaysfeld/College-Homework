#I pledge my honor that I have abided by the Stevens Honor System- Matthew Vaysfeld
from functools import reduce
lst=['yes','no','maybe']
def f(txt):
    return [len(txt),txt]
def b(lst):
          return(list(map(f,lst)))
def c(lst):
    newlst = b(lst)
    return(reduce(max,newlst)[1])

print(c(lst))
