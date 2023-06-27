import re
from parse import parse

lista = []
MyArray = []
W = []
w2= []
displayw = 319
displayh = 239




fobj_in = input("Upisi svg file ") #u ovom fileu su tvoji labirintevi dakle taj file ČITAŠ
fobj_out = input("Upisi gdje zelis da ti se spremi skalirani labirint ")
NameMaze = input("Upisi naziv labirinta: ")

inFile = open(str(fobj_in), 'r')
oneLine = inFile.readline()
while (len(oneLine) != 0):
    oneLine = oneLine.replace("\n", '')
    oneLine = oneLine.replace("\r", '')
    oneLine = oneLine.replace(' ', '')
    MyArray = parse('<linex1="{}"y1="{}"x2="{}"y2="{}"/>',oneLine)
    w2 = parse('<svgwidth="{}"height="{}"version="1.1"xmlns="http://www.w3.org/2000/svg">', oneLine)
    if MyArray != None:
        lista.append(list(MyArray))
    if w2 != None:
        W.append(list(w2))
        
    oneLine = inFile.readline()

for i in range(0, len(W)):
    width = (W[i][0])
    height = (W[i][1])
print(width)
print(height)
scaleX = int(width)/displayw
scaleY = int(height)/displayh
print(scaleX)
print(scaleY)
inFile.close()   
print(lista)

outFile = open(fobj_out, 'w')
outFile.write(f"const myline_t {NameMaze}[] = " + "{")

for i in range(0, len(lista)):
    outFile.write("{")
    outFile.write("{}, {}, {}, {}".format(
        int(float(lista[i][0])/scaleX),
        int(float(lista[i][1])/scaleY),
        int(float(lista[i][2])/scaleX),
        int(float(lista[i][3])/scaleY)
        ))
    outFile.write("}")
    if i != (len(lista) - 1):
        outFile.write(", ")
outFile.write("};")
outFile.close()

##credits by Borna Biro



