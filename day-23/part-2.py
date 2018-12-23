import sys
import re
import z3

class Nanobot:
    def __init__(self, x, y, z, r):
        self._x = int(x)
        self._y = int(y)
        self._z = int(z)
        self._r = int(r)

    def __str__(self):
        return "({}, {}, {}) [{}]".format(self._x, self._y, self._z, self._r)

if (len(sys.argv) != 2):
    print("Please provide a filename")
    exit()

bots = []

with open(sys.argv[1]) as f:
    for line in f.readlines():
        bots.append(Nanobot(*re.findall(r'-?\d+', line)))

def z3abs(x):
    return z3.If(x >= 0, x, -x)

range_count = z3.Int('sum')
x, y, z = z3.Ints('x y z')
in_ranges = [z3.Int('in_range_' + str(i)) for i, _ in enumerate(bots)]
dist_from_zero = z3.Int('dist')

o = z3.Optimize()
for i, b in enumerate(bots):
    o.add(in_ranges[i] == z3.If(z3abs(x - b._x) + z3abs(y - b._y) + z3abs(z - b._z) <= b._r, 1, 0))

o.add(dist_from_zero == z3abs(x) + z3abs(y) + z3abs(z))
o.add(range_count == sum(in_ranges))

h1 = o.maximize(range_count)
h2 = o.minimize(dist_from_zero)

o.check()

print("Min distance is {}".format(o.lower(h2)))
