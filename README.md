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

### Events
Event dictionaries contain the information about their type and the corresponding data.

There are 3 types of supported events:
* **button** - data field (**val**) contains the bitmap of currently
pressed buttons in the lowest 2 bits.
* **translate** - data fields (**x**, **y** and **z**) contain 3-axis movement
values
* **rotate** - data fields (**roll**, **pitch** and **yaw**) explain rotation
around axises x, y and z, respectively.

### get_devices()
Returns a list of 3dconnexion SpaceNavigators connected to the system,
and their paths. Linux example:
```
['/dev/hidraw2', '/dev/hidraw3']
```

### get_event()
Blocking call, with an optional device number as a parameter. Waits for the
event and returns an event dictionary.
