import re
from parse import parse




def parse_svg(fobj_in, displayw, displayh): #displayw i displayh moraju biti argumenti funkcije jer ih funkcija ne vidi inaće
    lista = []
    MyArray = []
    W = []
    w2= []
    Lista_endl = []
    endl = []
    end = []
    
    inFile = open(str(fobj_in), 'r')
    oneLine = inFile.readline()
    while (len(oneLine) != 0):
        oneLine = oneLine.replace("\n", '')
        oneLine = oneLine.replace("\r", '')
        oneLine = oneLine.replace(' ', '')
        MyArray = parse('<linex1="{}"y1="{}"x2="{}"y2="{}"/>',oneLine) #PARSIRANJE ZA LINIJE
        w2 = parse('<svgwidth="{}"height="{}"version="1.1"xmlns="http://www.w3.org/2000/svg">', oneLine) #PARSIRANJE ZA DULJINU I ŠIRINU LABIRINTA
        #Lista_endl = parse('<polylinefill="none"stroke="#ff0000"stroke-width="2"stroke-linecap="square"stroke-linejoin="round"points="{}"/>', oneLine)
        if MyArray != None: #ako argument iz liste je broj, taj argument stavi u listu
            lista.append(list(MyArray))
        if w2 != None: 
            W.append(list(w2))
        #if Lista_endl != None: #ako argument iz liste je broj, taj argument stavi u listu
            #endl.append(Lista_endl)
        
        oneLine = inFile.readline()  #čitaj liniju po liniju u fobj_in
    
   # print(endl)
    for i in range(0, len(W)): #petlja za širinu i duljinu labirinta
        width = (W[i][0])
        height = (W[i][1])
    print(width)
    print(height)
    scaleX = int(width)/displayw 
    scaleY = int(height)/displayh
    print(scaleX)
    print(scaleY)


    inFile.close()  #zatvaranje filea za čitanje

    return lista, W, scaleX, scaleY

def search_str(fobj_in):
    inFile = open(str(fobj_in), 'r')
    oneLine = inFile.readline()
    
    lista_en = []
    lista = []
    while (len(oneLine) != 0):
        word = "points="
        
        if word in oneLine:
            e = oneLine.index(word)
            print(e)
            lista_en.append(oneLine)
            
            
        oneLine = inFile.readline()
    brojač = 0
    for i in str(word):
        brojač+=1
    print(brojač)
    n = e+brojač
    print(lista_en)
    print(lista_en[1])

    print(lista_en)
    

    
    
        
    


    inFile.close()

def save_h(outFile, lista, scaleX, scaleY):
    
    NameMaze = input("Upisi naziv labirinta: ")
    outFile.write(f"const myline_t {NameMaze} " + "{")

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
    outFile.write("\n")
   
def headerguide(outFile):
    outFile.write("#ifndef __LAB_H__ \n") #Make header source in open file
    outFile.write("#define __LAB_H__ \n")
    outFile.write("#include 'myDefines.h' \n")
    
    
def main():

    displayw = 319
    displayh = 239
    numberMaze = int(input("Upisi koliko zelis imati labirinteva "))
    fobj_out = input("Upisi gdje zelis da ti se spremi skalirani labirint ")
    outFile = open(fobj_out, 'w')
    outFile.write("\n")
    headerguide(outFile)
    
    
    
    for i in range(0, numberMaze):
        
        fobj_in = input("Upisi svg file ") #u ovom fileu su tvoji labirintevi dakle taj file ČITAŠ
        lista,W, scaleX, scaleY = parse_svg(fobj_in, displayw, displayh)
        save_h(outFile, lista, scaleX, scaleY)
        search_str(fobj_in)
    outFile.write("#endif")
    outFile.close()
    

if __name__ == "__main__":
    main()
    

##credits by Borna Biro



