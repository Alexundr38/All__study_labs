import main
import pytest
from io import StringIO
import sys

@pytest.mark.parametrize('arr, expected',[
    ([0], True),
    ([2,1,3], True)
])
def test_check(arr, expected):
    root = None
    for i in arr:
        root = main.insert(i, root)
    answer = main.check(root)
    assert answer == expected

@pytest.mark.parametrize('arr, expected',[
    ([212, 69, 369, 145, 390], 21),
    ([3, -3], 6)
])
def test_diff(arr, expected):
    root = None
    for i in arr:
        root = main.insert(i, root)
    answer = main.diff(root)
    assert answer == expected

@pytest.mark.parametrize('arr, expected',[
    ([1,1,1], "-1; 1; -1\n-1; 1; -1\n1; 1; 1\n"),
    ([10,20,30,40,50], "-1; 10; -1\n-1; 30; -1\n-1; 50; -1\n30; 40; 50\n10; 20; 40\n")
])
def test_insert(arr, expected):
    root = None
    for i in arr:
        root = main.insert(i, root)
    captured_output = StringIO()
    sys.stdout = captured_output
    main.pre_order(root)
    sys.stdout = sys.__stdout__
    assert captured_output.getvalue() == expected

@pytest.mark.parametrize('arr, del_element, expected',[
    ([10,20,30,40,50], 40, "-1; 10; -1\n-1; 30; -1\n30; 50; -1\n10; 20; 50\n"),
    ([10,20,30,40,50], 20, "-1; 10; -1\n-1; 50; -1\n-1; 40; 50\n10; 30; 40\n")
])
def test_remove(arr, del_element, expected):
    root = None
    for i in arr:
        root = main.insert(i, root)
    root = main.remove(del_element, root)
    captured_output = StringIO()
    sys.stdout = captured_output
    main.pre_order(root)
    sys.stdout = sys.__stdout__
    assert captured_output.getvalue() == expected

@pytest.mark.parametrize('arr, expected',[
    ([10,20,30,40,50], "-1; 10; -1\n-1; 30; -1\n30; 40; -1\n10; 20; 40\n"),
    ([2,1,3], "-1; 1; -1\n1; 2; -1\n")
])
def test_remove_max(arr, expected):
    root = None
    for i in arr:
        root = main.insert(i, root)
    root = main.remove_max(root)
    captured_output = StringIO()
    sys.stdout = captured_output
    main.pre_order(root)
    sys.stdout = sys.__stdout__
    assert captured_output.getvalue() == expected



@pytest.mark.parametrize('arr, expected',[
    ([10,20,30,40,50], "-1; 30; -1\n-1; 20; 30\n-1; 50; -1\n20; 40; 50\n"),
    ([2,1,3], "-1; 3; -1\n-1; 2; 3\n")
])
def test_remove_min(arr, expected):
    root = None
    for i in arr:
        root = main.insert(i, root)
    root = main.remove_min(root)
    captured_output = StringIO()
    sys.stdout = captured_output
    main.pre_order(root)
    sys.stdout = sys.__stdout__
    assert captured_output.getvalue() == expected