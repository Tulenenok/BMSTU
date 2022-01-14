# Алгоритм поиска в глубину в неориентированном графе
# t - древестные дуги
# b - обратные дуги
# сycles - фундаментальные циклы (циклы, в которых одна обратная дуга)

def init(visited, t, b, cycles, stack):
    visited = [] if (visited is None) else visited

    t = [] if t is None else t
    b = [] if b is None else b
    stack = [] if stack is None else stack
    cycles = [[]] if cycles is None else cycles

    return visited, t, b, cycles, stack

def dfs(graph, start, visited=None, t=None, b=None, cycles=None, stack=None):
    visited, t, b, cycles, stack = init(visited, t, b, cycles, stack)

    visited.append(start)
    stack.append(start)

    for next_top in graph[start]:
        if next_top not in visited:
            t.append((start, next_top))
            dfs(graph, next_top, visited, t, b, cycles, stack)

    for next_top in graph[start]:
        was_not_used_before = (start, next_top) not in t and (next_top, start) not in t and \
                              (start, next_top) not in b and (next_top, start) not in b
        if was_not_used_before:
            b.append((start, next_top))
            for i in range(stack.index(next_top), stack.index(start) + 1):
                cycles[len(cycles) - 1].append(stack[i])
            cycles[len(cycles) - 1].append(next_top)
            cycles.append([])

    stack.remove(start)

    return visited, t, b, cycles, stack


neo_graph = {'0': ['1', '3'],
             '1': ['2'],
             '2': ['4'],
             '3': ['0', '1', '4', '5'],
             '4': ['3'],
             '5': ['6', '7'],
             '6': [],
             '7': []}

visited, t, b, c, stack = dfs(neo_graph, '0')

print("Visited = ", visited)
print("T = ", t)
print("B = ", b)
print("Cycles = ", c)
print("Stack = ", stack)



