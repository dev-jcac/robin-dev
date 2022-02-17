from cgi import test
import sys
from PyQt5.uic import loadUi
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QDialog, QApplication, QWidget

class WelcomeScreen(QDialog):
    def __init__(self):
        super(WelcomeScreen, self).__init__()
        loadUi("welcomescreen.ui", self)
        self.tapToStartButton.clicked.connect(self.goto1stpage)

    def goto1stpage(self):
        firstpage = FirstPage()
        widget.addWidget(firstpage)
        widget.setCurrentIndex(widget.currentIndex()+1)

class FirstPage(QDialog):
    def __init__(self):
        super(FirstPage, self).__init__()
        loadUi("firstpage.ui", self)


#main
app = QApplication(sys.argv)
welcome = WelcomeScreen()
widget = QtWidgets.QStackedWidget()
widget.addWidget(welcome)
widget.setFixedHeight(480)
widget.setFixedWidth(800)
widget.show()
try:
    sys.exit(app.exec())

except:
    print("Exiting...")
