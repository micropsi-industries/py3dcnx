# Py3Dcnx
A Python module that provides cross-platform access to 3dconnexion
SpaceNavigator

### Usage
* Import the SpaceMouse class from the package
```
from py3dcnx import SpaceMouse
```
* Create an event callback
```
def button(event):
    print(event)
```
* Create a new instance and assign the callback to the "button" event
```
sm = SpaceMouse()
sm.register_handler(button, "button")
```
