from main import *
class UI:
    def __init__(self, fileName):
        self.Graph = Graph(fileName)

    @staticmethod
    def menu():
        stri = ""
        stri += "\t  0. exit; \n"
        stri += "\t  1. get the number of vertices; \n"
        stri += "\t  2. add an edge; \n"
        stri += "\t  3. add a vertex; \n"
        stri += "\t  4. remove an edge; \n"
        stri += "\t  5. remove a vertex; \n"
        stri += "\t  6. check if an edge exists; \n"
        stri += "\t  7. check if a vertex exists; \n"
        stri += "\t  8. get the information attached to an edge; \n"
        stri += "\t  9. modify the information attached to an edge; \n"
        stri += "\t 10. parse the entire graph; \n"
        stri += "\t 11. parse the inbound neighbours of a vertex; \n"
        stri += "\t 12. parse the outbound neighbours of a vertex; \n"
        stri += "\t 13. print the graph; \n"
        return stri

    def run(self):
        print(self.menu())
        running = True
        while running:
            command = int(input(">> "))
            if command == 0:
                print(">> exit...")
                running = False
            elif command == 1:
                print("the number of vertices is:", self.Graph.get_vertices())
            elif command == 2:
                x = int(input("give vertex 1: "))
                if not self.Graph.is_vertex(x):
                    print("there is no such vertex!")
                    continue
                y = int(input("give vertex 2: "))
                if not self.Graph.is_vertex(y):
                    print("there is no such vertex!")
                    continue
                c = int(input("give cost: "))
                if not self.Graph.add(x, y, c):
                    print("the given edge already exists!")
                else:
                    print("edge added successfully")
            elif command == 3:
                x = int(input("give vector: "))
                if not self.Graph.add_vertex(x):
                    print("the given vertex already exists!")
                else:
                    print("vertex", x, "has been added successfully")
            elif command == 4:
                x = int(input("give vertex 1: "))
                if not self.Graph.is_vertex(x):
                    print("there is no such vertex!")
                    continue
                y = int(input("give vertex 2: "))
                if not self.Graph.is_vertex(y):
                    print("there is no such vertex!")
                    continue
                if not self.Graph.remove_Edge(x, y):
                    print("the given edge does not exist!")
                else:
                    print("the edge has been removed successfully")
            elif command == 5:
                x = int(input("give vertex: "))
                if not self.Graph.remove_vertex(x):
                    print("the given vertex does not exist!")
                else:
                    print("the vertex",x,"has been removed")
            elif command == 6:
                x = int(input("give vertex 1: "))
                if not self.Graph.is_vertex(x):
                    print("there is no such vertex!")
                    continue
                y = int(input("give vertex 2: "))
                if not self.Graph.is_vertex(y):
                    print("there is no such vertex!")
                    continue
                if self.Graph.is_edge(x, y):
                    print("the given edge exists")
                else:
                    print("the given edge does not exist")
            elif command == 7:
                x = int(input("give vertex: "))
                if self.Graph.is_vertex(x):
                    print("the given vertex exists")
                else:
                    print("the given vertex does not exist")
            elif command == 8:
                x = int(input("give vertex 1: "))
                if not self.Graph.is_vertex(x):
                    print("there is no such vertex!")
                    continue
                y = int(input("give vertex 2: "))
                if not self.Graph.is_vertex(y):
                    print("there is no such vertex!")
                    continue
                if not self.Graph.get_cost(x, y):
                    print("there is no such edge!")
                else:
                    print(self.Graph.get_cost(x, y))
            elif command == 9:
                x = int(input("give vertex 1: "))
                if not self.Graph.is_vertex(x):
                    print("there is no such vertex!")
                    continue
                y = int(input("give vertex 2: "))
                if not self.Graph.is_vertex(y):
                    print("there is no such vertex!")
                    continue
                new_cost = int(input("give new cost: "))
                if not self.Graph.set_cost(x, y, new_cost):
                    print("there is no such edge!")
                else:
                    print("the cost has been modified successfully")
            elif command == 10:
                print(self.Graph.parse())
            elif command == 11:
                x = int(input("give vertex: "))
                if self.Graph.parse_in(x):
                    print(self.Graph.parse_in(x))
                else:
                    print("there is no such vertex!")
            elif command == 12:
                x = int(input("give vertex: "))
                if self.Graph.parse_out(x):
                    print(self.Graph.parse_out(x))
                else:
                    print("there is no such vertex!")
            elif command == 13:
                self.Graph.pretty_print()
            else:
                print("invalid command!")