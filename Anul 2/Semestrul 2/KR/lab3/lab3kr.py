class State:
  N = 3
  M = 2

  def __init__(self, misionari = N, canibali = N, barca = -1):
    ''' Constructorul clasei State.

    :param misionari: cati misionari sunt pe malul stang
    :param canibali: cati canibali sunt pe malul stang
    :param barca: -1 daca se afla pe malul stang, 1 altfel
    '''
    self.misionari = misionari
    self.canibali = canibali
    self.barca = barca

  def __eq__(self, cls):
     return self.barca == cls.barca and \
     self.misionari == cls.misionari and self.canibali == cls.canibali

  def __str__(self):
    return 'Stare curenta:\n' + \
    f'{str(self.misionari)} misionari, ' + \
    f'{str(self.canibali)} canibali | ' + \
    f'{str(self.N - self.misionari)} misionari, ' + \
    f'{str(self.N - self.canibali)} canibali \n' + \
    f'Barca se afla pe malul {"stang" if self.barca == -1 else "drept"}\n'

  def __repr__(self):
    return ('({} {} {})').format(self.misionari, self.canibali, self.barca)

  def succesori(self):
    ''' Calculeaza lista succesorilor directi ai starii curente. 
    
    :return: lista starilor admisibile
    '''
    succesori = []

    # Calculez cati misionari si canibali sunt pe malul cu barca
    misionari = self.misionari if self.barca == -1 else self.N - self.misionari
    canibali = self.canibali if self.barca == -1 else self.N - self.canibali

    for locuri in range(1, self.M + 1):
      for locuriMisionari in range(misionari + 1):
        if locuriMisionari > locuri:
          continue

        # Verific sa existe cati canibali vreau sa plimb
        locuriCanibali = locuri - locuriMisionari
        if locuriCanibali < 0 or locuriCanibali > canibali:
          continue

        # Verific sa nu fie mancati misionari in barca
        if locuriCanibali > locuriMisionari and locuriMisionari > 0:
          continue

        # Verific sa nu fie mancati misionari pe malul de plecare
        if canibali - locuriCanibali > misionari - locuriMisionari and \
        misionari - locuriMisionari > 0:
          continue
        
        # Verific sa nu fie mancati misionari pe malul de sosire
        if (self.N - canibali) + locuriCanibali > \
        (self.N - misionari) + locuriMisionari and \
        (self.N - misionari) + locuriMisionari > 0:
          continue

        # Trucuri de notatie:
        stareCurenta = State(
            self.misionari + self.barca * locuriMisionari, 
            self.canibali + self.barca * locuriCanibali, 
            (-1) * self.barca)

        succesori.append(stareCurenta)

    return succesori

f = open("input.txt", "r")
State.N = int(f.readline())
State.M = int(f.readline())
f.close()

state = State(State.N, State.N, -1)
print(state)

#1

class Node:
  def __init__(self, informatie, parinte = None, g=0, h=0):
    self.informatie = informatie
    self.parinte = parinte
    self.g = g
    self.h = h
    self.f = g+h

  def __str__(self):
    return str(self.informatie)

  def __repr__(self):
    return "({}, ({}), cost: {})".format(self.informatie, "->".join([ str(x) for x in self.drumRadacina()]), self.f)

  def __eq__(self, other):
    return self.informatie == other.informatie and self.f == other.f

  def __le__(self, other):
    return self.f <= other.f

  def drumRadacina(self):
    drum =[]
    nod = self
    while nod is not None:
      drum.append(nod)
      nod = nod.parinte
    return reversed(drum)

  def vizitat(self):
    nod = self.parinte
    while nod is not None:
      if nod.informatie == self.informatie:
        return True
      nod = nod.parinte
    return False

#1
class Graph:
  def __init__(self, matrix, noduriStart, noduriScop, estimari):
    ''' Constructorul clasei Graf. '''
    self.nodStart =noduriStart
    self.noduriScop = noduriScop
    self.estimari = estimari
    self.matrix = matrix

  def scop(self, informatieNod):
    ''' Primeste o informatie de tip Nod si verifica daca e scop.

    :param informatieNod: informatia nodului de cautat
    :return: True daca nodul e scop, False altfel
    '''
    return informatieNod in self.noduriScop

  def estimeaza_h(self, nod):
    return self.estimari[nod.informatie]

  def succesori(self, nod):
    l = []
    for i in range(len(self.matrix)):
      if self.matrix[nod.informatie][i] != 0:
        nodNou = Node(i, nod, nod.g+self.matrix[nod.informatie][i], self.calculeaza_h(i))
        if not nodNou.vizitat():
          l.append(nodNou)

    return l

  def calculeaza_h(self, informatieNod):
    return self.estimari[informatieNod]

#2
#BFS il vom inlocui cu aStarSolMultiple

