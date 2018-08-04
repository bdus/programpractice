def numJewelsInStones(self, J, S):
        """
        :type J: str
        :type S: str
        :rtype: int
        """
        S = list(S)
        sum=0
        for c in J:
            sum = sum + S.count(c)
        return sum
