def naive(entry,new):
	#print(len(entry))
	buyY=buyN=incomeY=incomeN=ageY=ageN=creditY=creditN=studentY=studentN=probY=probN=0
	for i in entry:
		if(i[4]=='yes'):
			buyY+=1
		if(i[4]=='no'):
			buyN+=1

	for i in entry:
		if(i[0]==new[0] and i[4]=='yes'):
			ageY+=1
		elif(i[0]==new[0] and i[4]=='no'):
			ageN+=1

		if(i[1]==new[1] and i[4]=='yes'):
			incomeY+=1
		elif(i[1]==new[1] and i[4]=='no'):
			incomeN+=1

		if(i[2]==new[2] and i[4]=='yes'):
			studentY+=1
		elif(i[2]==new[2] and i[4]=='no'):
			studentN+=1

		if(i[3]==new[3] and i[4]=='yes'):
			creditY+=1
		elif(i[3]==new[3] and i[4]=='no'):
			creditN+=1

	ageY=ageY/buyY
	ageN=ageN/buyN
	incomeY=incomeY/buyY
	incomeN=incomeN/buyN
	creditY=creditY/buyY
	creditN=creditN/buyN
	studentY=studentY/buyY
	studentN=studentN/buyN

	probY = ageY * incomeY * studentY * creditY * (buyY/len(entry))
	probN = ageN * incomeN * studentN * creditN * (buyN/len(entry))

	print(new)
	print('probY= '+str(probY),end='\n')
	print('probN= '+str(probN),end='\n')

	if(probY>=probN):
		print('Buys-computer prediction = Yes')
	else:
		print('Buys-computer prediction = No')	

#----main-function----
d_lines=(open('naive_input','r').read()).split('\n')[1:-1]			#[:-1] to remove last \n & first title row
entry=[]
for i in d_lines:
	entry.append(i.split())
for i in entry:
	print(i,end='\n')
new=input("age(youth/mid-age/old)  income(high/medium/low)  student(yes/no)  credit(fair/excel)\n").split()
naive(entry,new)