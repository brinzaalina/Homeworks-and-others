# A. Display an image with pillow:

# load and show an image with Pillow
from PIL import Image
# load the image
image = Image.open('f1.jpg')
# summarize some details about the image
print(image.format)
print(image.mode)
print(image.size)
# show the image
image.show()

# B. Convert the image to a numpy array:

# load and display an image with Matplotlib
from matplotlib import image
from matplotlib import pyplot
# load image as pixel array
data = image.imread('f1.jpg')
# summarize shape of the pixel array
print(data.dtype)
print(data.shape)
# display the array of pixels as an image
pyplot.imshow(data)
pyplot.show()

# C. Resize an image to a specific dimension:

# create a thumbnail of an image
# load the image

image = Image.open('f1.jpg')
# report the size of the image
print(image.size)
# create a thumbnail and preserve aspect ratio
image.thumbnail((100,100))
# report the size of the thumbnail
print(image.size)
