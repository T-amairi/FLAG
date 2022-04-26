#!/usr/bin/env python3

# Tahar AMAIRI & Hamza RAIS
# MAIN4 Polytech Sorbonne
# To print execution time improvement due to compiler optimization
# FLAG : [Implementation project]

import csv

fLU = open("./archive/without optimization flags/LU.csv","r")
fInvStr_str = open("./archive/without optimization flags/InvStr_str.csv","r")
fInvStr_naive = open("./archive/without optimization flags/InvStr_naive.csv","r")
fProd_naive = open("./archive/without optimization flags/Prod_naive.csv","r")
fProd_str = open("./archive/without optimization flags/Prod_str.csv","r")

fLU_opt = open("./archive/with optimization flags/LU.csv","r")
fInvStr_str_opt = open("./archive/with optimization flags/InvStr_str.csv","r")
fInvStr_naive_opt = open("./archive/with optimization flags/InvStr_naive.csv","r")
fProd_naive_opt = open("./archive/with optimization flags/Prod_naive.csv","r")
fProd_str_opt = open("./archive/with optimization flags/Prod_str.csv","r")

def importData(f):
    d = dict()
    reader = csv.reader(f, delimiter = ';')
    for row in reader:
        d[int(row[0])] = float(row[1])
    return d

LU = importData(fLU)
InvStr_str = importData(fInvStr_str)
InvStr_naive = importData(fInvStr_naive)
Prod_naive = importData(fProd_naive)
Prod_str = importData(fProd_str)

LU_opt = importData(fLU_opt)
InvStr_str_opt = importData(fInvStr_str_opt)
InvStr_naive_opt = importData(fInvStr_naive_opt)
Prod_naive_opt = importData(fProd_naive_opt)
Prod_str_opt = importData(fProd_str_opt)

L = list()
L.append((LU,LU_opt))
L.append((InvStr_naive,InvStr_naive_opt))
L.append((InvStr_str,InvStr_str_opt))
L.append((Prod_naive,Prod_naive_opt))
L.append((Prod_str,Prod_str_opt))
methods = ["LU","Strassen inversion + naive product","Strassen inversion + Strassen product","Naive product","Strassen product"]

for i in range(len(L)):
    d = L[i][0]
    d_opt = L[i][1]
    tmp = 0.0
    ctr = 0
    for k in d.keys():
        if d[k]:
            tmp  += ((d_opt[k] - d[k]) / abs(d[k])) * 100
            ctr += 1
    tmp = tmp / ctr 
    print("{} : {}%".format(methods[i],tmp))

fLU.close()
fInvStr_str.close()
fInvStr_naive.close()
fProd_naive.close()
fProd_str.close()

fLU_opt.close()
fInvStr_str_opt.close()
fInvStr_naive_opt.close()
fProd_naive_opt.close()
fProd_str_opt.close()