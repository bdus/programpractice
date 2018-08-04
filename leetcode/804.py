def fun(words):
    lis1 = [".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]
    lis2 = [chr(a) for a in range(ord('a'),ord('a')+26,1)]
    lisz = zip(lis2,lis1)
    liDict = dict((a,b) for a,b in lisz)
    ans = []
    for word in words:
        str = ''
        for i in range(len(word)):
            str = str + liDict[word[i]]
        ans.append(str)
        #print(ans)
    return len(list(set(ans)))

wordsss = ["gin", "zen", "gig", "msg"]
print(fun(wordsss))
