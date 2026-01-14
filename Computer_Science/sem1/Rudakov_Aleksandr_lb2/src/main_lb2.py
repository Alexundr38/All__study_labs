# Задача 1
def user_func(image, x0, y0, x1, y1, fill, width):
    drawing=ImageDraw.Draw(image)
    drawing.line(((x0,y0),(x1,y1)),fill,width)
    return image

# Задача 2
def check_coords(image, x0, y0, x1, y1):
    count=0
    if x0<0 or x1<0 or y0<0 or y1<0:
        count+=1
    width,height=image.size
    if x0>width or x1>width or y0>height or y1>height:
        count+=1
    if x0>x1 or y0>y1:
        count+=1
    if count==0:
        return True
    else:
        return False

def set_black_white(image, x0, y0, x1, y1):
    if check_coords(image,x0,y0,x1,y1):
        polygon=image.crop((x0,y0,x1,y1))
        polygon_new=polygon.convert('1')
        image.paste(polygon_new,(x0,y0))
    return image

# Задача 3
def find_rect_and_recolor(image, old_color, new_color):
    old_color_new = tuple(old_color)
    new_color_new = tuple(new_color)
    max_volume=0
    width, height = image.size
    pixels = image.load()
    coor_x0 = coor_x1 = coor_y0 = coor_y1 =0
    for x in range(width):
        for y in range(height):
            if pixels[x,y]==old_color_new:
                x0_new = x1_new = x
                y0_new = y1_new = y
                while pixels[x1_new,y1_new]==old_color_new:
                    y1_new+=1
                    if y1_new==height:
                        break
                y1_new -= 1
                while pixels[x1_new,y1_new]==old_color_new:
                    x1_new+=1
                    if x1_new==width:
                        break
                x1_new -= 1
                volume=(x1_new-x0_new+1)*(y1_new-y0_new+1)
                if volume>max_volume:
                    max_volume=volume
                    coor_x0=x0_new
                    coor_x1=x1_new
                    coor_y0=y0_new
                    coor_y1=y1_new
    for y in range(coor_y0, coor_y1 + 1):
        for x in range(coor_x0, coor_x1 + 1):
            pixels[x, y] = new_color_new
    return image
    
