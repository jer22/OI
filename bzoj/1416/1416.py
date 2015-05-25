arr = []
tot = 0

def gcd(m, n) :
	while n :
		m, n = n, m % n
	return m

if __name__ == '__main__' :
	line = raw_input().split()
	n, m, d = int(line[0]), int(line[1]), int(line[2])
	line = raw_input().split()
	arr.append(0)
	for i in range(n) :
		x = int(line[i])
		arr.append(x)
		tot += x
	a, b = 1, 1
	for i in range(m) :
		x = int(raw_input().split()[1])
		a, b = a * arr[x], b * tot
		arr[x] += d
		tot += d
		a, b = a / gcd(a, b), b / gcd(a, b)
	print '%d/%d' % (a, b)

