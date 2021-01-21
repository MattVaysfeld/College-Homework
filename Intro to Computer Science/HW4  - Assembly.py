#Matthew Vaysfeld
#I pledge my honor that I have abided by the Stevens Honor System


from importlib import reload as Rfrsh
import hmmm

# Fibonacci! You've already done it in Lab 9
# Now however, you are to do hmmmonacci with
# recursion, & you MUST do so for any credit
# The tests are still the same as from Lab 9
# Tests: f(2) = 1 ■■■ f(5) = 5 ■■■ f(9) = 34
RecFibSeq ="""
00 setn r15 42
01 read r1
02 setn r3 1
03 calln r14 6
04 write r13
05 halt
06 jnezn r1 9
07 setn r13 0
08 jumpr r14
09 pushr r1 r15
10 pushr r14 r15
11 addn r1 -1
12 calln r14 6
13 popr r14 r15
14 popr r1 r15
15 add r4 r13 r3
16 copy r13 r3
17 copy r3 r4
18 jumpr r14

"""

# Change doDebug to false to turn off debugs
runThis = RecFibSeq
doDebug = True

# Note: main() in the shell to easily reload
def main(runArg=runThis,  debugArg=doDebug):
    Rfrsh(hmmm); hmmm.main(runArg, debugArg)

if __name__ == "__main__" :
    main()
