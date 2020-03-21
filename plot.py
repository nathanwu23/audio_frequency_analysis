import matplotlib.pyplot as plt
import sys

file_name = sys.argv[1]

with open(file_name) as file:
    readData = file.read()
lines = readData.splitlines()

data = []
index = 0

# Go up to numLines/2 (nyquist frequency)
# Take every ten of these samples (10Hz increment graph)
numLines = len(lines)
for i in range(numLines//2):
    if index % 10 == 0:
        # double amplitude of each entry because of nyquist frequency
        data.append(float(lines[i]) * 2)
    index += 1


xVals = [i for i in range(0, numLines//2, 10)]
plt.axis([0, 20000, 0, 1000])

plt.show()
