Customizing NeoPixel Compatible LED Ring (WS2812) colors and brightness using ILI9341 2.8" Touch Screen Lcd, the color is modulated using RGB 24 bit values.

![Screenshot (504)](https://github.com/NBAmine/Lamp-with-customized-colors/assets/86920473/7fdbf755-d167-4b3e-b724-b4cbb852f5dc)

### Note :
Later in the code, the conversion from RGB 24 bits to RGB 16 bits is due to a method (fillRoudRect) that accepts only uint16_t colors as arguments, we use this function to represent the resulting color on screen from different r g b values selected

# Documentation
### **barClicked()**

Detect which bar is clicked (brightness, red, blue green)

### **lightLamp()**

light the neo pixel lamp using the RGB values picked on screen

### **decimalToBinary(int color, int array)**

transfer a color represented in decimal to binary and save it in an array passed as an argument - in our case, the array is a global variable-

### **binaryToDecimal(int array)**

return decimal representation (uint16_t) of a color represented in binary (array of 16 bits)

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

