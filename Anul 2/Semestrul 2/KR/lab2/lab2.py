class NodArbore:
    def __init__(self, info, parinte=None):
        self.info = info
        self.parinte = parinte

    def drumRadacina(self):
        l = []
        nod = self
        while nod is not None:
            l.insert(0, nod)
            nod = nod.parinte
        return l

    def vizitat(self):
        nod = self.parinte
        while nod is not None:
            if nod.info == self.info:
                return True
            nod = nod.parinte
        return False

    def __str__(self):
        return str(self.info)

    def __repr__(self):
        return "({}, ({}))".format(self.info, "->".join([str(x) for x in self.drumRadacina()]))


class Graf:
    def __init__(self, start, scopuri):
        self.start = start
        self.scopuri = scopuri

    def scop(self, infoNod):
        return infoNod in self.scopuri

    def succesori(self, nod):

        def test(m, c):
            return m >= c or m == 0

        l = []
        if nod.info[2] == 1: # malul initial = malul cu barca
            misMalCurent = nod.info[0]
            canMalCurent = nod.info[1]

            misMalOpus = Graf.N - nod.info[0]
            canMalOpus = Graf.N - nod.info[1]
        else:
            misMalOpus = nod.info[0]
            canMalOpus = nod.info[1]

            misMalCurent = Graf.N - nod.info[0]
            canMalCurent = Graf.N - nod.info[1]

        maxMisBarca = min(misMalCurent, Graf.M)
        for mb in range(maxMisBarca+1):
            if mb == 0:
                minCanBarca = 1
                maxCanBarca = min(canMalCurent, Graf.M)
            else:
                minCanBarca = 0
                maxCanBarca = min(canMalCurent, Graf.M - mb, mb)

            for cb in range(minCanBarca, maxCanBarca + 1):
                misMalCurentNou = misMalCurent - mb
                canMalCurentNou = canMalCurent - cb

                misMalOpusNou = misMalOpus + mb
                canMalOpusNou = canMalOpus + cb

                if not test(misMalCurentNou, canMalCurentNou):
                    continue
                if not test(misMalOpusNou, canMalOpusNou):
                    continue

                if nod.info[2] == 1:
                    infoNod = (misMalCurentNou, canMalCurentNou, 0)
                else:
                    infoNod = (misMalOpusNou, canMalOpusNou, 1)

                nodNou = NodArbore(infoNod, nod)
                if not nodNou.vizitat():
                    l.append(nodNou)
        return l


def breadth_first(gr, nsol):
    c = [NodArbore(gr.start)]
    while c:
        nodCurent = c.pop(0)
        if gr.scop(nodCurent.info):
            print(repr(nodCurent))
            nsol -= 1
            if nsol == 0:
                return
        lSuccesori = gr.succesori(nodCurent)
        c += lSuccesori


f = open("input.txt", "r")
continut = f.read().strip().split(" ")

Graf.N = int(continut[0])
Graf.M = int(continut[1])

start = (Graf.N, Graf.N, 1)
scopuri = [(0, 0, 0)]

gr = Graf(start, scopuri)
breadth_first(gr, 1)
