import re



def funkcija1():

    fobj_in = open("labirint_proba.txt", 'r')
    fobj_out = open("maze22.txt", 'w')
    search_text = "<line"
    search_text1 = "x1="
    search_text2 = "y1="
    search_text3 = "x2="
    search_text4 = "y2="

    search_text5 = "\" "
    search_text6 = "=\""
    search_text7 = "<"
    search_text8 = "/>"
    replaced_text = ""
    replaced_text1 = ", "
    lista = []
    lista2 = []

    
    
    #search_text9 = "</g>"
    #search_text10 = " "
    #replaced_text = "["
    #replaced_text2 = ","
    #replaced_text3 = ""
    #replaced_text4 = "],"
    #replaced_text5 = "const myline_t lab1[][]=["
    #replaced_text6 = "]"
    with open(r'labirint_proba.txt', 'r') as file:
        data = fobj_in.read()
        data = data.replace(search_text, replaced_text)
        data = data.replace(search_text1, replaced_text)
        data = data.replace(search_text2, replaced_text)
        data = data.replace(search_text3, replaced_text)
        data = data.replace(search_text4, replaced_text1)
        data = data.replace(search_text5, replaced_text)
        data = data.replace(search_text6, replaced_text)
        data = data.replace(search_text7, replaced_text)
        data = data.replace(search_text8, replaced_text)
        #data = data.replace(search_text9, replaced_text3)
    
        out = re.findall(r'\d+', data)
        lista = []
        i = 21
        j = 65
        
        a = int
       # i = int(i)
        
    #with open(r'maze22.txt' , 'w') as file:
     #   file.write(str(out[i]*2))
        #lista.append(str(data[21]) + " " + str(data[22])+ " "  +  str(data[23]) +" "+ str(data[24]))
        #lis = lista.split()
       # for i in range(i, j,1):
            
        a = (str(int(out[21])*2) + " " + str(int(out[22])*2)+ " "  +  str(int(out[23])*2) +" "+ str(int(out[24])*2))
        print(a)

        
       
        
        
        
        #for el in lista:
         #   lista2.append(int(el))
        #print(lista2)
    fobj_in.close()
    fobj_out.close()

def funkcija2():
    lista = []
    fobj_in = open("maze22.txt", 'r')
    fobj_out = open("maze3.txt", 'w')
    with open(r'maze22.txt', 'r') as file:
        y = int
        d = fobj_in.readlines()
        lista.append(d)
        
        
        
        for i in range(0, len(lista)):
            lista[i] =  str(lista[i])
        print(lista)
        
               

    """
        data = fobj_in.read()
        lista = [data]
        lista = [float(0.7625*x) for x in L]
    with open(r'maze3.txt' , 'w') as file:
        file.write(str(L))

    """
    fobj_in.close()
    fobj_out.close()


funkcija1()
#funkcija2()



        
