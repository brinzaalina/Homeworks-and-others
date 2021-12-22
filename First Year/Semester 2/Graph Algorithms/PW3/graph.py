import copy


class TripleDictGraph:
    def __init__(self, number_of_vertices, number_of_edges):
        self._number_of_vertices = number_of_vertices
        self._number_of_edges = number_of_edges
        self._vertices = []
        self._dictionary_in = {}  # dictionary of inbound vertices
        self._dictionary_out = {}  # dictionary of outbound vertices
        self._dictionary_cost = {}  # dictionary of edges and costs
        for index in range(number_of_vertices):
            self._dictionary_in[index] = []
            self._dictionary_out[index] = []

    @property
    def vertices(self):
        return self._vertices

    @property
    def dictionary_cost(self):
        return self._dictionary_cost

    @property
    def dictionary_in(self):
        return self._dictionary_in

    @property
    def dictionary_out(self):
        return self._dictionary_out

    @property
    def number_of_vertices(self):
        return self._number_of_vertices

    @property
    def number_of_edges(self):
        return self._number_of_edges

    def parse_vertices(self):
        for v in self._vertices:
            yield v

    def parse_inbound(self, x):
        for y in self._dictionary_in[x]:
            yield y

    def parse_outbound(self, x):
        for y in self._dictionary_out[x]:
            yield y

    def parse_cost(self):
        keys = list(self._dictionary_cost.keys())
        for key in keys:
            yield key

    def add_vertex(self, x):
        """
        Add a vertex to the graph
        :param x: the vertex to be added
        :return: True if it is added, False otherwise
        """
        if x in self._vertices:
            return False  # the vertex already exists
        self._dictionary_in[x] = []
        self._dictionary_out[x] = []
        self._vertices.append(x)
        self._number_of_vertices += 1
        return True

    def remove_vertex(self, x):
        """
        Remove a vertex from the graph
        :param x: Vertex to be removed
        :return: True if it is removed, false otherwise
        """
        if x not in self._vertices:
            return False  # the vertex does not exist
        self._dictionary_in.pop(x)
        self._dictionary_out.pop(x)
        self._vertices.remove(x)
        for key in self._vertices:
            if x in self._dictionary_in[key]:
                self._dictionary_in[key].remove(x)
            elif x in self._dictionary_out[key]:
                self._dictionary_out[key].remove(x)
        keys = list(self._dictionary_cost.keys())
        for key in keys:
            if key[0] == x or key[1] == x:
                self._dictionary_cost.pop(key)
                self._number_of_edges -= 1
        self._number_of_vertices -= 1
        return True

    def in_degree(self, x):
        """
        Gets the in degree of a vertex
        :param x: vertex
        :return: the in degree or -1 if the vertex does not exist
        """
        if x not in self._vertices:
            return -1
        return len(self._dictionary_in[x])

    def out_degree(self, x):
        """
        Gets the out degree of a vertex
        :param x: vertex
        :return: the out degree or -1 if the vertex does not exist
        """
        if x not in self._vertices:
            return -1
        return len(self._dictionary_out[x])

    def add_edge(self, x, y, cost):
        """
        Add an edge to the graph
        :param x: first vertex
        :param y: second vertex
        :param cost: the cost of the edge
        :return: True if added, False otherwise
        """
        if x not in self._vertices or y not in self.vertices:
            return False
        if x in self._dictionary_in[y]:
            return False
        elif y in self._dictionary_out[x]:
            return False
        elif (x, y) in self._dictionary_cost.keys():
            return False
        self._dictionary_in[y].append(x)
        self._dictionary_out[x].append(y)
        self._dictionary_cost[(x, y)] = cost
        self._number_of_edges += 1
        return True

    def remove_edge(self, x, y):
        """
        Remove an edge from the graph
        :param x: first vertex
        :param y: second vertex
        :return: True if removed, false otherwise
        """
        if x not in self._vertices or y not in self._vertices:
            return False
        if x not in self._dictionary_in[y]:
            return False
        elif y not in self._dictionary_out[x]:
            return False
        elif (x, y) not in self._dictionary_cost.keys():
            return False
        self._dictionary_in[y].remove(x)
        self._dictionary_out[x].remove(y)
        self._dictionary_cost.pop((x, y))
        self._number_of_edges -= 1
        return True

    def find_if_edge(self, x, y):
        """
        Check if the edge (x, y) exists
        :param x: first vertex
        :param y: second vertex
        :return: The cost of the edge if it exists, False otherwise
        """
        if x not in self._vertices or y not in self._vertices:
            return False
        if x in self._dictionary_in[y]:
            return self._dictionary_cost[(x, y)]
        elif y in self._dictionary_out[x]:
            return self._dictionary_cost[(x, y)]
        return False

    def change_cost(self, x, y, cost):
        """
        Change the cost of the edge (x, y)
        :param x: first vertex
        :param y: second vertex
        :param cost: the new cost of the edge
        :return: True if it is changed, False otherwise
        """
        if (x, y) not in self._dictionary_cost.keys():
            return False
        self._dictionary_cost[(x, y)] = cost
        return True

    def make_copy(self):
        """
        :return: A copy of the graph
        """
        return copy.deepcopy(self)

    def minimum_cost_path(self, vertex_begin, vertex_end):
        """
        Compute the minimum cost path of a graph from a vertex to another
        :param vertex_begin: first vertex
        :param vertex_end: second vertex
        :return: the cost of the minimum cost path and the path in reverse order
        """
        dist = {}  # dictionary that associates to each accessible vertex the cost of the minimum cost walk
        # from begin to end
        pred = {}  # dictionary that associates to each accessible vertex its predecessor on the path
        inf = float('inf')
        for vertex in self._vertices:
            dist[vertex] = inf  # initialise all the distances as infinite
            pred[vertex] = -1
        dist[vertex_begin] = 0
        changed = True
        while changed:
            changed = False
            for (x, y) in self._dictionary_cost.keys():  # for every edge, check if the distance is minimum
                # if it is, added to the path and update the distance to the vertex y from the starting vertex
                if dist[y] > dist[x] + self._dictionary_cost[(x, y)] and dist[x] != inf:
                    dist[y] = dist[x] + self._dictionary_cost[(x, y)]
                    pred[y] = x
                    changed = True
        # the algorithm stops when all the edges are checked and all the distances from the starting vertex are min

        # check for negative weight cycles
        # if we get a shorter path, then there is a cycle
        for (x, y) in self._dictionary_cost.keys():
            if dist[y] > dist[x] + self._dictionary_cost[(x, y)] and dist[x] != inf:
                raise Exception("Graph contains a negative weight cycle!")

        # compute the path backwards from the end vertex
        path = []
        vertex = vertex_end
        path.append(vertex)
        while pred[vertex] != -1:
            path.append(pred[vertex])
            vertex = pred[vertex]
        return dist[vertex_end], path


