import re



def funkcija1():

    fobj_in = open("labirint_2.txt", 'r')
    fobj_out = open("labirint.h", 'w')
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
    with open(r'labirint_2.txt', 'r') as file:
        data = fobj_in.read()
        data = data.replace(search_text, replaced_text)
        data = data.replace(search_text1, replaced_text)
        data = data.replace(search_text2, replaced_text)
        data = data.replace(search_text3, replaced_text)
        data = data.replace(search_text4, replaced_text)
        data = data.replace(search_text5, replaced_text)
        data = data.replace(search_text6, replaced_text)
        data = data.replace(search_text7, replaced_text)
        data = data.replace(search_text8, replaced_text)
        #data = data.replace(search_text9, replaced_text3)
    
        #out1 = re.findall(r'\d+', data1)
        #out2 = re.findall(r'\d+', data2)
        #out3 = re.findall(r'\d+', data3)
        #out4 = re.findall(r'\d+', data4)
        out = re.findall(r'\d+', data)
        lista = []
        i = 21
        j = 22
        i2 =23
        j2 = 24
        
        a = int
        b = int

    while i <= 295 and j <= 296 and i2 <= 297 and j2 <= 298 :
            
           
            a = ("{" + str(int(out[i])/0.71473) + ", " + str(int(out[j])/0.619246) + ", "+ str(int(out[i2])/0.71473)+ ", " + str(int(out[j2])/0.61924) + "},")
            print(a)
            lista.append(a)
            i+=4
            j+=4
            i2+=4
            j2+=4
            
            

            with open(r'labirint.h' , 'w') as file:
                file.write("const myline_t lab[80] = ")
                file.write(str(lista))

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
        
               

    
        data = fobj_in.read()
        lista = [data]
        lista = [float(0.7625*x) for x in L]
    with open(r'maze3.txt' , 'w') as file:
        file.write(str(L))


    fobj_in.close()
    fobj_out.close()


funkcija1()
#funkcija2()



        
