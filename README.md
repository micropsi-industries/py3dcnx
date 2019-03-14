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
```
{'val': 2, 'type': 'button'}
```
* **translate** - data fields (**x**, **y** and **z**) contain 3-axis movement
values
```
{'z': 54, 'y': 11, 'type': 'translate', 'x': -20}
```
* **rotate** - data fields (**roll**, **pitch** and **yaw**) explain rotation
around axises x, y and z, respectively.
```
{'yaw': -10, 'roll': 9, 'pitch': 104, 'type': 'rotate'}
```

### get_devices()
Returns a list of 3dconnexion SpaceNavigators connected to the system,
and their paths. Linux example:
```
['/dev/hidraw2', '/dev/hidraw3']
```

### get_event([device_number [, timeout]])
Returns an event from the spacemouse, or `None` after a timeout.
Optionally takes a device_number for identification and a value for the timeout. A timeout of `-1` makes this call blocking until the next event occurs.
