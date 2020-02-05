import matplotlib.pyplot as plt

with open("readData.txt") as file:
    readData = file.read()
lines = readData.splitlines()


data = []
index = 0

# Go up to numLines/2 (nyquist frequency)
# Take every ten of these samples (10Hz increment graph)
numLines = len(lines)
for i in range(numLines//2):
    if index % 5 == 0:
        # double amplitude of each entry because of nyquist frequency
        data.append(lines[i] * 2)
    index += 1

xVals = [i for i in range(0, numLines//2, 5)]
plt.xscale('log')
plt.plot(xVals, data)
plt.show()
