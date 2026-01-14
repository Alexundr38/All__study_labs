import numpy as np


def check_collision(bot1, bot2):
    nbot1=list(bot1)
    nbot2=list(bot2)
    matr=np.array([[nbot1[0],nbot1[1]],[nbot2[0],nbot2[1]]])
    ans=np.array([-nbot1[2],-nbot2[2]])
    if np.linalg.matrix_rank(matr)<2:
        return None
    else:
        answer=tuple(np.round(np.linalg.solve(matr,ans),2))
        return answer
        
        
def check_surface(point1, point2, point3):
    npoint1=list(point1)
    npoint2=list(point2)
    npoint3=list(point3)
    matr=np.array([[npoint1[0],npoint1[1],1],[npoint2[0],npoint2[1],1],[npoint3[0],npoint3[1],1]])
    ans=np.array([npoint1[2],npoint2[2],npoint3[2]])
    if np.linalg.matrix_rank(matr)<3:
        return None
    else:
        answer=np.round(np.linalg.solve(matr,ans),2)
        return answer
        
        
def check_rotation(vec, rad):
    c=np.cos(rad)
    s=np.sin(rad)
    round_z=np.array([[c,-s,0],[s,c,0],[0,0,1]])
    answer=np.round(round_z.dot(vec),2)
    return answer
