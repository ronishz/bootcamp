from __future__ import division
from itertools import combinations as comb
from itertools import count


class Apriori():
    def __init__(self):
        self.converter = {1:"Mango",2:"Onion",3:"Jar",4:"Key-Chain",5:"Eggs",
                            6:"Chocolates",7:"Nuts",8:"Corn",
                            9:"Apple",10:"Knief",11:"ToothBrush"}
        print(self.converter)
        self.data = {
                1:[1,2,3,4,5,6],
                2:[2,3,4,5,6,7],
                3:[1,4,5,9],
                4:[1,4,6,8,11],
                5:[2,4,5,8,10]
            }
            
        self.support=3
        self.confidence=.5
        self.table=dict()

    def apriori(self):
    	self.init_table()
    	print("pruned List:")
    	print(self.table)
   	for i in count(0):
    		self.find_commons()
    		print("pruned List:")
    		print(self.table)
    		if len(self.table)==1:
    			break

    	tup=set(list(self.table.keys())[0])
    	sup= self.table[list(self.table.keys())[0]]
    	ls = list()
    	for i in range(1,len(tup)):
    		ls = ls+list(comb(tup,i))
    	#for i in tup:
    		#print("{} : {}".format(i,self.converter[i]))

    	print("+--------------------+---------------+------------------+")
    	print("|  Association rule  |     Support   |   Confidence     |")

    	print("+--------------------+---------------+------------------+")

    	for i in ls:
    		i=set(i)
    		j=set(tup-i)
    		sup2 = self.getsupport(i)
    		conf = sup/sup2
    		print("|{}->{} \t|        {}   |   {}/{} = {}  \t|".format(i,j,sup,sup,sup2,conf))
    	print("+--------------------+---------------+------------------+")





    
   
    def getsupport(self,tup):
    	count = 0
    	for v in self.data.keys():
    		has=True
    		for i in tup:
    			if i in self.data[v]:
    				continue
    			else:
    				has=False
    				break

    		if has:
    			count+=1
    	return count

   
 

    
    def init_table(self):
    	for i in range (1,len(self.converter)+1):
    		count = self.getsupport({i})
    		if count>=self.support:
    			self.table[(i,)]=count

    def find_commons(self):
    	keys=list(self.table.keys())
    	comm_c=len(keys[0])
    	
    	
    	self.table={}
    	print("Candidate List:")
    	for v in comb(keys,2):
    		a=set(v[0])
    		b=set(v[1])
    		if len(a & b)==comm_c-1:
    			tup = tuple(a | b)
    			print(tup)
    			count = self.getsupport(tup)
    			if count>=self.support:
    				self.table[tup]=count

if __name__=="__main__":
    a=Apriori()
a.apriori()





        				
