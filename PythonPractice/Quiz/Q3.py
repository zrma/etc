# coding=utf-8
import sys


def ReverseNum(num: int) -> int:
    return int(str(num)[::-1])


def IsPalindrome(num: int) -> bool:
    return str(num) == str(num)[::-1]


inputData = sys.stdin.readline()
inputNum = int(inputData)

count = 0
while not IsPalindrome(inputNum) and count < 3:
    count += 1

    reversedNum = ReverseNum(inputNum)
    inputNum = inputNum + reversedNum

if count == 3:
    print('{}'.format(-1))
else:
    print('{}'.format(inputNum))
