import csv
import sys 

def main(): 
    
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")
    
    dataBase = sys.argv[1]
    seqFile = sys.argv[2]
    with open(dataBase) as csvFile:
        reader = csv.DictReader(csvFile)
        for row in reader:
            dictList = list(reader)#["name":Fred,"23","21",'12']
            
    with open(seqFile) as seq:
        sequence = seq.read()#AGATAAGATAAGATAAGATAAGATAAGATAAGATAAGATAAGATA
        
    MaxCounts = []
    
    for i in range(1, len(reader.fieldnames)):
        STR = reader.fieldnames[i] #AGAT
        MaxCounts.append(0)
        
        for j in range(len(sequence)):
            STRCounts = 0 #
            if sequence[j:j + len(STR)] == STR: #AGAT = 1 GATC = 2 ATCG = 3
                k = 0
                while sequence[(j+k):(j + k + len(STR))] == STR:
                    STRCounts +=1
                    k += len(STR)
                if STRCounts > MaxCounts[i-1]:
                    MaxCounts[i-1] = STRCounts
                        
    for i in range(len(dictList)):
        matches = 0 
        for j in range(1, len(reader.fieldnames)):
            if int(MaxCounts[j - 1]) == int(dictList[i][reader.fieldnames[j]]):
                matches += 1
            if matches == (len(reader.fieldnames) - 1):
                print(dictList[i]["name"])
                print(len(reader.fieldnames))
                sys.exit(0)
    print("No match")
    

if __name__ == "__main__":
    main()