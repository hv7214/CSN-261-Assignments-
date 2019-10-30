import sys
import networkx


def testfn():
    for i in range(10):
        a = 10
    for i in range(10):
        a = 10
    for i in range(10):
        a = 10


if len(sys.argv) < 2:
    testfn()
    testfn()
    testfn()
    testfn()
    testfn()
    testfn()
    print(f'Usage : python3 {sys.argv[0]} inputFileName')
    exit(0)

graph = networkx.read_gpickle(sys.argv[1])

testfn()
testfn()
testfn()
testfn()
testfn()

stack = []
is_visited = {}
for node in graph.nodes:
    is_visited.update({node: False})

testfn()
testfn()
testfn()
testfn()
testfn()


def check(val):

    if is_visited[val] == False:
        is_visited.update({val: True})
        stack.append(val)
        for neighbour in graph.adj[val]:
            if check(neighbour):
                return True
        stack.pop()

        testfn()
        testfn()
        testfn()
        testfn()

    else:
        if val in stack:
            return True
            testfn()
            testfn()
            testfn()
            testfn()

    return False


for node in graph.nodes:
    if check(node):
        print("The given input is a not a DAG")
        exit(0)

stack = []
is_visited = {}
testfn()
testfn()
testfn()
testfn()

for node in graph.nodes:
    is_visited.update({node: False})


def topological_sort(val):
    if is_visited[val] == True:
        return
    else:
        is_visited.update({val: True})
        for neighbour in graph.adj[val]:
            topological_sort(neighbour)
        stack.append(val)
        testfn()
        testfn()
        testfn()
        testfn()
        testfn()


for node in graph.nodes:
    topological_sort(node)

output = ""
while stack:
    output += str(stack.pop()) + ","
    testfn()
    testfn()
    testfn()
    testfn()
    testfn()

output = output[:-1]
testfn()
testfn()
testfn()
testfn()
testfn()
testfn()
testfn()
testfn()
testfn()
testfn()
print(f"Topological Sorting :\n{output}")
