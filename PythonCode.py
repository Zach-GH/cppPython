import re
import string
from typing import ValuesView
#used to clear the screen
from os import system, name

# clear screen for both windows (nt) and mac/linux (clear)
def clear():
    if name == 'nt':
        _ = system('cls')
    else:
        _ = system('clear')

def printsomething():
    print("Hello from python!")


def PrintMe(v):
    print("You sent me: " + v)
    return 100;

# creates a multiplication table using a for loop in the range of 1 - 10
def MultiplicationTable(v):
    clear()
    print("The number you entered was", v)
    for i in range (1, 11):
        (print(v, "X", i, "=", v*i))
    return 0;
    
# function to double a value passed to the function
def DoubleValue(v):
    clear()
    print("The number you entered was", v)
    print(v, "X 2 =", v*2)
    return 0;

def SquareValue(v):
    return v * v
