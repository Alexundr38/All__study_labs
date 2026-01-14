class Figure:
    def __init__(self,perimeter,area,color):
        if isinstance(perimeter,int) and perimeter>0 and isinstance(area,int) and area>0 and (color=='r' or color=='b' or color=='g'):
            self.perimeter = perimeter
            self.area = area
            self.color = color
        else:
            raise ValueError('Invlaid value')


class Polygon(Figure): #Наследуется от класса Figure
    def __init__(self,perimeter,area,color,angle_count,equilateral,biggest_angle):
        if isinstance(perimeter,int) and isinstance(area,int) and isinstance(angle_count,int) and isinstance(equilateral,bool) and isinstance(biggest_angle,int) and (equilateral==True or equilateral==False) and biggest_angle>0 and  perimeter>0 and area>0 and angle_count>2 and (color=='r' or color=='b' or color=='g'):
            super().__init__(perimeter, area, color)
            self.angle_count = angle_count
            self.equilateral = equilateral
            self.biggest_angle = biggest_angle
        else:
            raise ValueError('Invalid value')
    def __str__(self):
        return f'Polygon: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, количество углов {self.angle_count}, равносторонний {self.equilateral}, самый большой угол {self.biggest_angle}.'
    def __add__(self):
        return self.perimeter+self.area
    def __eq__(self,other):
        return self.perimeter==other.perimeter and self.area==other.area and self.angle_count==other.angle_count




class Circle(Figure):  # Наследуется от класса Figure
    def __init__(self,perimeter,area,color,radius,diametr):
        if isinstance(perimeter,int) and isinstance(area,int) and isinstance(radius,int) and isinstance(diametr,int) and perimeter>0 and area>0 and radius>0 and diametr==2*radius and (color=='r' or color=='b' or color=='g'):
            super().__init__(perimeter, area, color)
            self.radius = radius
            self.diametr = diametr
        else:
            raise ValueError('Invalid value')
    def __str__(self):
        return f'Circle: Периметр {self.perimeter}, площадь {self.area}, цвет фигуры {self.color}, радиус {self.radius}, диаметр {self.diametr}.'
    def __add__(self):
        return self.perimeter+self.area
    def __eq__(self,other):
        return self.radius==other.radius



class PolygonList(list):
    def __init__(self,name):
        self.name=name
    def append(self,p_object):
        if isinstance(p_object,Polygon):
            super().append(p_object)
        else:
            raise TypeError(f'Invalid type {type(p_object)}')
    def print_colors(self):
        counts=1
        for item in self:
            print(f'{counts} многоугольник: {item.color}')
            counts+=1
    def print_count(self):
        print(len(self))



class CircleList(list):
    def __init__(self, name):
        self.name=name
    def extend(self,iterable):
        super().extend(list(filter(lambda item: isinstance(item,Circle),iterable)))
    def print_colors(self):
        counts=1
        for item in self:
            print(f'{counts} окружность: {item.color}')
            counts+=1
    def total_area(self):
        print(sum(item.area for item in self))

