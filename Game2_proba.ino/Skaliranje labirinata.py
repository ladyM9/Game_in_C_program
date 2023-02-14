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
        a1 = 318
        a2 = 319
        a3 = 320
        a4 = 321
        a5 = 584
        a6 = 585
        a7 = 586
        a8 = 587
        b1 = 850
        b2 = 851
        b3 = 852
        b4 = 853
        
        a = int
        b = int
        print(out)
    with open(r'labirint.h' , 'w') as file:  #open file  
        file.write("#ifndef __LABIRINT_H__ \n") #Make header source in open file
        file.write("#define __LABIRINT_H__ \n")
        file.write("#include 'defines.h' \n")
        
        file.write("const myline_t lab1[80] = { ")
        while i <= 292 and j <= 293 and i2 <= 294 and j2 <= 295 : #sve dok ne dođeš do zadnje linije u labirintu
            
                a = ("{" + str(int(out[i])/0.71473) + ", " + str(int(out[j])/0.619246) + ", " + str(int(out[i2])/0.71473) + ", " + str(int(out[j2])/0.619246) + "},") #svaki x,y,x1 i y1 podijeli, tako radim resize
                #file.write("const myline_t lab[80] = ")
                file.write(str(a))
                i+=4
                j+=4
                i2+=4
                j2+=4
                
        file.write("\nconst myline_t lab2[80] = { ")
        while a1 <= 558 and a2 <= 559 and a3 <= 560 and a4 <= 561:
                b = ("{" + str(int(out[a1])/0.71473) + ", " + str(int(out[a2])/0.619246)+ ", " + str(int(out[a3])/0.71473)+ ", " + str(int(out[a4])/0.619246) + "},")
                file.write(str(b))
                a1+=4
                a2+=4
                a3+=4
                a4+=4

        file.write("\nconst myline_t lab4[80] = { ")
        while a5 <= 824 and a6 <= 825 and a7 <= 826 and a8 <= 827:
                b = ("{" + str(int(out[a5])/0.71473) + ", " + str(int(out[a6])/0.619246)+ ", " + str(int(out[a7])/0.71473)+ ", " + str(int(out[a8])/0.619246) + "},")
                file.write(str(b))
                a5+=4
                a6+=4
                a7+=4
                a8+=4

        file.write("\nconst myline_t lab5[80] = { ")
        while b1 <= 1056 and b2 <= 1057 and b3 <= 1058 and b4 <= 1059:
                b = ("{" + str(int(out[b1])/0.71473) + ", " + str(int(out[b2])/0.619246)+ ", " + str(int(out[b3])/0.71473)+ ", " + str(int(out[b4])/0.619246) + "},")
                file.write(str(b))
                b1+=4
                b2+=4
                b3+=4
                b4+=4
        

        file.write("\nconst lab3[] = {{170,229,140,230}};\n")

                
        file.write("\nconst myline_t *labirint[] = {lab1, lab2, lab4, lab5};\n")
        file.write("\nconst myline_t *p[] = {lab3};\n")
        file.write("const int labElements[] = {(sizeof(lab1) / sizeof(myline_t)), (sizeof(lab2) / sizeof(myline_t)), (sizeof(lab4) / sizeof(myline_t)), (sizeof(lab5) / sizeof(myline_t))};\n")
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




        
