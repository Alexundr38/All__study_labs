import main
import pytest

# 1 -1 1 1 1 1 1 1 1 -1 1 1 1 1 -1 -1 1 1 -1 1 -1 1 -1 -1 1 1
@pytest.mark.parametrize('arr, expected', [
    ([1,-1,1,1,1,1,1,1,1,-1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,-1,-1,1,1],
     [1,-1,1,1,1,1,1,1,1,-1,1,1,1,1,-1,-1,1,1,-1,1,-1,1,-1,-1,1,1]),
    ([],[]),
    ([-1,2], [2,-1])
])
def tests_sort(arr, expected):
    data = arr
    answer = main.TimSort(data)
    assert answer == expected

