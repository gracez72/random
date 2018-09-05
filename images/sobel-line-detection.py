from PIL import Image
from numpy import *
from scipy.ndimage import filters

im = array(Image.open('1024x768_2.jpg').convert('L'))

#Sobel derivative filters
imx = zeros(im.shape)
filters.sobel(im,1,imx)

imy = zeros(im.shape)
filters.sobel(im,0,imy)

magnitude = sqrt(imx**2+imy**2)
output = Image.fromarray(uint8(magnitude))
output.save('sobel.jpg')
