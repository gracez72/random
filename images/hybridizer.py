from PIL import Image
from pylab import *
from numpy import *
import imgtools

# Enter size 
im_size = 200
# Insert images into empty list
im_list = []

for image in im_list:
    imresize(image,im_size)

average_im = Image.fromarray(compute_average(im_list))
average_im.save('hybridized_averaged.jpg')
