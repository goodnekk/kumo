#python script runs tests
import subprocess

tests = [["variables","20"],["functions","8"]]

for t in tests:

    p = subprocess.Popen(["../bin/kumo","scripts/"+t[0]+".kmo"], stdout=subprocess.PIPE)
    data = p.communicate()
    lines = data[0].split('\r\n')

    for i in lines:
        if(not i=="> hello kumo 0.01"):
            if(i[2:]==t[1]):
                print(t[0]+"...ok!")
