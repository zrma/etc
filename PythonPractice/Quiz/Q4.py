# coding=utf-8
import sys


inputData = sys.stdin.readline()
inputList = [int(x) for x in inputData.split()]

comparator = lambda x: x if x >= 10 else x * 11

inputList.sort(key = comparator)
minest = ''.join(str(x) for x in inputList)

inputList.sort(key = comparator, reverse = True)
maxest = ''.join(str(x) for x in inputList)

result = int(minest) + int(maxest)
print('{}'.format(result))
