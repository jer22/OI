import Queue

class Edge :
	def __init__(self, a, b) :
		self.to = a
		self.v = b

input = open("1631.in", "r")
line = input.readline().split()
# line = raw_input().split()

global n, m, S
global edges, redges
n = int(line[0])
m = int(line[1])
S = int(line[2])
edges = {}
redges = {}
for i in range(n + 1) :
	edges[i] = []
	redges[i] = []

for i in range(m) :
	line = input.readline().split()
	# line = raw_input().split()
	while len(line) == 0 :
		line = input.readline().split()
		# line = raw_input().split()
	x = int(line[0])
	y = int(line[1])
	v = int(line[2])
	edges[x].append(Edge(y, v))
	redges[y].append(Edge(x, v))

def spfa(graph) :
	dist = [1000000000] * 1005
	vis = [False] * 1005
	dist[S] = 0
	vis[S] = 1
	q = Queue.Queue()
	q.put(S)
	while not q.empty() :
		cur = q.get()
		vis[cur] = False
		for e in graph[cur] :
			if (dist[cur] + e.v < dist[e.to]) :
				dist[e.to] = dist[cur] + e.v
				if (not vis[e.to]) :
					vis[e.to] = 1;
					q.put(e.to);
	return dist

dist1 = spfa(edges)
dist2 = spfa(redges)

ans = 0
for i in range(1, n + 1) :
	ans = max(ans, dist1[i] + dist2[i])
print ans

# input.close()