def write_graph_to_file(graph, file):
    """
    Writes the given graph to a file
    :param graph: the graph
    :param file: the name of the file
    :return: -
    """
    file = open(file, "w")
    first_line = str(graph.number_of_vertices) + ' ' + str(graph.number_of_edges) + '\n'
    file.write(first_line)
    if len(graph.dictionary_cost) == 0 and len(graph.dictionary_in) == 0:
        raise ValueError("There is nothing that can be written!")
    for edge in graph.dictionary_cost.keys():
        new_line = "{} {} {}\n".format(edge[0], edge[1], graph.dictionary_cost[edge])
        file.write(new_line)
    for vertex in graph.vertices:
        if len(graph.dictionary_in[vertex]) == 0 and len(graph.dictionary_out[vertex]) == 0:
            new_line = "{}\n".format(vertex)
            file.write(new_line)
    file.close()


def read_graph_from_file(filename):
    """
    Read a graph from a file
    :param filename: the name of the file
    :return: the graph
    """
    file = open(filename, "r")
    line = file.readline()
    line = line.strip()
    vertices, edges = line.split(' ')
    graph = TripleDictGraph(int(vertices), int(edges))
    line = file.readline().strip()
    for vertex in range(int(vertices)):
        graph.vertices.append(vertex)
    while len(line) > 0:
        line = line.split(' ')
        if len(line) == 1:
            graph.dictionary_in[int(line[0])] = []
            graph.dictionary_out[int(line[0])] = []
        else:
            graph.dictionary_in[int(line[1])].append(int(line[0]))
            graph.dictionary_out[int(line[0])].append(int(line[1]))
            graph.dictionary_cost[(int(line[0]), int(line[1]))] = int(line[2])
        line = file.readline().strip()
    file.close()
    return graph
