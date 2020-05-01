
class RootedTree:
    def __init__(self, root):
        self._root=root
        self._children={root:[]}
        self._parent={root:None}
    def add_child(self,vertex,new_vertex):
        #adds new_vertex as child of vertex
        self._children[vertex].append(new_vertex)
        self._children[new_vertex]=[]
        self._parent[new_vertex]=vertex
        
        
    def get_children(self,vertex):
        #this function returns a generator that enumerates the children of a given vertex 
        return self._children[vertex][:]
    
    def is_vertex(self,vertex):
        #true or false
        return vertex in self._children.keys()
    
    def get_parent(self,vertex):
        #return the parent vertex of a given vertex
        #if the vertex is the root, return None
        return self._parent[vertex]
    def get_root(self):
        #returns the root of the graph
        return self._root
    
    def printSubTree(self,root,spaces):
        print ('\t'*spaces,root)
        for child in self._children[root]:
            self.printSubTree(child,spaces+1)
            
    def printTree(self):
        self.printSubTree(self._root, 0)

def bfs(graph,Vertex):
    '''
    returns the tree corresponding to the bfs from the start vertex
    '''
    queue=[Vertex]
    tree= RootedTree(Vertex)
    
    while queue !=[]:
        currVertex=queue.pop(0)
        children=graph.parse_in(currVertex)
        for vertex in children:
            if not tree.is_vertex(vertex):
                tree.add_child(currVertex, vertex)
                queue.append(vertex)
    return tree
def getPath(tree,targetVertex):
    if not tree.is_vertex(targetVertex):
        return None
    path=[]
    currVertex=targetVertex
    while currVertex!=None:
        path.append(currVertex)
        parent=tree.get_parent(currVertex)
        currVertex=parent
    path.reverse()
    return path

def dfs_util(g, currentVertex, tree):
    children = g.parse_out(currentVertex)
    for nextVertex in children:
        if not tree.is_vertex(nextVertex):
            tree.add_child(currentVertex, nextVertex)
            dfs_util(g,  nextVertex, tree)
            
def dfs2(g, startVertex):
    '''Returns the tree corresponding to the DFS from the start vertex
    '''
    tree = RootedTree(startVertex)
    dfs_util(g, startVertex, tree)
    return tree