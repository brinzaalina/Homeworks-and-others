import copy
import heapq


class UndirectedGraph:
    def __init__(self, number_of_vertices, number_of_edges):
        """
        Initialization of the graph
        :param number_of_vertices: the number of vertices
        :param number_of_edges: the number of edges
        """
        self._number_of_vertices = number_of_vertices
        self._number_of_edges = number_of_edges
        self._dictionary_bound = {}
        self._costs = []
        self._vertices = []
        for index in range(number_of_vertices):
            self._dictionary_bound[index] = []  # create an empty list for every vertex
            self._vertices.append(index)

    @property
    def vertices(self):
        return self._vertices  # getter for vertices

    @property
    def dictionary_bound(self):  # getter for the list of bound vertices
        return self._dictionary_bound

    @property
    def costs(self):
        return self._costs

    @property
    def number_of_vertices(self):  # getter for the number of vertices
        return self._number_of_vertices

    @property
    def number_of_edges(self):  # getter for the number of edges
        return self._number_of_edges

    @number_of_edges.setter
    def number_of_edges(self, value):  # setter for the number of edges
        self._number_of_edges = value

    def parse_vertices(self):  # iterator for the vertices
        for v in self._vertices:
            yield v

    def parse_bound(self, x):  # iterator for the bound vertices
        for y in self._dictionary_bound[x]:
            yield y

    def parse_cost(self):
        keys = self.costs
        for key in keys:
            yield key

    def degree(self, x):
        """
        Get the degree of a vertex if it exists
        :param x: the vertex for which we get the degree
        :return: the number of bound vertices or -1 if the vertex does not exist
        """
        if x not in self._dictionary_bound.keys():
            return -1
        return len(self._dictionary_bound[x])

    def add_edge(self, x, y, cost):
        """
        Add an edge if it is valid: the vertices exist and the edge does not exist
        :param x: First vertex
        :param y: Second vertex
        :param cost: const of edge
        :return: False if it can't be added, True otherwise
        """
        if x not in self._vertices or y not in self._vertices:
            return False
        if x == y:
            return False
        if x in self._dictionary_bound[y] and y in self._dictionary_bound[x]:
            return False

        self._dictionary_bound[y].append(x)  # add x to the list of bound vertices for y
        self._dictionary_bound[x].append(y)  # add y to the list of bound vertices for x
        self.costs.append([x, y, cost])
        self._number_of_edges += 1  # increase the number of edges
        return True

    def find_if_edge(self, x, y):
        """
        Check if there is an edge between two edges
        :param x: the first vertex
        :param y: the second vertex
        :return: False if the vertices don't exist or the edge does not exist, True if the edge exists
        """
        if x not in self._vertices or y not in self._vertices:
            return False
        if x in self._dictionary_bound[y] and y in self._dictionary_bound[x]:
            return True
        return False

    def find_cost(self, x, y):
        value = -1
        for index in range(0, len(self.costs)):
            if (self.costs[index][0] == x and self.costs[index][1] == y) or (self.costs[index][0] == y and self.costs[index][1] == x):
                value = self.costs[index][2]
        if value == -1:
            raise ValueError("No edge!")
        return value

    def make_copy(self):
        """
        Make a copy of the current graph
        :return: the copy
        """
        return copy.deepcopy(self)

    def DFSUtil(self, v, visited, traversal):
        visited.add(v)
        traversal.append(v)
        for neighbour in self._dictionary_bound[v]:
            if neighbour not in visited:
                self.DFSUtil(neighbour, visited, traversal)  # go recursively through all the bound vertices
                # that are not visited yet

    def DFS(self, v):
        visited = set()
        traversal = []
        self.DFSUtil(v, visited, traversal)
        return traversal

    def primsMST(self):
        for x in self.parse_vertices():
            s = x
            break
        q = []  # heap for the edges to be visited
        for x in self.parse_bound(s):
            heapq.heappush(q, (self.find_cost(s, x), s, x))
        treeVertices = {s}
        treeEdges = []  # edges of the tree
        treeCost = 0
        while len(q) > 0:  # algorithm stops when there are no edges left in the heap
            cost, x, y = heapq.heappop(q)
            if y in treeVertices:
                continue
            treeVertices.add(y)
            treeEdges.append((x, y))
            treeCost = treeCost + cost
            for z in self.parse_bound(y):  # go through the bound edges and find other candidate edge
                if z not in treeVertices:
                    heapq.heappush(q, (self.find_cost(y, z), y, z))
        return (treeEdges, treeCost)


def write_graph_to_file(graph, file):
    """
    Write the given graph to a file
    :param graph: the graph to be written
    :param file: the name of the file
    :return: -
    """
    file = open(file, "w")
    first_line = str(graph.number_of_vertices) + ' ' + str(graph.number_of_edges) + '\n'
    file.write(first_line)
    if len(graph.vertices) == 0 and len(graph.dictionary_bound) == 0 and len(graph.dictionary_costs):
        raise ValueError("There is nothing that can be written!")  # check if there is anything to be written
    for vertex in graph.vertices:  # get the edges, making sure that there are no duplicates
        if len(graph.dictionary_bound[vertex]) == 0:
            new_line = "{}\n".format(vertex)
            file.write(new_line)
    for edge in graph.costs:
        new_line = "{} {} {}\n".format(edge[0], edge[1], edge[2])
        # write the edges to the file
        file.write(new_line)
    file.close()


def read_graph_from_file(filename):
    """
    Read a graph from a given file
    :param filename: The name of the file from which the graph will be read
    :return: the new graph
    """
    file = open(filename, "r")
    line = file.readline()
    line = line.strip()
    vertices, edges = line.split(' ')
    graph = UndirectedGraph(int(vertices), 0)  # initialize a new graph
    line = file.readline().strip()
    while len(line) > 0:  # add the edges to the graph, line by line
        line = line.split(' ')
        if len(line) != 1:
            if int(line[0]) != int(line[1]):  # if the line contains 2 different vertices
                # we can have an edge
                if int(line[0]) not in graph.dictionary_bound[int(line[1])] and int(line[1]) not in graph.dictionary_bound[int(line[0])]:
                    graph.number_of_edges += 1
                    graph.dictionary_bound[int(line[1])].append(int(line[0]))
                    graph.dictionary_bound[int(line[0])].append(int(line[1]))
                    graph.costs.append([int(line[0]), int(line[1]), int(line[2])])
        else:
            graph.dictionary_bound[int(line[0])] = []
        line = file.readline().strip()
    file.close()
    return graph
