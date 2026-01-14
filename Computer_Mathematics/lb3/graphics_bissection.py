import matplotlib.pyplot as plt
import numpy as np

with open("bissection.txt", "r") as f:
    data = f.read()
f.close()
n = 0

bissection_row = data.split('\n')[:-1]
bissection_row = bissection_row[n:]
bissection_left = []
bissection_center = []
bissection_right = []
bissection_value = []
for i in bissection_row:
    row = list(map(float, i.split(',')))
    bissection_left.append(row[0])
    bissection_center.append(row[1])
    bissection_right.append(row[2])
    bissection_value.append(row[3])

fig, axs = plt.subplots(2,2, figsize = (10,10))
idx = [x+n for x in range(len(bissection_row))]

axs[0,0].plot(idx, bissection_left)
axs[0,0].set_title("Bissection left")
axs[0,0].set_xlabel("idx")
axs[0,0].set_ylabel("x")

axs[1,0].plot(idx, bissection_center)
axs[1,0].set_title("Bissection center")
axs[1,0].set_xlabel("idx")
axs[1,0].set_ylabel("x")

axs[0,1].plot(idx, bissection_right)
axs[0,1].set_title("Bissection right")
axs[0,1].set_xlabel("idx")
axs[0,1].set_ylabel("x")

axs[1,1].plot(idx, bissection_value)
axs[1,1].set_title("Bissection_value")
axs[1,1].set_xlabel("idx")
axs[1,1].set_ylabel("x")

# plt.savefig("Bissection_with_1_5.pdf")
plt.show()