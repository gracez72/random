from PIL import Image
from scipy.ndimage import filters
from numpy import *

im = array(Image.open('bird.jpg').convert('L'))
im2 = filters.gaussian_filter(im,5)
gaussian_bw = Image.fromarray(im2)
gaussian_bw.save('gaussian_b&w.jpg')

im_colour = array(Image.open('bird.jpg'))
im3 = zeros(im.shape)
for i in range(3):
    im3[:,:,i] = filters.gaussian_filter(im[:,:,i],5)

im3 = uint8(im3)
gaussian_colour = Image.fromarray(im3)
gaussian_colour.save('gaussian_colour.jpg')
