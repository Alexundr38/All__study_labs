class Node:
    def __init__(self, data=[]):
        self.data = data
        self.prev_element = None


class Stack:
    def __init__(self):
        self.__tail = None
        self.__length = 0

    def __len__(self):
        return self.__length

    def push(self, data):
        current = Node(data)
        new_tail = self.__tail
        current.prev_element = new_tail
        self.__tail = current
        self.__length += 1

    def pop(self):
        if not self.isEmpty():
            data = self.__tail.data
            self.__tail = self.__tail.prev_element
            self.__length -= 1
            return data
        else:
            return -1

    def isEmpty(self):
        if self.__tail != None:
            return False
        else:
            return True


def merge_block(value_stack, galops, merges, flag=0):
    while len(value_stack) >= 2:
        if len(value_stack) >= 3 and flag == 0:
            X_data = value_stack.pop()
            Y_data = value_stack.pop()
            Z_data = value_stack.pop()
            X_len, Y_len, Z_len = len(X_data), len(Y_data), len(Z_data)
            if Y_len >= X_len and Z_len >= X_len + Y_len:
                value_stack.push(Z_data)
                value_stack.push(Y_data)
                value_stack.push(X_data)
                break
            else:
                if X_len < Z_len:
                    galop_number, merged_data = merge(Y_data, X_data)
                    galops.append(galop_number)
                    merges.append(merged_data)
                    value_stack.push(Z_data)
                    value_stack.push(merged_data)
                else:
                    galop_number, merged_data = merge(Z_data, Y_data)
                    galops.append(galop_number)
                    merges.append(merged_data)
                    value_stack.push(merged_data)
                    value_stack.push(X_data)
        else:
            X_data = value_stack.pop()
            Y_data = value_stack.pop()
            X_len, Y_len = len(X_data), len(Y_data)
            if Y_len <= X_len or flag == 1:
                galop_number, merged_data = merge(Y_data, X_data)
                galops.append(galop_number)
                merges.append(merged_data)
                value_stack.push(merged_data)
            else:
                value_stack.push(Y_data)
                value_stack.push(X_data)
                break
    return galops, merges, value_stack


def bin_find(data, element):
    left = 0
    right = len(data)
    if abs(element) > abs(data[0]):
        return [], 0
    while right - left != 1:
        center = left + (right - left) // 2
        if abs(data[center]) >= abs(element):
            left = center
        elif abs(data[center]) < abs(element):
            right = center
    return data[1:right], right


def merge(first, second, flag = 3):
    first_idx, second_idx = 0, 0
    first_count, second_count = 0, 0
    count_galops = 0
    new_data = []
    while first_idx < len(first) and second_idx < len(second):
        if abs(first[first_idx]) >= abs(second[second_idx]):
            new_data.append(first[first_idx])
            first_idx += 1
            first_count += 1
            second_count = 0
        elif abs(first[first_idx]) < abs(second[second_idx]):
            new_data.append(second[second_idx])
            second_idx += 1
            second_count += 1
            first_count = 0

        if first_count == flag:
            data, new_idx = bin_find(first[first_idx - 1:], second[second_idx])
            first_idx += new_idx - 1
            first_count = 0
            new_data.extend(data)
            count_galops += 1
        elif second_count == flag:
            data, new_idx = bin_find(second[second_idx - 1:], first[first_idx])
            second_idx += new_idx - 1
            second_count = 0
            new_data.extend(data)
            count_galops += 1

    if first_idx >= len(first):
        new_data.extend(second[second_idx:])
    elif second_idx >= len(second):
        new_data.extend(first[first_idx:])
    return count_galops, new_data


def InsertionSort(data, flag):
    for i in range(len(data)):
        for j in range(i, 0, -1):
            if flag == True:
                if abs(data[j]) > abs(data[j - 1]):
                    temp = data[j]
                    data[j] = data[j - 1]
                    data[j - 1] = temp
            else:
                if abs(data[j]) < abs(data[j - 1]):
                    temp = data[j]
                    data[j] = data[j - 1]
                    data[j - 1] = temp
    return data


def push_and_merge(value_stack, data, galops, merges):
    value_stack.push(data)
    galops, merges, value_stack = merge_block(value_stack, galops, merges, 0)
    return galops, merges, value_stack


def final_merge(value_stack, galops, merges):
    while len(value_stack) > 1:
        galops, merges, value_stack = merge_block(value_stack, galops, merges, 1)
    return value_stack.pop()

def minrun_length(n):
    flag = 0
    while n >= 16:
        flag |= n & 1
        n >>= 1
    return n + flag

def TimSort(data):
    minrun = minrun_length(len(data))
    parts = []
    galops = []
    merges = []
    if minrun != len(data):
        idx = 0
        current_idx = 0
        value_stack = Stack()
        direction = True  # True == ">=", False == "<"
        for i in range(len(data)):
            if idx != 0:
                if idx == 1:
                    if current_idx + idx < len(data) and abs(data[current_idx]) < abs(data[current_idx + idx]):
                        direction = False
                    else:
                        direction = True

                elif idx >= minrun - 1:
                    flag = 0
                    if idx == minrun - 1:
                        add_idx = idx + 1
                    else:
                        add_idx = idx
                    if direction == True:
                        if current_idx + idx == len(data) or abs(data[current_idx + idx - 1]) < abs(
                                data[current_idx + idx]):
                            new_data = InsertionSort(data[current_idx: current_idx + add_idx], True)
                            flag = 1
                    elif current_idx + idx == len(data) or abs(data[current_idx + idx - 1]) >= abs(
                            data[current_idx + idx]):
                        new_data = InsertionSort(data[current_idx: current_idx + add_idx], False)
                        flag = 1

                    if flag == 1:
                        if direction == False:
                            new_data = InsertionSort(new_data, True)
                        data = data[:current_idx] + new_data + data[current_idx + add_idx:]
                        parts.append(new_data)

                        galops, merges, value_stack = push_and_merge(value_stack, new_data, galops, merges)
                        current_idx += add_idx
                        idx = 0

                else:
                    new_data = InsertionSort(data[current_idx: current_idx + idx], direction)
                    data = data[:current_idx] + new_data + data[current_idx + idx:]
            idx += 1

        if current_idx < len(data):
            new_data = InsertionSort(data[current_idx:], True)
            parts.append(new_data)
            galops, merges, value_stack = push_and_merge(value_stack, new_data, galops, merges)
        answer_data = final_merge(value_stack, galops, merges)

    else:
        answer_data = InsertionSort(data, True)
        parts.append(data)
    for i in range(len(parts)):
        print(f"Part {i}:", ' '.join(map(str, parts[i])))
    if len(galops) != 0:
        for i in range(len(galops)):
            print(f"Gallops {i}:", galops[i])
            print(f"Merge {i}:", ' '.join(map(str, merges[i])))
    return answer_data


n = int(input())
data = list(map(int, input().split()))

data = TimSort(data)
print("Answer:", ' '.join(map(str, data)))





