import random
import string

def createString(Length=10):
    randomString = string.ascii_lowercase
    return ''.join(random.choice(randomString) for i in range(Length))

makeFileOne = open("FileOne.txt","w+")
makeFileTwo = open("FileTwo.txt","w+")
makeFileThree = open("FileThree.txt", "w+")

stringOne = createString()
print (stringOne)
stringTwo = createString()
print (stringTwo)
stringThree = createString()
print (stringThree)

makeFileOne.write(stringOne + "\n")
makeFileTwo.write(stringTwo + "\n")
makeFileThree.write(stringThree + "\n")

numberOne = random.randrange(1,43,1)
print (numberOne)
numberTwo = random.randrange(1,43,1)
print (numberTwo)
Product = numberOne*numberTwo
print (Product)

makeFileOne.close()
makeFileTwo.close()
makeFileThree.close()