def binary_search(listaNoduri, nodNou, st, dr):
   if len(listaNoduri)==0:
       return 0
   if st==dr:
       if nodNou.f<listaNoduri[st].f:
           return st
       elif nodNou.f>listaNoduri[st].f:
           return dr+1
       else: # f-uri egale
           if nodNou.g < listaNoduri[st].g:
               return dr + 1
           else:
               return st
   else:
       mij=(st+dr)//2
       if nodNou.f<listaNoduri[mij].f:
           return binary_search(listaNoduri, nodNou, st, mij)
       elif nodNou.f>listaNoduri[mij].f:
           return binary_search(listaNoduri, nodNou, mij+1, dr)
       else:
           if nodNou.g < listaNoduri[mij].g:
               return binary_search(listaNoduri, nodNou, mij + 1, dr)
           else:
               return binary_search(listaNoduri, nodNou, st, mij)



def aStarSolMultiple(graf, n):
  coada = [Node(graf.nodStart)]
  while coada:
    nod = coada.pop(0)
    if graf.scop(nod.informatie):
      print(repr(nod))
      n-=1
      if n == 0:
        return
    drum = graf.succesori(nod)
    for s in drum:
      i = binary_search(coada, s, 0, len(coada)-1)
      if i == len(coada):
        coada.append(s)
      else:
        coada.insert(i, s)

m = [
    [0, 3, 5, 10, 0, 0, 100],
    [0, 0, 0, 4, 0, 0, 0],
    [0, 0, 0, 4, 9, 3, 0],
    [0, 3, 0, 0, 2, 0, 0],
    [0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 4, 0, 5],
    [0, 0, 3, 0, 0, 0, 0],
]

start =0
NodScop = [4,6]
h = [0, 1, 6, 2, 0, 3, 0]

graf = Graph(m, start, NodScop, h)
aStarSolMultiple(graf, 3)

#3 priority_queue

import heapq

class PriorityQueue:
  def __init__(self):
    self.heap = []

  def push(self, item):
    heapq.heappush(self.heap, item)

  def pop(self):
    return heapq.heappop(self.heap)

  def __len__(self):
    return len(self.heap)

  def __str__(self):
    return str(self.heap)




def aStarSolMultiple_priority(graf, n):
  coada = PriorityQueue()
  for nodStart in graf.nodStart:
    coada.push(Node(nodStart, None, 0, graf.estimeaza_h(Node(nodStart))))

  solutii = []
  while len(coada) > 0 and len(solutii) < n:
    nodCurent = coada.pop()
    if graf.scop(nodCurent.informatie):
      solutii.append(nodCurent)
    else:
      succesori = graf.succesori(nodCurent)
      for succesor in succesori:
        coada.push(succesor)

  return solutii

#4 A* dupa pseudocod 

def BFS(graf, n):
  coada = [Node(graf.nodStart)]
  while coada:
    nod = coada.pop(0)
    if graf.scop(nod.informatie):
      # If we've reached the goal node, reconstruct the path and return it
      path = [nod]
      while nod.parinte:
        nod = nod.parinte
        path.insert(0, nod)
      return path
    drum = graf.succesori(nod)
    for succesor in drum:
      succesor.parinte = nod  # Set the parent of the successor node to the current node
    coada += drum
    n -= 1
    if n == 0:
      return None  # If we've explored n nodes and haven't found the goal, return None



def expandeaza_nodul_curent(nod_curent, graf):
    """
    Funcție care expandează nodul curent și returnează o listă cu toți succesori săi validați.
    """
    succesori = graf.succesori(nod_curent)
    valid_succesori = []
    for succesor in succesori:
        l= graf.succesori(nod_curent)
        if succesor not in l:
            valid_succesori.append(succesor)
    return valid_succesori




def a_star(graf):
    open_list = [start]  
    closed_list = []     
    
    while open_list:
      nodCurent = open_list.pop(0)
      closed_list.append(nodCurent)

      if nodCurent in NodScop:
         BFS(graf, len(graf[nodCurent]))
         return

      succesori = expandeaza_nodul_curent(nodCurent, graf)


      for successor in succesori(nodCurent):
        nodNou = None
        if successor in open_list:
            if successor.f < nodCurent.f or (successor.f == nodCurent.f and successor.g > nodCurent.g):
              open_list.pop(nodCurent)
              nodNou = successor
        elif successor in closed_list:
           if successor.f < nodCurent.f or (successor.f == nodCurent.f and successor.g > nodCurent.g):
              closed_list.pop(nodCurent)
              nodNou = successor

        else:
          nodNou = successor
            
        if nodNou is not None:
          for i, nod in enumerate(open_list):
            if nodNou.f < nod.f or (nodNou.f == nod.f and nodNou.g > nod.g):
              open_list.insert(i, nodNou)
              return
          open_list.append(nodNou)
