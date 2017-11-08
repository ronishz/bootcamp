from itertools import combinations as c

def get_support(l):
	count=0
	for i in data.keys():
		has=True
		for j in l:
			if j in data[i]:
				continue
			else:
				has=False
				break	

		if has:
			count+=1
	return count

def gen_candidates(table):
	keys=list(table.keys())
	tup_cnt=len(list(keys[0]))
	table = {}
	tup = []
	for v in c(keys,2):
		a=set(v[0])
		b=set(v[1])
		if((len(a&b)==(tup_cnt-1)) and (tuple(a|b) not in tup)):
			tup.append(tuple(a|b))
			print tup[-1]
			cnt=get_support(tup[-1])
			if(cnt>=support):
				table[tup[-1]]=cnt
	return table			




conv={1:"Mango",2:"Onion",3:"Jar",4:"Key-Chain",5:"Eggs",6:"Chocolates",7:"Nuts",8:"Corn",9:"Apple",10:"Knief",11:"ToothBrush"}
print conv
data={1:[1,2,3,4,5,6],2:[2,3,4,5,6,7],3:[1,4,5,9],4:[1,4,6,8,11],5:[2,4,5,8,10]}
support=3
conf=.5
table={}
for i in range(1,len(conv)+1):
	cnt=get_support({i})
	if cnt>=support:
		table[(i,)]=cnt
print "Prune list\n"
print table
while True:
	table=gen_candidates(table)
	if(len(table)==1 or len(table)==0):
		print "Pruned list\n"
		print table
		break
	else:
		print "Pruned list\n"
		print table

tup=set(list(table.keys())[0])
sup=table[list(table.keys())[0]]
ls = []
for i in range(1,len(tup)):
	ls+=c(tup,i)
print("+--------------------+---------------+------------------+")
print("|  Association rule  |     Support   |   Confidence     |")

print("+--------------------+---------------+------------------+")	

for i in ls:
	i=set(i)
	j=set(tup-i)
	sup_i=get_support(i)
	conf=float(sup)/float(sup_i)
	print("{}->{}\t\t{}\t\t{}/{}={}\t".format(i,j,sup,sup,sup_i,conf))





























 
