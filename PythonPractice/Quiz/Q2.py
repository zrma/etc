# coding=utf-8
import sys


def IsVowel(word: str) -> bool:
    vowelSet = {'a', 'e', 'i', 'o', 'u'}
    return word in vowelSet


def IsExistTwoVowel(word: str) -> bool:
    for i, j in zip(word, word[1:]):
        if IsVowel(i) and IsVowel(j):
            return True

    # 검출 안 되면 없는 것
    return False


def IsExistThreeConsonant(word: str) -> bool:
    for i, j, k in zip(word, word[1:], word[2:]):
        if not IsVowel(i) and not IsVowel(j) and not IsVowel(k):
            return True

    # 검출 안 되면 없는 것
    return False


inputData = sys.stdin.readline()
inputList = inputData.split()

twoVowelCount = 0
threeConsonantCount = 0

for word in inputList:
    twoVowelCount += 1 if IsExistTwoVowel(word) else 0
    threeConsonantCount += 1 if IsExistThreeConsonant(word) else 0

print('{}\n{}'.format(twoVowelCount, threeConsonantCount))
