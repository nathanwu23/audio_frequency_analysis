import matplotlib.pyplot as plt

with open("readData.txt") as file:
    readData = file.read()
lines = readData.splitlines()

# with open("inputData.txt") as file:
#     readData = file.read()
# lines = readData.splitlines()


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

# numLines = len(lines)
# # for i in range(4000):
# for i in range(numLines):
#     if index % 10 == 0:
#         # double amplitude of each entry because of nyquist frequency
#         data.append(float(lines[i]))
#     index += 1

# xVals = [i for i in range(0, numLines, 10)]
xVals = [i for i in range(0, numLines//2, 10)]
# plt.xscale('log', basex=, subsx = [1,2,3,4,5,6,7,8,9])
plt.axis([0, 20000, 0, 1000])

# plt.yscale('log', basey=10)
# fig, ax = plt.subplots()
# plt.set_xscale('log', basex=10)
# plt.set_yscale('log', basey=10)
plt.plot(xVals, data)
plt.show()
