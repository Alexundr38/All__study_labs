f = open('time_1.txt', 'r')
arr = []
lines = f.readlines()
all_value = 0
count_value = 0
for i in lines:
    all_value += float(i)
    count_value += 1
print(all_value/count_value)

f.close()