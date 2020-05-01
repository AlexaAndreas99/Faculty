from random import randint
from copy import deepcopy
from program.RootedTree import *

def createRandomGraph(n,m):
    graph=Graph(n)
    for i in range(m):
        x=randint(0,n-1)
        y=randint(0,n-1)
        c=randint(-n,n)
        while not graph.add(x, y, c):
            x=randint(0,n-1)
            y=randint(0,n-1)
        graph.add(x, y, c)
    return graph
def ford(s,t):
    g=Graph()
    #g.pretty_print()
    dist={}
    prev={}
    for x in g.parse():
        dist[x]=999
    dist[s]=0
    changed=True
    i=1
    while changed and i<g.get_vertices():
        changed=False
        for (x,y) in g.parse_edges():
            if dist[y]>dist[x]+g.get_cost(x, y):
                dist[y]=dist[x]+g.get_cost(x, y)
                prev[y]=x
                changed=True
        i+=1
        
    if dist[t]==999:
        print("there is no road from",s ,"to", t)
    else:
        print(dist[t])
        print(s)
        for i in prev:
            print(i)
        
    
class Graph():
    def __init__(self,n=0):
        self._in={}
        self._out={}
        self._cost={}
        self._edges=0
        self._vertices=n
        if(n==0):
            self.read()
        else:
            for vertex in range(self._vertices):
                self._out[vertex]=[]
                self._in[vertex]=[]
    '''
    creates an edge
    input: two vertices and the cost
    output: false if the edge exists, true otherwise
    ''' 
    def add(self,a,b,c):
        if self.is_edge(a,b):
            return False
            
        self._out[a].append(b)
        self._in[b].append(a)
        
        t=(a,b)
        self._cost[t]=c
        return True
    

    #returns the number of verices
    def get_vertices(self):
        return self._vertices
    def read(self):
        f=open("graph1.txt","r")
        line=f.readline()
        tok=line.split( )
        n=int(tok[0])
        m=int(tok[1].strip())
        self._vertices=n;
        self._edges=m;
        
        for vertex in range(self._vertices):
            self._out[vertex]=[]
            self._in[vertex]=[]
        i=m
        while i:
            line=f.readline()
            tok=line.split( )
            self.add(int(tok[0]), int(tok[1]), int(tok[2].strip()))
            i-=1
        f.close()
    
    '''
    input: a vertex
    output: true if the vertex exists,false otherwise
    '''
    def is_vertex(self,x):
        if x in self.parse():
            return True
        return False
    def parse(self):
        return list(self._in.keys())
    def parse_edges(self):
        return list(self._cost.keys())
    
    def parse_in(self,x):
        if self.is_vertex(x):
            return self._in[x]
        return False
    
    def parse_out(self,x):
        if self.is_vertex(x):
            return self._out[x]
        return False
    
    def pretty_print(self):
        for vertex in self.parse():
            string=str(vertex)+"->"
            for neigh in self.parse_out(vertex):
                string+=str(neigh)+" "
            print(string)
    
    #verifies if an edge exists 
    def is_edge(self,a,b):
        return b in self._out[a]
    
    '''
    removes an edge
    input: two vertices
    output: false if the edge does not exist,true if removed succesfully
    '''
    def remove_edge(self,a,b):
        if self.is_edge(a,b)==0:
            return False
        
        self._in[b].remove(a)
        self._out[a].remove(b)
        del self._cost[(a,b)]
        return True
    
    '''
    adds a vertex
    input: a vertex
    output: true if the vertex is added,false otherwise
    ''' 
    def add_vertex(self,x):
        if self.is_vertex(x)==False:
            self._vertices+=1
            self._out[x]=[]
            self._in[x]=[]
            return True
        return False
    '''
    removes a vertex and all its edges
    input: a vertex
    output: true if the vertex exists and it is removed,false otherwise
    '''
    def remove_vertex(self,x):
        
        if self.is_vertex(x):
            self._vertices-=1
            del self._in[x]
            del self._out[x]
        
            for vertex in self.parse():
                if x in self._in[vertex]:
                    self._in[vertex].remove(x)
                if x in self._out[vertex]:
                    self._out[vertex].remove(x)
            
                if (x,vertex) in self._cost.keys():
                    del self._cost[(x,vertex)]
                    
                if (vertex,x) in self._cost.keys():
                    del self._cost[(vertex,x)]
            return True
        return False
        
    
    def out_deg(self,a):
        if a in self._out.keys():
            return len(self._out[a])
        return False
    
    def in_deg(self,a):
        if a in self._in.keys():
            return len(self._in[a])
        return False
    def get_cost(self,a,b):
        if self.is_edge(a, b):
            return  self._cost[(a,b)]
        return False
    def set_cost(self,a,b,x):
        if self.is_edge(a, b):
            self._cost[(a,b)]=x
        return False
    def copy(self):
        return deepcopy(self)
class UI:
    def __init__(self):
        self.Graph = Graph()

    @staticmethod
    def menu():
        stri = ""
        stri += "0. exit; \n"
        stri += "1. get the number of vertices; \n"
        stri += "2. add an edge; \n"
        stri += "3. add a vertex; \n"
        stri += "4. remove an edge; \n"
        stri += "5. remove a vertex; \n"
        stri += "6. check if an edge exists; \n"
        stri += "7. check if a vertex exists; \n"
        stri += "8. get the information attached to an edge; \n"
        stri += "9. modify the information attached to an edge; \n"
        stri += "10. parse the entire graph; \n"
        stri += "11. parse the inbound neighbours of a vertex; \n"
        stri += "12. parse the outbound neighbours of a vertex; \n"
        stri += "13. print the graph; \n"
        stri+= "14. get the lowest lenght path between 2 vertices; \n"
        return stri

    def run(self):
        print(self.menu())
        running = True
        while running:
            command = int(input(">> "))
            if command == 0:
                print(">> exit")
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
                x = int(input("give vertex: "))
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
                if not self.Graph.remove_edge(x, y):
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
            elif command==14:
                x = int(input("give vertex 1: "))
                if not self.Graph.is_vertex(x):
                    print("there is no such vertex!")
                    continue
                y = int(input("give vertex 2: "))
                if not self.Graph.is_vertex(y):
                    print("there is no such vertex!")
                    continue

                tree=bfs(self.Graph,y)
                tree.printTree()
                print(getPath(tree,x))
                
            else:
                print("invalid command!")
#g=createRandomGraph(2, 4)
def recToposort(g, v, sorted, fullyProcessed, visited):
    visited.add(v)
    for vertex in g.parse_in(v):
        if vertex in visited and vertex not in fullyProcessed:
            return False
        if vertex not in fullyProcessed:
            ok = recToposort(g, vertex, sorted, fullyProcessed, visited)
            
            if not ok:
                return False
    
    sorted.append(v)
    fullyProcessed.add(v)
    return True
    

def toposort(g):
    '''Returns the list of vertices in g, in topological sorting order
    Returns None if g contains cycles
    '''
    sorted = []
    fullyProcessed = set()
    visited = set()
    
    for v in g.parse():
        if v not in visited:
            ok = recToposort(g, v, sorted, fullyProcessed, visited)
            if not ok:
                return None
                
    return sorted

ui=UI()
#ui.run()
g=Graph()
#dfs2(g, 5).printTree()
#print(dfs2(g, 5)._children)
ford(0,2)