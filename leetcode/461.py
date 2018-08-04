class Solution:
    def hammingDistance(self, x, y):
        """
        :type x: int
        :type y: int
        :rtype: int
        """
        z = x ^ y
        cnt = 0
        while z != 0:
            cnt += (z % 2)
            z = z // 2
        return cnt

ss = Solution()
print(ss.hammingDistance(1,4))
