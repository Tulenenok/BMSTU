import numexpr as ne
import random
import matplotlib.pyplot as plt

def randomColor():
    return "#" + ''.join([random.choice('0123456789ABCDEF') for j in range(6)])

def genPointsForLine(xStart, xEnd, pol):
    X, Y = [], []
    x = xStart
    while x <= xEnd:
        Y.append(pol.findValue(x=x))
        X.append(x)
        x += (xEnd - xStart) / 50

    return X, Y


def showPol(table, newton, spline_0_0, spline_P_0, spline_P_P):
    xStart = table.x[0]
    xEnd = table.x[-1]

    NX, NY = genPointsForLine(xStart, xEnd, newton)
    S00X, S00Y = genPointsForLine(xStart, xEnd, spline_0_0)
    SP0X, SP0Y = genPointsForLine(xStart, xEnd, spline_P_0)
    SPPX, SPPY = genPointsForLine(xStart, xEnd, spline_P_P)

    plt.plot(table.x, table.y, 'mo', label='Start points')
    plt.plot(NX, NY, randomColor(), label='Newton')
    plt.plot(S00X, S00Y, randomColor(), label='Spline 0 0')
    plt.plot(SP0X, SP0Y, randomColor(), label='Spline P 0')
    plt.plot(SPPX, SPPY, randomColor(), label='Spline P P')

    plt.legend()
    ax = plt.gca()
    ax.spines['left'].set_position('center')
    ax.spines['bottom'].set_position('center')
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)

    plt.show()

