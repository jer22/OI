input = raw_input().split()
n = int(input[0])
d = int(input[1])
dp = [0] * 20
dp[0] = 1
dp[1] = 1
for i in range (2, d + 1) :
	a = 0
	for j in range (0, i - 1) :
		a += dp[j]
	dp[i] += (a + dp[i - 1]) ** n
	dp[i] -= a ** n
print dp[d]
