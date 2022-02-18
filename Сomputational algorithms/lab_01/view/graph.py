import numexpr as ne


def showGraphUsePol(table, polStr, plt, label, color):
    X, Y = [], []
    x = table[0][0]
    while x <= table[0][-1]:
        Y.append(ne.evaluate(polStr))
        X.append(x)
        x += (table[0][-1] - table[0][0]) / 50

    plt.plot(X, Y, color, ms=5, label=label)



def showGraphUsePoints(X, Y, plt, label, color):
    plt.plot(X, Y, color, ms=5, label=label)