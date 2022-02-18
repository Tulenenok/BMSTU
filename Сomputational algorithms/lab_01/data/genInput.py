import numexpr as ne

# start = float(input("Input start x: "))
# end = float(input("Input end x: "))
# countPoints = int(input("Input count points: "))
# func = input("Input function (example, sin(x)): ")
# derivative = input("Input derivative (example, cos(x)): ")

start = -0.5
end = 0.3
countPoints = 10
func = 'sin(x)'
derivative = 'cos(x)'

with open("new.txt", 'w') as fout:
    x = start
    while x <= end:
        fout.write("%2.5f" % x + " " + "%2.5f" % ne.evaluate(func) + " " + "%2.5f" % (ne.evaluate(derivative)) + "\n")
        x += (end - start) / countPoints

