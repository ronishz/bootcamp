from Tkinter import *
from pyDes import *
class MyGUI:
    def __init__(self, master):
        self.master = master
        self.plainT = StringVar()
        self.key = StringVar()
        master.title("Cipher")

        self.label1 = Label(master, text="Enter plaintext:")
        self.label1.pack()

        self.plainText = Entry(master, textvariable = self.plainT)
        self.plainText.pack()

        self.label3 = Label(master, text="Enter appropriate key:")
        self.label3.pack()

        self.keyLabel = Entry(master, textvariable = self.key)
        self.keyLabel.pack()

        self.label2 = Label(master, text="Encrypted text:")
        self.label2.pack()

        self.resultText = Label(master, text = "")
        self.resultText.pack()

        self.ceaserB = Button(master, text="Ceaser cipher", command=self.ceaserCipher)
        self.ceaserB.pack()

        self.desB = Button(master, text="       DES       ", command=self.des)
        self.desB.pack()

        self.pfB = Button(master, text ="     Playfair    ", command=self.pf)
        self.pfB.pack()

        self.close_button = Button(master, text="Close", command=master.quit)
        self.close_button.pack()

    def pf():
    	pass

    def ceaserCipher(self):
    	print 'Ceaser cipher'
    	plain = self.plainT.get().lower()
    	ceaserKey = self.key.get()
    	if ceaserKey.isalpha():
    		print 'Key needs to be a number!'
    		return
    	ceaserKey = int(ceaserKey)
        encrypted = []
        for char in plain:
        	newChar = (ord(char) - 97 + ceaserKey) % 26
        	newChar = newChar + 97
        	encrypted.append(chr(newChar))	
        self.resultText['text'] = ''.join(encrypted)
    
    def des(self):
	    print ("DES encryption")
	    desKey = self.key.get()
	    if len(desKey) != 8:
	    	print 'DES key needs to be 8 bytes long!'
	    	return
	    k = des(desKey)
	    data = "DES encryption algorithm"
	    d = k.encrypt(data)
	    print 'Encrypted:'
	    print (d)
	    self.resultText['text'] = unicode(d, 'iso8859-1')
	  #  d = k.decrypt(d)
	   # print (d)

root = Tk()
my_gui = MyGUI(root)
root.mainloop()