from prettytable import PrettyTable

# ***********************************************
# Построение коэффициентов на конкретном примере
# ***********************************************


def Fi(yi_2, yi_1, yi, hi_1, hi):
    return 3 * ((yi - yi_1) / hi - (yi_1 - yi_2) / hi_1)


def Ei__1(hi_1, hi, Ei):
    return - hi / (hi_1 * Ei + 2 * (hi_1 + hi))


def Ni__1(fi, hi_1, hi, Ei, ni):
    return (fi - hi_1 * ni) / (hi_1 * Ei + 2 * (hi_1 + hi))


def Ci(hi_1, hi, fi, Ei, ni, ci__1):
    return - hi / (hi_1 * Ei + 2 * (hi_1 + hi)) * ci__1 + (fi - hi_1 * ni) / (hi_1 * Ei + 2 * (hi_1 + hi))


def Ai(yi_1):
    return yi_1


def Bi(hi, yi_1, yi, ci, ci__1):
    return (yi - yi_1) / hi - hi * (ci__1 + 2 * ci) / 3


def Bn(hn, yn_1, yn, cn):
    return (yn - yn_1) / hn - hn * 2 * cn / 3


def Di(ci, ci__1, hi):
    return (ci__1 - ci) / (3 * hi)


def Dn(cn, hn):
    return - cn / (3 * hn)



x = [-4, -2, 0, 1, 3]
y = [0, 1, 2, 1, 0]

countValues = len(x)                 # 5
countSplines = countValues - 1       # 4

h = [''] + [x[i] - x[i - 1] for i in range(1, countValues)]
f = ['', ''] + [Fi(y[i - 2], y[i - 1], y[i], h[i - 1], h[i]) for i in range(2, countValues)]

E = ['', '', 0]
for i in range(2, countValues):
    E.append(Ei__1(h[i - 1], h[i], E[i]))

n = ['', '', 0]
for i in range(2, countValues):
    n.append(Ni__1(f[i], h[i - 1], h[i], E[i], n[i]))

c = [''] + [0 for i in range(countValues)]
for i in range(countValues - 1, 1, -1):
    c[i] = Ci(h[i - 1], h[i], f[i], E[i], n[i], c[i + 1])


a = [''] + [Ai(y[i - 1]) for i in range(1, countValues)]

b = [''] + \
    [Bi(h[i], y[i - 1], y[i], c[i], c[i + 1]) for i in range(1, countSplines)] + \
    [Bn(h[countSplines], y[countSplines - 1], y[countSplines], c[countSplines])]

d = [''] + \
    [Di(c[i], c[i + 1], h[i]) for i in range(1, countSplines)] + \
    [Dn(c[countSplines], h[countSplines])]




resTable = PrettyTable()
resTable.field_names = ['x', 'y', 'h', 'f', 'E', 'n', 'c', 'a', 'b', 'd']

for i in range(countValues):
    resTable.add_row([x[i], y[i], h[i], f[i], E[i], n[i], c[i], a[i], b[i], d[i]])

print(resTable)


