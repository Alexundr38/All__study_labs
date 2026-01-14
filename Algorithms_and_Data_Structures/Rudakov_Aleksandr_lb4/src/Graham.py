def rotate(point1, point2, point3):
    return (point2[0]-point1[0])*(point3[1]-point2[1]) - (point2[1]-point1[1])*(point3[0]-point2[0])

def sort_point(points):
    for i in range(1, len(points)):
        for j in range(i, 1, -1):
            if rotate(points[0], points[j], points[j-1]) > 0:
                points[j], points[j-1] = points[j-1], points[j]
    return points

def get_convex_surface(points):
    new_points = points[:2]
    for i in range(2, len(points)):
        while rotate(new_points[-2], new_points[-1], points[i]) < 0:
            new_points.pop()
        new_points.append(points[i])
    return new_points

def area(points):
    result = 0
    length = len(points)
    for i in range(length):
        result += points[i % length][0] * points[(i+1) % length][1]
        result -= points[(i+1) % length][0] * points[i % length][1]
    result /= 2
    return result

if __name__ =="__main__":
    n = int(input())
    points = []
    min_point = []
    for i in range(n):
        current_point = list(map(int, input().split(', ')))
        points.append(current_point)
        if points[i][0] < points[0][0]:
            points[i], points[0] = points[0], points[i]

    points = sort_point(points)
    new_points = get_convex_surface(points)
    result_area = area(new_points)
    print(f'({new_points}, {result_area})')

