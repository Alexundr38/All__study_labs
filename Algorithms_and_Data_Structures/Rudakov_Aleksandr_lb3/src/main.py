from typing import Union

class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left: Union[Node, None] = left
        self.right: Union[Node, None] = right
        self.height: int = 1

def height(root: Union[Node, None]) -> int:
    if root == None:
        return 0
    return root.height

def right_rotate(root: Node) -> Node:
    out = root.left
    current = out.right
    out.right = root
    root.left = current

    root.height = 1 + max(height(root.left), height(root.right))
    out.height = 1 + max(height(out.left), height(out.right))

    return out

def left_rotate(root: Node) -> Node:
    out = root.right
    current = out.left
    out.left = root
    root.right = current

    root.height = 1 + max(height(root.left), height(root.right))
    out.height = 1 + max(height(out.left), height(out.right))

    return out

def balance(root: Union[Node, None]) -> int:
    if root == None:
        return 0
    left_height = height(root.left)
    right_height = height(root.right)
    return left_height - right_height

def insert(val, root: Union[Node, None]) -> Node:
    if root == None:
        return Node(val)
    if root.val > val:
        root.left = insert(val, root.left)
    else:
        root.right = insert(val, root.right)

    root.height = 1 + max(height(root.left), height(root.right))

    flag = balance(root)

    if flag == 2:
        if height(root.left.right) <= height(root.left.left):
            return right_rotate(root)
        else:
            root.left = left_rotate(root.left)
            return right_rotate(root)
    if flag == -2:
        if height(root.right.left) <= height(root.right.right):
            return left_rotate(root)
        else:
            root.right = right_rotate(root.right)
            return left_rotate(root)

    return root

def pre_order(root: Union[Node, None]):
    if root.left != None:
        left = root.left.val
        pre_order(root.left)
    else:
        left = -1
    if root.right != None:
        right = root.right.val
        pre_order(root.right)
    else:
        right = -1
    print(f'{left}; {root.val}; {right}')

def find_min(min_val, root: Union[Node, None]) -> (Node, int):
    if root.left != None:
        root.left, min_val = find_min(min_val, root.left)
    elif root.right != None:
        root.right, min_val = find_min(min_val, root.right)
    else:
        min_val = root.val
        root = None
    return root, min_val

def find_max_value(root: Union[Node, None], max_val = 0) -> (Node, int):
    if root.right != None:
        root.right, new_max = find_max_value(root.right, max_val)
        max_val = max(new_max, root.val)
    elif root.left != None:
        root.left, new_max = find_max_value(root.left, max_val)
        max_val = max(new_max, root.val)
    else:
        max_val = root.val
    return root, max_val

def remove_max(root: Union[Node, None]) -> Node:
    root, max_val = find_max_value(root)
    root = remove(max_val, root)
    return root

def find_min_value(root: Union[Node, None], min_val = 0) -> (Node, int):
    if root.left != None:
        root.left, new_min = find_max_value(root.left, min_val)
        min_val = min(new_min, root.val)
    elif root.right != None:
        root.right, new_min = find_max_value(root.right, min_val)
        min_val = min(new_min, root.val)
    else:
        min_val = root.val
    return root, min_val

def remove_min(root: Union[Node, None]) -> Node:
    root, min_val = find_min_value(root)
    root = remove(min_val, root)
    return root

def remove(val, root: Union[Node, None]) -> Node:
    if root == None:
        return root
    if val > root.val:
        root.right = remove(val, root.right)
    elif val < root.val:
        root.left = remove(val, root.left)
    else:
        if root.right == None:
            root = root.left
            if root == None:
                return root
        else:
            root.right, min_val = find_min(root.right.val, root.right)
            root.val = min_val

    root.height = 1 + max(height(root.left), height(root.right))

    flag = balance(root)

    if flag == 2:
        if height(root.left.right) <= height(root.left.left):
            return right_rotate(root)
        else:
            root.left = left_rotate(root.left)
            return right_rotate(root)
    if flag == -2:
        if height(root.right.left) <= height(root.right.right):
            return left_rotate(root)
        else:
            root.right = right_rotate(root.right)
            return left_rotate(root)

    return root

def check(root: Union[Node, None]) -> bool:
    balanced = True
    left_height = height(root.left)
    right_height = height(root.right)
    if abs(left_height - right_height) > 1:
        balanced = False
    if root.left != None:
        flag = check(root.left)
        if flag == False:
            balanced = False
    if root.right != None:
        flag = check(root.right)
        if flag == False:
            balanced = False
    return balanced

def diff(root: Union[Node, None], max_val = 100000000) -> int:
    min_count = max_val
    left_min_count = min_count
    add_left_count = min_count
    right_min_count = min_count
    add_right_count = min_count
    if root.left != None:
        left_min_count = diff(root.left)
        add_left_count = abs(root.val - root.left.val)
    if root.right != None:
        right_min_count = diff(root.right)
        add_right_count = abs(root.val - root.right.val)

    min_count = min(min_count, left_min_count, right_min_count, add_left_count, add_right_count)
    return min_count
