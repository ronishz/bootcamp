import math
def cal_tf(doc):
	text=((open(doc).read()).lower()).split()			#split all words in the document in text array	
	words={}											#to store words with their term frequency
	for i in text:										#for each word in document
		if i not in words:								#to avoid repetitive words
			words[i]=text.count(i)/float(len(text))		#formula of term freq=count of word in doc / total words in doc
	return words

def cal_idf(doc_list,tf):
	text=""
	idf = {}
	words=[]
	for i in doc_list:
		text=((open(i).read()).lower())
		words.append(text)								#each element in words array 'll have set of all words in one document
	word_set=""											
	for i in words:
		word_set+=i 									#word_set stores all words in all documents
	all_words=set(word_set.split())						#unique set of all words
	total_doc=len(doc_list)
	for i in all_words:
		cnt=0
		for j in words:
			if i in j.split():
				cnt+=1									#count of documents containing word 'i' in jth document
		if cnt>0:		
			idf[i]=1+math.log(total_doc/cnt)			#formula of idf = 1+log(total docs/no of docs that contain particular word)
	return idf

def cal_tfidf(doc_list,tf,idf):
	tfidf={}
	for i in idf:
		tfidf[i]={}											
		for j in doc_list:								#j=document
			if i in tf[j]:								#i=word
				tfidf[i][j]=tf[j][i]*idf[i]				#tfidf= tf* idf (for each word in every document)	
			else:
				tfidf[i][j]=0	
	return tfidf	

def cosine_similarity(query,doc_list,tf,idf,tfidf):
	q=list(set((query.lower()).split()))				#set eliminates duplicate words
	q_tfidf={}											#query set
	for i in q:
		if i in idf and i not in q_tfidf:
			q_tfidf[i]=((q.count(i))/len(q))*idf[i]		#calculate tf-idf for query(tf*idf)
		else:
			q_tfidf[i]=0								#if words doesn't exist in documents then return 0
	cos = []											#to store cosine similarity for all documents
	for i in doc_list:
		dot=0											#numerator - dot product
		mod_q=0											#denominator - modulus of query
		mod_d=0											#denominator - modulus of document
		for j in q_tfidf:								#for each word in query set
			if j in tfidf:
				dot+=q_tfidf[j]*tfidf[j][i]				#dot product=tfidf of 1st word in query * tfidf of 1st word in that document
				mod_q+=q_tfidf[j]*q_tfidf[j]			#modulus - (jth word tf-idf)^2 in query
				mod_d+=tfidf[j][i]*tfidf[j][i]			#modulus - (jth word tf-idf)^2 in document
		mod_q=math.sqrt(mod_q)	
		mod_d=math.sqrt(mod_d)
		mod=mod_d*mod_q									#denominator= modulus of document * modulus of query
		cos.append(dot/(mod+0.001))						#add 0.001 to denominator to avoid 0/0 error
	return cos 											#return cosine similarity for all documents

doc_list=["doc-1","doc-2","doc-3"]
tf={}
idf={}
tfidf={}
cos=[]
for i in doc_list:
	tf[i]=cal_tf(i)										#calculate term frequency
idf=cal_idf(doc_list,tf)								#calculate inverse document frequency
tfidf=cal_tfidf(doc_list,tf,idf)						#calculate tf-idf(tf*idf for each document)
print('---------Term Frequency(TF)-------------',end="\n\n")
print(tf,end="\n\n")
print('---------Inverse Document Frequency(IDF)-------------',end="\n\n")
print(idf,end="\n\n")
print('---------TF-IDF-------------',end="\n\n")
print(tfidf,end="\n\n")
query=input('Query:	')									#input query for which similarity is to be found
#Cosine Similarity (d1, d2) = Dot product(d1, d2) / ||d1|| * ||d2||		---------formula--------
cos=cosine_similarity(query,doc_list,tf,idf,tfidf)
print('cosine_similarity for all documents starting from 1 :	',end=" ")
print(cos)
print("Maximum cosine_similarity is :	",end=" ")
print(max(cos))											#max cosine similarity
if(max(cos)==0):
	print('Sorry, no Similarity found !',end="\n")
else:	
	print("In document no-	",end=" ")
	print(cos.index(max(cos)) + 1)						#document number in which max cosine similarity is found
