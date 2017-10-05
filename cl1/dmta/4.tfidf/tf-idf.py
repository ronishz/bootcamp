import re, math

def termFrequency(document):  # output the normalized term frequencies
    text = open(document).read()
    reducedDocument = [i for i in re.split('[ .\n]', text.lower()) if i]
    termFrequencyDict = {}
    for i in reducedDocument:
        if i not in termFrequencyDict:
            termFrequencyDict[i] = reducedDocument.count(i) / float(len(reducedDocument))
    return termFrequencyDict

def inverseDocumentFrequency(allDocuments):
    idfSet = set()
    idfDict, tempDict = {}, {}
    wordSets = []
    text = ""
    for doc in allDocuments:
        text = open(doc).read()      # merge all the text data
        wordSets.append(set([i for i in re.split('[ .\n]', text.lower()) if i]))  # wordSets is a doc.wise freq. count set
        idfSet |= wordSets[-1]
    for i in idfSet:                 # initialization of the dictionary
        tempDict[i] = 0.0
    for i in tempDict:
        for j in range(len(wordSets)):
            if i in wordSets[j]:     # number of documents in which the word has appeared
                tempDict[i] += 1
    for i in tempDict:            # if numDocumentsWithThisTerm > 0:
        if tempDict[i] > 0:
            idfDict[i] = 1.0 + math.log(float(len(allDocuments))/tempDict[i])
        else:
            idfDict[i] = 1.0
    return idfDict

def tfIdf(tf_list, idf):
    for doc in tf_list:
        for term in tf_list[doc]:
            tf_list[doc][term] = (tf_list[doc][term], tf_list[doc][term]*idf[term])

def cos_sim(query, document_list, idf, tf_list):
    query_set = set(query.split())  # to eliminate duplication
    term_freq = 1.0/len(query_set)  # the frequency of each term of the query
    cosines_dict = {}
    max_similarity = 0             # initialization of similarity
    max_doc = None
    for doc in document_list:
        cos_sum = 0
        query_mag = 0               # query magnitude and doc. term magnitude
        doc_mag = 0
        for term in query_set:
            cos_sum += (idf[term] if term in idf else 0)*term_freq*(tf_list[doc][term][1] if term in tf_list[doc] else 0)
            query_mag += math.pow((idf[term] if term in idf else 0)*term_freq, 2)
            doc_mag += math.pow((tf_list[doc][term][1] if term in tf_list[doc] else 0), 2)
        query_mag = math.sqrt(query_mag)
        doc_mag = math.sqrt(doc_mag)
        #print query_mag, doc_mag, cos_sum
        #print query_mag*doc_mag+0.001
        cos_sum /= (query_mag*doc_mag+0.001) # to avoid 0/0
        if (cos_sum >= max_similarity):
             max_similarity = cos_sum
             max_doc = doc
    if (max_similarity == 0):
        max_doc = "None"
    return (max_similarity, max_doc)

def main():
    document_list = ["doc-1", "doc-2", "doc-3"]
    termFrequencyList = {}    # contains the term frequency of all documents's terms
    for doc in document_list:
        termFrequencyList[doc] = termFrequency(doc)
    idf = inverseDocumentFrequency(document_list)  # inverse document frequency for all terms of all documents
    print idf, "\n"
    tfIdf(termFrequencyList, idf)
    print termFrequencyList
    query = raw_input("Enter the query : ")
    max_sim, doc_with_max_sim = cos_sim(query, document_list, idf, termFrequencyList)
    print "The max sim. is", max_sim, "for the doc.", doc_with_max_sim

if __name__ == "__main__":
    main()
