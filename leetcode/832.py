def ReverseRow(line):
    return line[::-1]

def invertRow(line):
    return [c*-1+1 for c in line]

def fineAndInvert(A):
    ans = []
    for line in A:
        ans.append(invertRow(ReverseRow(line)))
    return ans

class Solution:
    def flipAndInvertImage(self, A):
        """
        :type A: List[List[int]]
        :rtype: List[List[int]]
        """
        ans = []
        for line in A:
            line = line[::-1]
            line = [c*-1+1 for c in line]
            ans.append(line)
        return ans
