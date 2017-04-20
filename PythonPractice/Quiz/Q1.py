# coding=utf-8
import sys


inputData = sys.stdin.readline()
inputList = [int(x) for x in inputData.split()]
inputList.sort()

if len(inputList) > 1:
    minPrev, minNext = inputList[: 2]
    minDist = minNext - minPrev

    for prev, next in zip(inputList[1:], inputList[2:]):
        dist = next - prev

        if minDist > dist:
            minDist = dist
            minPrev, minNext = prev, next

    print('{} {}'.format(minPrev, minNext))
