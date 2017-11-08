class Apriori():
	def __init__(self):
		self.support = 2
		self.confidence = 0.7
		self.elements = {1:"Mango",2:"Onion",3:"Jar",4:"Key-Chain",5:"Eggs"}
		self.data = {
				1:[1,2,4],
                2:[1,2,5],
                3:[1,3,5],
                4:[2,4],
                5:[2,3],
                6:[1,2,3,5],
                7:[1,3],
                8:[1,2,3],
                9:[2,3],
                10:[3,5]
		}
		self.prune_list = dict()


	def getSupport(self, tup):
		"""
		Returns the count of tuples belonging to the prune_list
		"""
		count = 0
		for key in self.data.keys():
			has = True
			for element in tup:
				if element in self.data[key]:
					continue
				else:
					has = False
					break
			if has:
				count+=1
		return count

	def init_prune_list(self):
		"""
		Initialize the prune list
		"""
		for i in range(1, len(self.elements)+1):
			count = self.getSupport({i})
			if(count >= self.support):
				self.prune_list[(i,)] = count



	def generateCandidates(self):
		"""
		Generate candidate list and update prune list
		"""
		print("Candidate list:\n")
		keys = list(self.prune_list.keys())
		tuple_count = len(keys[0])
		prune_list = {}
		tup = []
		for v in comb(keys, 2):
			a = set(v[0])
			b = set(v[1])
			
			# If there's as many common element in a & b as one less than tuple_count
			if((len(a & b) == (tuple_count - 1)) and (tuple(a | b) not in tup)):
				tup.append(tuple(a | b))
				print(tup[-1])
				# Update prune list
				count = self.getSupport(tup[-1])
				if(count >= self.support):
					prune_list[tup[-1]] = count
		return prune_list

	def apriori(self):
		self.init_prune_list()

		print("Pruned List:\n")
		print(self.prune_list)
		prune_list = {}
		# Keep on generating candidates and pruning till only one tuple remains
		while True:
			prune_list = self.generateCandidates()

			# If prune_list exists, then print otherwise break the loop
			if(len(prune_list)):
				self.prune_list = prune_list
				print("Pruned List:\n")
				print(prune_list)
			elif(len(prune_list) == 0):
				#print self.prune_list
				break
			if(len(self.prune_list) == 1):
				break

		tup = set(list(self.prune_list.keys())[0])
		sup = self.prune_list[list(self.prune_list.keys())[0]]
		ls = list()
		for i in range(1, len(tup)):
			ls += comb(tup, i)

		for i in tup:
			print("{} : {}").format(i, self.elements[i])

		print("+--------------------+---------------+------------------+")
		print("|  Association rule  |     Support   |   Confidence     |")

		print("+--------------------+---------------+------------------+")

		for i in ls:
			i = set(i)
			j = set(tup - i)
			sup_d = self.getSupport(i)
			confidence = float(sup)/float(sup_d)
			print("{}->{}|\t\t{}    |\t{}/{}={}\t|".format(i,j,sup,sup, sup_d, round(confidence,2) ))



def main():
	a = Apriori()
	a.apriori()

if __name__ == '__main__':
	from itertools import combinations as comb
	main()

