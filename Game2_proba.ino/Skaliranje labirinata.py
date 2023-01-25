


def funkcija1():

    fobj_in = open("maze.txt", 'r')
    fobj_out = open("maze22.txt", 'w')
    search_text = "<line"
    search_text1 = "x1="
    search_text2 = "y1="
    search_text3 = "x2="
    search_text4 = "y2="
    search_text5 = "/>"
    search_text6 = '"'
    search_text7 = "\n"
    search_text8 = "<g fill="
    search_text9 = "</g>"
    search_text10 = " "
    replaced_text = "["
    replaced_text2 = ","
    replaced_text3 = ""
    replaced_text4 = "],"
    replaced_text5 = "const myline_t lab1[][]=["
    replaced_text6 = "]"
    with open(r'maze.txt', 'r') as file:
        data = fobj_in.read()
        data = data.replace(search_text, replaced_text3)
        data = data.replace(search_text1, replaced_text3)
        data = data.replace(search_text2, replaced_text2)
        data = data.replace(search_text3, replaced_text2)
        data = data.replace(search_text4, replaced_text2)
        data = data.replace(search_text5, replaced_text3)
        data = data.replace(search_text6, replaced_text3)
        data = data.replace(search_text7, replaced_text2)
        data = data.replace(search_text8, replaced_text3)
        data = data.replace(search_text9, replaced_text3)
    
    

    with open(r'maze22.txt' , 'w') as file:
        file.write(data)
    

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
            lista[i] =  str(lista[i]*2)
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
funkcija2()



        
