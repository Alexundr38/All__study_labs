import pytest
import ETurbo
from io import StringIO
import sys

@pytest.mark.parametrize('arr, expected', [
    ([[1,'A'], [2, 'B'], [3, 'C']], ['h: 1   left: x center: Score: 1, Names: A right: x',
                                     'h: 1   left: x center: Score: 3, Names: C right: x',
                                     'h: 2   left: Score: 1, Names: A center: Score: 2, Names: B right: Score: 3, Names: C']),
    ([[3, 'A'], [2, 'B'], [1, 'C']], ['h: 1   left: x center: Score: 1, Names: C right: x',
                                      'h: 1   left: x center: Score: 3, Names: A right: x',
                                      'h: 2   left: Score: 1, Names: C center: Score: 2, Names: B right: Score: 3, Names: A']),
    ([[2, 'A'], [5, 'B'], [1, 'C'], [6, 'D'], [4, 'E'], [3, 'F']], ['h: 1   left: x center: Score: 1, Names: C right: x',
                                                                    'h: 1   left: x center: Score: 3, Names: F right: x',
                                                                    'h: 2   left: Score: 1, Names: C center: Score: 2, Names: A right: Score: 3, Names: F',
                                                                    'h: 1   left: x center: Score: 6, Names: D right: x',
                                                                    'h: 2   left: x center: Score: 5, Names: B right: Score: 6, Names: D',
                                                                    'h: 3   left: Score: 2, Names: A center: Score: 4, Names: E right: Score: 5, Names: B']),
    ([[6, 'A'], [5, 'B'], [2, 'C'], [1, 'D'], [3, 'E'], [4, 'F']], ['h: 1   left: x center: Score: 1, Names: D right: x',
                                                                    'h: 2   left: Score: 1, Names: D center: Score: 2, Names: C right: x',
                                                                    'h: 1   left: x center: Score: 4, Names: F right: x',
                                                                    'h: 1   left: x center: Score: 6, Names: A right: x',
                                                                    'h: 2   left: Score: 4, Names: F center: Score: 5, Names: B right: Score: 6, Names: A',
                                                                    'h: 3   left: Score: 2, Names: C center: Score: 3, Names: E right: Score: 5, Names: B']),
    ([[1, 'A'], [2, 'B'], [3, 'C'], [1, 'F']], ['h: 1   left: x center: Score: 1, Names: A, F right: x',
                                                'h: 1   left: x center: Score: 3, Names: C right: x',
                                                'h: 2   left: Score: 1, Names: A, F center: Score: 2, Names: B right: Score: 3, Names: C'])
])
def test_insert(arr, expected):
    root_score = None
    for i in arr:
        root_score = ETurbo.insert(i[0], i[1], root_score)
    captured_output = StringIO()
    sys.stdout = captured_output
    ETurbo.post_order(root_score)
    sys.stdout = sys.__stdout__
    assert list(captured_output.getvalue().split('\n'))[:-1] == expected

@pytest.mark.parametrize('arr, find_score, expected', [
    ([[2, 'A'], [4, 'B'], [1, 'C'], [8, 'D']], 1, 'Score: 1, Name: C; Sub: 0'),
    ([[2, 'A'], [4, 'B'], [1, 'C'], [8, 'D']], 5, 'Score: 4, Name: B; Sub: -1'),
    ([[2, 'A'], [4, 'B'], [1, 'C'], [8, 'D']], 7, 'Score: 8, Name: D; Sub: 1'),
    ([[2, 'A'], [4, 'B'], [1, 'C'], [8, 'D']], 3, 'Score: 4, Name: B; Sub: 1')
])
def test_find(arr, find_score, expected):
    root_score = None
    for i in arr:
        root_score = ETurbo.insert(i[0], i[1], root_score)
    out_str = '; Sub: '.join(map(str, ETurbo.find(root_score, find_score)))
    assert out_str == expected

@pytest.mark.parametrize('arr, min_value, expected', [
    ([[10, 'A'], [17, 'B'], [7, 'C'], [18, 'D'], [14, 'E'], [12, 'F'], [11, 'G'], [13, 'H'], [1, 'I'], [4, 'J'], [16, 'K'], [15, 'L'], [19, 'M'], [20, 'N']],
     16, ['Score: 17, Name: B','Score: 18, Name: D','Score: 19, Name: M','Score: 20, Name: N']),
    ([[10, 'A'], [17, 'B'], [7, 'C'], [18, 'D'], [14, 'E'], [12, 'F'], [11, 'G'], [13, 'H'], [1, 'I'], [4, 'J'], [16, 'K'], [15, 'L'], [19, 'M'], [20, 'N']],
     6, ['Score: 7, Name: C','Score: 10, Name: A','Score: 11, Name: G','Score: 12, Name: F','Score: 13, Name: H','Score: 14, Name: E',
         'Score: 15, Name: L','Score: 16, Name: K','Score: 17, Name: B','Score: 18, Name: D','Score: 19, Name: M','Score: 20, Name: N']),
    ([[10, 'A'], [17, 'B'], [7, 'C'], [18, 'D'], [14, 'E'], [12, 'F'], [11, 'G'], [13, 'H'], [1, 'I'], [4, 'J'], [16, 'K'], [15, 'L'], [19, 'M'], [20, 'N'], [17, 'O'], [19, 'Z']],
     14, ['Score: 15, Name: L','Score: 16, Name: K','Score: 17, Name: B','Score: 17, Name: O','Score: 18, Name: D',
          'Score: 19, Name: M','Score: 19, Name: Z','Score: 20, Name: N'])
])
def test_print_biggest(arr, min_value, expected):
    root_score = None
    for i in arr:
        root_score = ETurbo.insert(i[0], i[1], root_score)
    captured_output = StringIO()
    sys.stdout = captured_output
    ETurbo.print_biggest(root_score, min_value)
    sys.stdout = sys.__stdout__
    assert list(captured_output.getvalue().split('\n'))[:-1] == expected