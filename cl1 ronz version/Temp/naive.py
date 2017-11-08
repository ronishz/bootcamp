from __future__ import division
from __future__ import print_function

def displayData(data):
	print("ID\tAGE\t\tINCOME\tSTUDENT\tCREDIT RATING\tBUY")
	for entry in data:
		print(str(entry[0])+"\t"+str(entry[1])+"\t"+str(entry[2])+"\t"+str(entry[3])+"\t"+str(entry[4])+"\t\t"+str(entry[5]))

def getData(data, n):
	for i in range(n):
		entry = []
		entry.append(i+1)
		print("ENTRY "+str(i+1))
		age = input("Enter age\n1-Young\n2-Middle-Aged\n3-Old\n")
		if age == 1:
			entry.append("Young")
		elif age == 2:
			entry.append("Middle-Aged")
		elif age == 3:
			entry.append("Old")
		income = input("Enter income\n1-Low\n2-Medium\n3-High\n")
		if income == 1:
			entry.append("Low")
		elif income == 2:
			entry.append("Medium")
		elif income == 3:
			entry.append("High")
		student = input("Enter if student\n1-Yes\n2-No\n")
		if student == 1:
			entry.append("Yes")
		elif student == 2:
			entry.append("No")
		cred = input("Enter credit rating\n1-Low\n2-Fair\n3-High\n")
		if cred == 1:
			entry.append("Low")
		elif cred == 2:
			entry.append("Fair")
		elif cred == 3:
			entry.append("High")
		buy = input("Enter if person buys computer\n1-Yes\n2-No\n")
		if buy == 1:
			entry.append("Yes")
		elif buy == 2:
			entry.append("No")
		data.append(entry)

def predictNaive(data, new, n):
	ageY = 0 
	ageN = 0
	incomeY=0
	incomeN=0
	studY=0
	studN=0
	credY=0
	credN=0
	buyY=0
	buyN=0
	for entry in data:
		if entry[5] == "Yes":
			buyY += 1
		elif entry[5] == "No":
			buyN += 1
	for i in range(4):
		for entry in data:
			if entry[i+1] == new[i] and entry[5]=="Yes":
				if i+1 == 1:
					ageY += 1
				elif i+1 ==2:
					incomeY += 1
				elif i+1 == 3:
					studY += 1
				elif i+1 == 4:
					credY +=1
			elif entry[i+1] == new[i] and entry[5]=="No":
				if i+1 == 1:
					ageN += 1
				elif i+1 == 2:
					incomeN += 1
				elif i+1 == 3:
					studN += 1
				elif i+1 == 4:
					credN +=1
	#print(ageY, ageN, ageCount, incomeY, incomeN, incomeCount, studY, studN, studCount, credY, credN, credCount, buyY, buyN)
	ageY = ageY/buyY
	ageN= ageN/buyN
	incomeY= incomeY/buyY
	incomeN= incomeN/buyN
	studY=studY/buyY
	studN=studN/buyN
	credY=credY/buyY
	credN=credN/buyN
	buyY = buyY/n
	buyN=buyN/n
	probY = ageY * incomeY * studY * credY * buyY
	probN = ageN * incomeN * studN * credN * buyN
	print(probY)
	print(probN)
	if probY >= probN:
		print("Yes")
	else:
		print("No")
	

data = []
n = input("Enter no. of entries: ")
getData(data, n)
displayData(data)

new = []
print("Enter new data: ")
age = input("Enter age\n1-Young\n2-Middle-Aged\n3-Old\n")
if age == 1:
	new.append("Young")
elif age == 2:
	new.append("Middle-Aged")
elif age == 3:
	new.append("Old")
income = input("Enter income\n1-Low\n2-Medium\n3-High\n")
if income == 1:
	new.append("Low")
elif income == 2:
	new.append("Medium")
elif income == 3:
	new.append("High")
student = input("Enter if student\n1-Yes\n2-No\n")
if student == 1:
	new.append("Yes")
elif student == 2:
	new.append("No")
cred = input("Enter credit rating\n1-Low\n2-Fair\n3-High\n")
if cred == 1:
	new.append("Low")
elif cred == 2:
	new.append("Fair")
elif cred == 3:
	new.append("High")
	
predictNaive(data, new, n)