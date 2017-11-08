import json
def isSafe(row,col,sol):
	for prev_row in range(0,row):
		if((sol[prev_row]==col) or (abs(sol[prev_row]-col)==abs(prev_row-row))):
			#sol arrays contains prev placed queens col_num
			#for diagonal compare (prev_col - curr_col)==(prev_row - curr_row)
			return False
	return True		

def nqueens(row,n):
	global cnt
	for col in range(0,n):
		if(isSafe(row,col,sol)):
			sol[row]=col
			#insert queen
			if(row==(n-1)): #if row==7 means last row then print solution
				print('\nSolution- '+str(cnt)+"\n")
				cnt+=1
				for j in range(0,len(sol)):
					for k in range(0,8):
						if(k==sol[j]):
							print("Q", end="")
						else:
							print(".", end="")
					print('\n')
				print('\n--------------------------\n')
			else:
				nqueens(row+1,n)

sol = [-1]*8
sol[0]=int(json.load(open('input.json','r'))["start"])	#start_position taken from input.json
cnt=1	#keep count of all soutions
nqueens(1,8)	#row=1(next pos after 0), #n=number of rows/columns
print('Total solutions: '+str(cnt-1))







