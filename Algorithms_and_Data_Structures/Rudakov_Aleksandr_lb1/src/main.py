import math

def check(arr_1, arr_2, n_array = 4):
    my_list = Unrolled_Linked_List(arr_1, n_array)
    print(my_list)
    for i in arr_2:
        if my_list.find(i) != -1:
            my_list.remove(i)
            print(my_list)

class Node:
    def __init__(self, data = [], next_element = None):
        self.data = data
        self.next_element = next_element


class Unrolled_Linked_List:
    def __init__(self, data = None, n_array = 4):
        if not isinstance(n_array, int) or n_array == 0:
            self.__type_error_index()
        if not isinstance(data, list):
            self.__type_error_value()
        for value in data:
            if not isinstance(value, int):
                self.__type_error_value()
        if len(data) == 0:
            self.__length_error()
        idx = 0
        self.__head = None
        self.__n_array = n_array
        self.__length = len(data)
        while len(data) > idx:
            element = self.__create_node(data[idx : idx + n_array])
            self.__head = self.__add_node(self.__head, element)
            idx += n_array


    def __getitem__(self, index):
        if index >= self.__length or index < 0:
            self.__index_error()
        current, idx = self.__find_current(index)
        return current.data[index - idx]


    def __add_node(self, head, element):
        if head == None:
            head = element
        else:
            current = head
            while current.next_element != None:
                current = current.next_element
            current.next_element = element
        return head


    def __str__(self):
        output = ''
        current = self.__head
        while current != None:
            output += ' '.join(map(str,current.data)) + ' '
            current = current.next_element
        return output


    def __len__(self):
        return self.__length
        
    def calculate_optimal_node_size(num_elements, size_of_int = 4, cache_min_size = 64):
        total_memory = num_elements * size_of_int
        num_lines = math.ceil(total_memory / cache_min_size) + 1
        return num_lines


    def find(self, value):
        if not isinstance(value, int):
            self.__type_error_value()
        current = self.__head
        idx = 0
        while current.next_element != None and (not (value in current.data)):
            idx += len(current.data)
            current = current.next_element
        if value in current.data:
            idx += current.data.index(value)
        else:
            idx = -1
        return idx


    def __find_current(self, n_idx):
        current = self.__head
        idx = 0
        while idx + len(current.data) <= n_idx and current.next_element != None:
            idx += len(current.data)
            current = current.next_element
        return current, idx


    def __create_node(self, data):
        current = Node(data)
        return current


    def __optimal_size(self):
        current_n_array = self.calculate_optimal_node_size(self.__length)
        if current_n_array != self.__n_array:
            self.__balance(current_n_array)
            self.__n_array = current_n_array


    def __balance(self, n_array):
        current = self.__head
        new_head = None
        data = []
        idx = 0
        curr_idx = 0
        while current != None:
            if 1 - curr_idx + idx + len(current.data) <= n_array:
                data.extend(current.data[curr_idx:])
                idx += len(current.data[curr_idx:])
                curr_idx = 0
                current = current.next_element
            else:
                curr_idx = n_array - idx
                data.extend(current.data[:curr_idx])
            if len(data) == n_array:
                element = self.__create_node(data)
                new_head = self.__add_node(new_head, element)
                data = []
                idx = 0
        if len(data) != 0:
            element = self.__create_node(data)
            new_head = self.__add_node(new_head, element)
        self.__head = new_head


    def insert(self, value, in_idx):
        if not isinstance(value, int):
            self.__type_error_value()
        if not isinstance(in_idx, int):
            self.__type_error_index()
        self.__length += 1
        current, idx = self.__find_current(in_idx)
        if idx + self.__n_array < in_idx or in_idx < 0:
            self.__length -= 1
            self.__index_error()
        elif idx + self.__n_array == in_idx:
            element = self.__create_node([value])
            element.next_element = current.next_element
            current.next_element = element
        else:
            if len(current.data) == self.__n_array:
                first_data = current.data[:in_idx - idx]
                first_data.append(value)
                first_element = self.__create_node(first_data)
                second_data = current.data[in_idx - idx:]
                second_element = self.__create_node(second_data)
                second_element.next_element = current.next_element
                first_element.next_element = second_element
                self.__add_support(current, first_element)
            else:
                new_data = current.data[:in_idx - idx]
                new_data.append(value)
                new_data.extend(current.data[in_idx - idx:])
                current.data = new_data
        self.__optimal_size()


    def __add_support(self, current, add_element):
        if current != self.__head:
            current_support = self.__head
            while current_support.next_element != current:
                current_support = current_support.next_element
            current_support.next_element = add_element
        else:
            self.__head = add_element


    def pop(self, idx):
        if not isinstance(idx, int):
            self.__type_error_index()
        if idx < 0 or idx >= self.__length:
            self.__index_error()
        else:
            current, d_idx = self.__find_current(idx)
            if len(current.data) != 1:
                current.data.pop(idx - d_idx)
            else:
                self.__add_support(current, current.next_element)
            self.__length -= 1
            self.__optimal_size()


    def remove(self, value):
        idx = self.find(value)
        if idx == -1:
            self.__value_error(value)
        self.pop(idx)


    def print_Node(self):
        current = self.__head
        i = 0
        while current != None:
            print(f'Node {i}:', ' '.join(map(str, current.data)))
            i += 1
            current = current.next_element


    def __index_error(self):
        raise IndexError('IndexError: Unrolled_Linked_List index out of range')  # error


    def __value_error(self, value):
        raise ValueError(f'ValueError: {value} is not in Unrolled_Linked_List')  # error


    def __type_error_value(self):
        raise TypeError('TypeError: The Unrolled_Linked_List must consist of "int"') #error


    def __type_error_index(self):
        raise TypeError('TypeError: The index and n_array can only contain "int"') #error


    def __length_error(self):
        raise Exception('LengthError: The length of Unrolled_Linked_List cannot be equal to 0')
