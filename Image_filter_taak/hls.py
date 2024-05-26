from pynq import Overlay, allocate
import numpy as np
from PIL import Image


class addresses:
    input_buffer = 0x10
    output_buffer = 0x1c
    image_width = 0x10
    image_height = 0x18
    num_channels = 0x24
    start = 0x00
    status = 0x04

addresses = addresses()

image_path = 'test.jpg'  # Replace with the actual path to your image
image = Image.open(image_path)
image_width, image_height = image.size
num_channels = len(image.getbands())
length = image_width * image_height * num_channels
image_list = np.array(list(image.getdata()), dtype=np.uint8)
print("image loaded as list")
image.close()
print("starting")
ol = Overlay('Applyconvolution.bit')

convolution_ip = ol.applyConvolution_0
print("init complete")




print("allocating buffers")
input_buffer = allocate(shape=(length,), dtype=np.uint8)
output_buffer = allocate(shape=(length,), dtype=np.uint8)
print("buffers allocated")
print("copying data to input buffer")
reshaped_image_list = image_list.reshape((length,))
np.copyto(input_buffer, reshaped_image_list)
print("data copied to input buffer")



print("starting convolution")
convolution_ip.s_axi_control.write(addresses.input_buffer, input_buffer.device_address)
convolution_ip.s_axi_control.write(addresses.output_buffer, output_buffer.device_address)
convolution_ip.s_axi_control.write(addresses.image_width, image_width)
convolution_ip.s_axi_control.write(addresses.image_height, image_height)
convolution_ip.s_axi_control.write(addresses.num_channels, num_channels)
convolution_ip.s_axi_control.write(addresses.start, 0x01)
print("convolution started")
print("waiting for completion")
while convolution_ip.s_axi_control.read(addresses.start) & addresses.status == 0:
    pass
print("convolution complete")
output_list = output_buffer.tolist()
output_image = Image.frombytes('RGB', (image_width, image_height), bytes(output_list))
output_image.save('output.jpg')
print("output saved as output.jpg")
output_image.close()