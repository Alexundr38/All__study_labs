class Node:
    def __init__(self, data, next = None):
        self.__data = data
        self.next = next

    def get_data(self):
        return self.__data

    def change_data(self, new_data):
        self.__data = new_data

    def __str__(self):
        if self.next != None:
            return f"data: {self.__data}, next: {self.next.__data}"
        else:
            return f"data: {self.__data}, next: {self.next}"


class LinkedList:
    def __init__(self, head = None):
        if head != None:
            self.head = [head]
        else:
            self.head = []
        self.length = len(self)

    def __len__(self):
        counts = 0
        if self.head != [] and self.head != None:
            counts = 1
            item=self.head
            while item.next != None:
                item=item.next
                counts += 1
        self.length = counts
        return counts

    def append(self, element):
        new_node = Node(element)
        if self.length > 0 :
            item = self.head
            while item.next != None:
                item=item.next
            item.next = new_node
            len(self)
        else:
            self.head = new_node
            len(self)

    def __str__(self):
        if self.length == 0:
            return "LinkedList[]"
        else:
            s = f"LinkedList[length = {self.length}, ["
            item = self.head
            while item != None:
                s += str(item) + '; '
                item = item.next
            s = s[:-2] + ']]'
        return s

    def pop(self):
        if len(self) == 0:
            raise IndexError("LinkedList is empty!")
        elif len(self) == 1:
            self.head = None
            len(self)
        else:
            item = self.head
            while item.next.next != None:
                item = item.next
            item.next = None
            len(self)

    def change_on_start(self, n, new_data):
        if len(self) < n or n <= 0:
            raise KeyError("Element doesn't exist!")
        else:
            item = self.head
            counted = 1
            while counted != n:
                item = item.next
                counted += 1
            item.change_data(new_data)

    def clear(self):
        self.length = 0
        while self.head != None:
            item = self.head
            self.head = self.head.next
            item = None

