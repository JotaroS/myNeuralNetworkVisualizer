import cv2
import numpy as np
from PIL import Image
import scipy as sp
import scipy.misc
import os
list=os.listdir('./outimage/');
for file in list:
    data = np.loadtxt(open("./outimage/"+str(file),"rb"),delimiter=",",skiprows=0);
    out = np.array(data);
    sp.misc.imsave('./outimage/'+str(file)+'.png',out);
