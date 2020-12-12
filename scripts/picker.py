import time
import os, sys, inspect

from PyQt5.QtWidgets import * 
from PyQt5 import QtCore, QtGui 
from PyQt5.QtGui import * 
from PyQt5.QtCore import * 

# Add 'simpap' to the import path
currentdir = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
parentdir = os.path.dirname(currentdir)
sys.path.insert(0, parentdir) 

import simpap
  
# Interface to LED strip
c = simpap.Blueled('/dev/ttyUSB0')
num_leds = 120
c.set_leds(num_leds)
  
class Window(QMainWindow): 
  
    def __init__(self): 
        super().__init__() 
  
        # setting title 
        self.setWindowTitle("Python ") 
  
        # setting geometry 
        self.setGeometry(100, 100, 500, 400) 
  
        # calling method 
        self.UiComponents() 
  
        # showing all the widgets 
        self.show() 
  
  
    # method for components 
    def UiComponents(self): 
  
        # creating a QColorDialog object 
        self.dialog = QColorDialog(self) 
  
        # getting color changed signal 
        # when signal receives print the message 
        self.dialog.currentColorChanged.connect(self.update_color) 
  
        # setting current color 
        self.dialog.setCurrentColor(Qt.red) 
  
        # executing the dialog 
        self.dialog.exec_() 

    def update_color(self):
        c.solid(int(self.dialog.currentColor().name()[1:], 16))
  
# create pyqt5 app 
App = QApplication(sys.argv) 
  
# create the instance of our Window 
window = Window() 
  
# start the app 
sys.exit(App.exec()) 
