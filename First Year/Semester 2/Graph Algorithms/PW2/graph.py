import copy


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

    def add_vertex(self, x):
        """
        Add a vertex to the graph if it doesn't already exist
        :param x: the vertex to be added
        :return: True if it didn't exist, False otherwise
        """
        if x in self._vertices:
            return False
        self._vertices.append(x)  # add the vertex to the list of vertices
        self._dictionary_bound[x] = []  # initialize the list of bound vertices for x
        self._number_of_vertices += 1  # increase the number of vertices
        return True

    def remove_vertex(self, x):
        """
        Remove a vertex from the graph; it must already exist
        :param x: the vertex to be removed
        :return: True if it is removed, False if it doesn't exist
        """
        if x not in self._vertices or x not in self._dictionary_bound.keys():
            return False
        self._vertices.remove(x)  # remove from the list of vertices
        self._dictionary_bound.pop(x)  # remove the key x
        self._number_of_vertices -= 1  # decrease the number of vertices
        for key in self._dictionary_bound.keys():  # remove all occurrences in the bound dictionary
            if x in self._dictionary_bound[key]:
                self._dictionary_bound[key].remove(x)
                self._number_of_edges -= 1  # decrease the number of edges
        return True

    def degree(self, x):
        """
        Get the degree of a vertex if it exists
        :param x: the vertex for which we get the degree
        :return: the number of bound vertices or -1 if the vertex does not exist
        """
        if x not in self._dictionary_bound.keys():
            return -1
        return len(self._dictionary_bound[x])

    def add_edge(self, x, y):
        """
        Add an edge if it is valid: the vertices exist and the edge does not exist
        :param x: First vertex
        :param y: Second vertex
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
        self._number_of_edges += 1  # increase the number of edges
        return True

    def remove_edge(self, x, y):
        """
        Remove an edge if the vertices exist and the edge exists too
        :param x: First vertex
        :param y: Second vertex
        :return: True if it is removed, False if the vertices don't exist or the edge does not exist
        """
        if x not in self._vertices or y not in self._vertices:
            return False
        if x not in self._dictionary_bound[y] or y not in self.dictionary_bound[x]:
            return False
        self._dictionary_bound[y].remove(x)  # remove x from the bound vertices of y
        self._dictionary_bound[x].remove(y)  # remove y from the bound vertices of x
        self._number_of_edges -= 1  # decrease the number of edges
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

    def make_copy(self):
        """
        Make a copy of the current graph
        :return: the copy
        """
        return copy.deepcopy(self)

    def breath_first_traversal(self, vertex, visited):
        """
        Traverse the graph with a breath-first algorithm for a given vertex
        :param vertex: the starting vertex
        :param visited: a map to mark the visited vertices
        :return: the connected component with the given vertex as a starting vertex
        """
        queue_list = []  # queue for BFS
        connected = []  # this list will contain the connected components
        queue_list.append(vertex)  # Add the starting vertex to the queue
        visited[vertex] = True  # Mark the starting vertex as visited
        while queue_list:
            x = queue_list.pop(0)  # pop the first element from the queue and add it to the list of connected components
            connected.append(x)
            for i in self.dictionary_bound[x]:  # get all the adjacent vertices of the vertex x that are not visited yet
                # mark them and add them to the queue
                if visited[i] is False:
                    queue_list.append(i)
                    visited[i] = True
        return connected  # return the connected components

    def find_connected_components(self):
        visited = {}
        connected = []  # list of connected comp
        all_connected = []  # all the connected comp
        for vertex in self._vertices:
            visited[vertex] = False  # create a dict used as a map to mark if a vertex is visited
        for vertex in self._vertices:  # find the connected components of the graph by calling BFS for every vertex
            # that is not yet visited
            if visited[vertex] is False:
                connected = self.breath_first_traversal(vertex, visited)
                all_connected.append(connected)
        return all_connected


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
    if len(graph.vertices) == 0 and len(graph.dictionary_bound) == 0:
        raise ValueError("There is nothing that can be written!")  # check if there is anything to be written
    edges = []
    for vertex in graph.vertices:  # get the edges, making sure that there are no duplicates
        if len(graph.dictionary_bound[vertex]) != 0:
            for second_vertex in graph.dictionary_bound[vertex]:
                edge = (vertex, second_vertex)
                if (vertex, second_vertex) not in edges and (second_vertex, vertex) not in edges:
                    edges.append(edge)
        else:
            new_line = "{}\n".format(vertex)
            file.write(new_line)
    for edge in edges:  # write the edges to the file
        new_line = "{} {}\n".format(edge[0], edge[1])
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
        if len(line) != 1 and int(line[0]) != int(line[1]):  # if the line contains 2 different vertices
            # we can have an edge
            if int(line[0]) not in graph.dictionary_bound[int(line[1])]:
                graph.number_of_edges += 1
                graph.dictionary_bound[int(line[1])].append(int(line[0]))  # add the edge to the graph
            if int(line[1]) not in graph.dictionary_bound[int(line[0])]:
                graph.dictionary_bound[int(line[0])].append(int(line[1]))  # add the edge to the graph
        line = file.readline().strip()
    file.close()
    return graph
