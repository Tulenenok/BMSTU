import numexpr as ne


def showGraphUsePol(tableNewton, polStr, plt, label, color):
    X, Y = [], []
    x = tableNewton[0][0]
    while x <= tableNewton[0][-1]:
        Y.append(ne.evaluate(polStr))
        X.append(x)
        x += (tableNewton[0][-1] - tableNewton[0][0]) / 50

    plt.plot(X, Y, color, ms=5, label=label)



def showGraphUsePoints(X, Y, plt, label, color):
    plt.plot(X, Y, color, ms=5, label=label)