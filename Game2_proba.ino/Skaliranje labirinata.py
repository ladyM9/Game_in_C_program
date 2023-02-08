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
        
        out = re.findall(r'\d+', data)
        lista = []
        lista2 = []
        i = 21
        j = 22
        i2 =23
        j2 = 24
        
        a = int
        b = int
    with open(r'labirint.h' , 'w') as file:  #open file
        file.write("#ifndef __LABIRINT_H__ \n") #Make header source in open file
        file.write("#define __LABIRINT_H__ \n")
        file.write("#include 'defines.h' \n")
        
        file.write("const myline_t lab1[80] = ")
        while i <= 295 and j <= 296 and i2 <= 297 and j2 <= 298 : 
            
                a = ("{" + str(int(out[i])/0.71473) + ", " + str(int(out[j])/0.619246) + ", " + str(int(out[i2])/0.71473) + ", " + str(int(out[j2])/0.619246) + "},")
                #file.write("const myline_t lab[80] = ")
                file.write(str(a))
                i+=4
                j+=4
                i2+=4
                j2+=4
        file.write("\nconst myline_t *labirint[] = {lab1, lab2};\n")
        file.write("const int labElements[] = {(sizeof(lab1) / sizeof(myline_t)), (sizeof(lab2) / sizeof(myline_t))};\n")
        file.write("#endif")


    '''
    while i <= 295 and j <= 296 and i2 <= 297 and j2 <= 298 :

        #a = str(int(out[i])/0.71473)
        #v = ' '
        #b = str(int(out[j])/0.619246)
        #c = str(int(out[i2])/0.71473)
        #d = str(int(out[j2])/0.61924)
               
        a = ("{" + str(int(out[i])/0.71473) + ", " + str(int(out[j])/0.619246) + ", "+ str(int(out[i2])/0.71473)+ ", " + str(int(out[j2])/0.619246)+  "}," )
        x = re.findall(r'\d+', a)
        lista.append(x)
        
        

        i+=4
        j+=4
        i2+=4
        j2+=4
            
            

    '''
    fobj_in.close()
    fobj_out.close()


funkcija1()




        
