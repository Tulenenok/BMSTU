import matplotlib.pyplot as plt
from scipy.interpolate import UnivariateSpline

def takeData(src):
    x, y = [], []
    with open(src, 'r') as fin:
        for line in fin:
            x.append(float(line.split()[0]))
            y.append(float(line.split()[1]))
    return x, y

def createGraph(i, colorPoint, colorLine):
    x, y = takeData("..\\data\\time_result.txt")
    spl = UnivariateSpline(x, y)

    ax.plot(x, y, colorPoint, ms=5)
    ax.plot(x, spl(x), colorLine, lw=1)

fig, ax = plt.subplots()
createGraph(1, 'g', 'm')
ax.legend(['count_elem', 'interpol(count_elem)'], loc=0)
plt.xlabel('Количество элементов')
plt.ylabel('Время')
plt.title('Зависимость времени от количества элементов',)
ax.grid(True)
fig.savefig('..\\results\\time.svg')