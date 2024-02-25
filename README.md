Customizing NeoPixel Compatible LED Ring (WS2812) colors and brightness using ILI9341 2.8" Touch Screen Lcd. The color is modulated using RGB 24 bit values that we converte automatically to 16 bit - colors setting method (setPixelColor) accepts only 16 bits RGB color

# Documentation
### **barClicked()**

Detect which bar is clicked (brightness, red, blue green)

### **lightLamp()**

light the neo pixel lamp using the RGB values picked on screen

### **decimalToBinary(int color, int array)**

transfer a color represented in decimal to binary and save it in an array passed as an argument

### **binaryToDecimal(int array)**

return decimal representation (uint16_t) of a color represented in binary (array of 8 bits)

### **brightnessInput()**

draw the brightness bar

### **modulateBrightness()**

on screen touch, reads the brightness value entered by user

### **updateBrightnessBar()**

change brightness bar width to match brightness value

### **redInput()**

draw the red bar

### **modulateRed()**

on screen touch, reads the red color value entered by user

### **updateRedBar()**

change red bar width to match red color value

### **greenInput()**

draw the green bar

### **modulateGreen()**

on screen touch, reads the green color value entered by user

### **updateGreenBar()**

change red bar width to match green color value

### **blueInput()**

draw the blue bar

### **modulateBlue()**

on screen touch, reads the blue color value entered by user

### **updateBlueBar()**

change red bar width to match blue color value

### **displayColorOnScreen()**

draw the rectangle that displays the current choosed color

### **updateColorOnScreen()**

on modifying r g b values update the color displayed on screen

### **display()**

populate the screen (r g b brightness bars + color)

