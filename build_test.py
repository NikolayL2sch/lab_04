from random import *

n = 10000
a = [randint(-1000, 1000) for i in range(n)]
f = open("input_4.txt", "w+")
f.write(str(n)+"\n")
for elem in a:
	f.write(str(elem)+" ")
f.close()
