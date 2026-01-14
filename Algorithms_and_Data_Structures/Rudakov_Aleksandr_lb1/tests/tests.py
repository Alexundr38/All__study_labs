from main import Unrolled_Linked_List
import pytest

@pytest.mark.parametrize('arr, expected',[
    ([1], (True, [1])),
    ([0,'a'], (False, 'TypeError: The Unrolled_Linked_List must consist of "int"')),
])
def test_find(arr, expected):
    if expected[0]:
        ex = Unrolled_Linked_List(arr)
        first = str(ex)[:-1]
        second = ' '.join(map(str, expected[1]))
        assert first == second
    else:
        with pytest.raises(TypeError) as call:
            ex = Unrolled_Linked_List(arr)
        assert expected[1] in str(call.value)






@pytest.mark.parametrize('arr, value, index, expected',[
    ([1], 2, 1, (True, [1,2])),
    ([0,1], 2, 1, (True, [0,2,1])),
    ([0,1], 2, 30, (False, 'IndexError: Unrolled_Linked_List index out of range'))
])

def test_insert(arr, value, index, expected):
    ex = Unrolled_Linked_List(arr)
    if expected[0]:
        ex.insert(value, index)
        first = str(ex)[:-1]
        second = ' '.join(map(str, expected[1]))
        assert first == second
    else:
        with pytest.raises(IndexError) as call:
            ex.insert(value, index)
        assert expected[1] in str(call.value)




@pytest.mark.parametrize('arr, index, expected',[
    ([1], 0, []),
    ([0,1], 0, [1])
])
def test_pop(arr, index, expected):
    ex = Unrolled_Linked_List(arr)
    ex.pop(index)
    first = str(ex)[:-1]
    second = ' '.join(map(str, expected))
    assert first == second




@pytest.mark.parametrize('arr, value, expected',[
    ([0,1], 0, (True, [1])),
    ([1,0], 0, (True, [1])),
    ([0,1], 10, (False, f'ValueError: 10 is not in Unrolled_Linked_List'))
])
def test_remove(arr, value, expected):
    ex = Unrolled_Linked_List(arr)
    if expected[0]:
        ex.remove(value)
        first = str(ex)[:-1]
        second = ' '.join(map(str, expected[1]))
        assert first == second
    else:
        with pytest.raises(ValueError) as call:
            ex.remove(value)
        assert expected[1] in str(call.value)




@pytest.mark.parametrize('arr, value, expected',[
    ([1], 0, -1),
    ([0,1], 0, 0),
    ([1,0], 0, 1)
])
def test_find(arr, value, expected):
    ex = Unrolled_Linked_List(arr)
    first = ex.find(value)
    second = expected
    assert first == second





@pytest.mark.parametrize('arr, index, expected',[
    ([1], 0, 1),
    ([2,0], 0, 2),
])
def test_index(arr, index, expected):
    ex = Unrolled_Linked_List(arr)
    first = ex[index]
    second = expected
    assert first == second





@pytest.mark.parametrize('arr, expected',[
    ([1], 1),
    ([2,0], 2)
])
def test_length(arr, expected):
    ex = Unrolled_Linked_List(arr)
    first = len(ex)
    second = expected
    assert first == second
