n = int(raw_input())
dp = [0] * 505
dp[0] = 1
dp[1] = 1
for i in range (2, n + 1) :
	for j in range(1, i + 1) :
		a = j
		b = i + 1 - a
		dp[i] += dp[i - a] * dp[i - b]
print dp[n]
