import Queue

input = open('1231.in', 'r')
line = input.readline().split()

class Node :
	def __init__(self, a, b):
		self.last = a
		self.stat = b

n = int(line[0])
K = int(line[1])
i = 0
j = 0
num = [i for i in range(20)]
vis = [[0] * 20] * 135550
dp = [[0] * 20] * 135550
q = Queue.Queue()
for i in range(n) :
	line = input.readline().split()
	num[i] = int(line[0])
	q.put(Node(i, 1 << i))
	dp[i][1 << i] = 1
	vis[i][1 << i] = 1
input.close();

while not q.empty() :
	cur = q.get()
	vis[cur.last][cur.stat] = 0

	for i in range(n) :
		if ((1 << i) & cur.stat) > 0 : continue
		if (abs(num[i] - num[cur.last]) <= K) :
			continue

		nex = (cur.stat | (1 << i))
		dp[i][nex] += dp[cur.last][cur.stat]

		if vis[i][nex] == 0 :
			vis[i][nex] = 1
			print i, nex
			q.put(Node(i, nex))
ans = 0
for i in range(n) :
	ans += dp[i][(1 << n) - 1]
print ans
