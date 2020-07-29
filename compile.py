import os

os.system("cmake .")
os.system("make SpreadSimulation")

os.chdir("SpreadSimGUI")
os.system("qmake PandemiC.pro CONFIG+=debug CONFIG+=qml_debug")
os.system("make -j8")

os.chdir("../")
os.system("cp SpreadSimulation SpreadSimGUI")
