# Алгоритм поиска в глубину в ориентированном графе
# t - древестные дуги
# f - прямые дуги
# b - обратные дуги
# с - поперечные дуги

def init(visited, t, f, b, c):
    visited = [] if (visited is None) else visited

    t = [] if t is None else t
    f = [] if f is None else f
    b = [] if b is None else b
    c = [] if c is None else c

    return visited, t, f, b, c

def dfs(graph, start, visited=None, t=None, f=None, b=None, c=None):
    visited, t, f, b, c = init(visited, t, f, b, c)

    visited.append(start)

    for next_top in graph[start]:
        if next_top not in visited:
            t.append( (start, next_top) )
            dfs(graph, next_top, visited, t, f, b, c)

    for v in graph[start]:
        if (start, v) in t:
            continue

        if (v, start) in t:
            b.append((start, v))
            continue

        rc = visited.index(start) - visited.index(v)
        if rc >= 1:
            c.append((start, v))
        elif rc < 1:
            f.append((start, v))

    return visited, t, f, b, c


graph = {'0': ['1', '2'],
         '1': ['0', '3', '4'],
         '2': ['0'],
         '3': ['1'],
         '4': ['2', '3']}

graph1 = {
    'A' : ['B', 'S'],
    'B' : ['A'],
    'C' : ['D', 'E', 'F', 'S'],
    'D' : ['C'],
    'E' : ['C', 'H'],
    'F' : ['C', 'G'],
    'G' : ['F', 'S'],
    'H' : ['E', 'G'],
    'S' : ['A', 'C', 'G']
}

visited, t, f, b, c = dfs(graph1, 'A')

print("Visited = ", visited)
print("T = ", t)
print("F = ", f)
print("B = ", b)
print("C = ", c)
