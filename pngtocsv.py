import cv2 
import numpy as np

for n in range(0,10):
    inname = str(n)+".png"
    img = cv2.imread(inname)
    mat = np.zeros((10,10))
    for i in range(0,10):
        for j in range (0,10):
            mat[i][j] =img[i][j][0]/255.0
            outname = str(n)+".csv"
    np.savetxt(outname,mat,fmt="%.3f",delimiter=",");
