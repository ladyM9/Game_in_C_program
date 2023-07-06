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

def search_str(fobj_in): #Funkcija pomoću koje se traži pobjednicki put, odnosno startna pozicija u labirintu i pozicija koja oznacava izlaz iz labirinta
    inFile = open(str(fobj_in), 'r')
    oneLine = inFile.readline()
    
    lista_en = []
    lista = []
    while (len(oneLine) != 0):
        
        
        word = "points=" #U svg fileu koji otvorimo trazimo kljucnu rijec points, jer se nakon te rjeci nalaze tocke koje oznacavaju pobjednicki put tj rjesenje za izlaz iz labirinta
        
        if word in oneLine:

            txt = str(oneLine) #Nakon sto pronademo kljucnu rijec, tu cijelu liniju gdje se ta rijec nalazi spremamo u varijablu txt
            
        oneLine = inFile.readline()

    
    print(txt) 
    startindex = txt.find("points=\"") #zatim trazimo index sa kojom pocinje rijec points
    print(startindex)
    txt = txt[startindex + 8:] #Za ispis podniza koji počinje u sredini niza i ispisuje se do kraja, možemo to učiniti uključivanjem samo broja indeksa ispred dvotočke, ovako:
    print(txt)
    #txt = txt.replace(' ', ';')
    txt = txt.strip() #micemo razmake
    txt = txt.replace("/>", "")
    txt = txt.replace('"', '')
    print(txt)
    lista_en.append(txt.split(' ')) #stavljamo txt u listu i odvajamo tocke, da mozemo lakse naci pocetnu i zavrsnu tocku
    firstpos = parse("{},{}", lista_en[0][0]) #Prva pozicija, lista_en[0][0] to su prvi x i y odnosno startna pozicija kuglice po x osi i po y osi
    startX = firstpos[0] # razdvajanje x i y osi
    startY = firstpos[1]
    print(startX)
    print(startY)
    exitpos = parse("{},{}", lista_en[0][-2]) #zadnjna tocka u labirintu, ujedno i exitLine
    print(exitpos)
    exitX = exitpos[0]
    exitY = exitpos[1]
    exitX1 = (int(exitX) + 2) #rastavljanje na exitX1 i exitX2 jer nama treba linija a ne samo jedna točka odnosno pozicija, pa sam morala pravit liniju
    exitX2 = (int(exitX) - 2)
    exitB = exitY



    inFile.close()

    return startX, startY, exitX1, exitY, exitX2, exitB

def save_h(outFile, lista, scaleX, scaleY, startX, startY,exitX2, exitY, exitX1, exitB ): #funkcija pomocu koje upisujemo parsirani labirint u h file
    
    NameMaze = input("Upisi naziv labirinta: ")
    NameDate = input("Upisi naziv podatka ")
    outFile.write(f"const myline_t {NameMaze}[] = " + "{")

    for i in range(0, len(lista)): #petlja za upis u h file svih linija iz svg filea
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
    outFile.write(f"const myMaze_t {NameDate} = " + "{" )
    outFile.write(f"(myline_t*){NameMaze} " + ",")
    outFile.write("{} , {} ".format(int(float(startX)/scaleX), int(float(startY)/scaleY))) #upis startne pozicije u h file
    outFile.write(" , {")
    outFile.write("{}, {}, {}, {} ".format(int((float(exitX1)/ scaleX)-5) ,int(float(exitY)/scaleY), int((float(exitX2)/ scaleX)+6), int(float(exitB)/scaleY))) #upis zadnje linije u h file
    outFile.write("},")
    outFile.write(f"sizeof({NameMaze}) / sizeof(myline_t)" + "}" + ";")
    outFile.write("\n")
    
   
def headerguide(outFile):
    outFile.write("#ifndef __LAB_H__ \n") #Make header source in open file
    outFile.write("#define __LAB_H__ \n")
    outFile.write('#include "myDefines.h" \n')
    outFile.write('#include "ILI9341_STM32.h" \n')
    
    
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
        startX, startY, exitX1, exitY, exitX2, exitB = search_str(fobj_in)
        save_h(outFile, lista, scaleX, scaleY, startX, startY, exitX1, exitY, exitX2, exitB)
    outFile.write("#endif")
    outFile.close()
    

if __name__ == "__main__":
    main()
    

##credits by Borna Biro



