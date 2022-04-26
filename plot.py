#!/usr/bin/env python3

# Tahar AMAIRI & Hamza RAIS
# MAIN4 Polytech Sorbonne
# FLAG : [Implementation project]
# To export the results into plots 

from matplotlib import pyplot as plt
import csv

fLU = open("./benchmark/LU.csv","r")
fInvStr_str = open("./benchmark/InvStr_str.csv","r")
fInvStr_naive = open("./benchmark/InvStr_naive.csv","r")
fProd_naive = open("./benchmark/Prod_naive.csv","r")
fProd_str = open("./benchmark/Prod_str.csv","r")

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

plt.figure(figsize=(8,5))

plt.plot(list(LU.keys()),list(LU.values()),label="LU inversion")
plt.plot(list(InvStr_str.keys()),list(InvStr_str.values()),label="Strassen inversion using Strassen product")
plt.plot(list(InvStr_naive.keys()),list(InvStr_naive.values()),label="Strassen inversion using naive product")

plt.xlabel("n : size of the matrix")
plt.ylabel("Execution time in seconds")
plt.legend()

plt.savefig('./img/Inversion.png',bbox_inches='tight')
plt.clf()

plt.plot(list(Prod_naive.keys()),list(Prod_naive.values()),label="Naive product")
plt.plot(list(Prod_str.keys()),list(Prod_str.values()),label="Strassen product")

plt.xlabel("n : size of the matrix")
plt.ylabel("Execution time in seconds")
plt.legend()

plt.savefig('./img/Product.png',bbox_inches='tight')

fLU.close()
fInvStr_str.close()
fInvStr_naive.close()
fProd_naive.close()
fProd_str.close()