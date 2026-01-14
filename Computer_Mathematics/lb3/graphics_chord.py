import matplotlib.pyplot as plt
import numpy as np

with open("chord.txt", "r") as f:
    data = f.read()
f.close()
n = 0

chord_row = data.split('\n')[:-1]
chord_row = chord_row[n:]
chord_left = []
chord_right = []
chord_value = []
for i in chord_row:
    row = list(map(float, i.split(',')))
    chord_left.append(row[0])
    chord_right.append(row[1])
    chord_value.append(row[2])

fig, axs = plt.subplots(2,2, figsize = (10,10))
idx = [x+n for x in range(len(chord_row))]

axs[0,0].plot(idx, chord_left)
axs[0,0].set_title("chord left")
axs[0,0].set_xlabel("idx")
axs[0,0].set_ylabel("x")

axs[0,1].plot(idx, chord_right)
axs[0,1].set_title("chord right")
axs[0,1].set_xlabel("idx")
axs[0,1].set_ylabel("x")

axs[1,0].plot(idx, chord_value)
axs[1,0].set_title("bring_value")
axs[1,0].set_xlabel("idx")
axs[1,0].set_ylabel("x")

fig.delaxes(axs[1,1])
# plt.savefig("chord_with_1_5.pdf")
plt.show()