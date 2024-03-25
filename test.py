from py3dcnx import SpaceMouse

buttons = 0


class Listener():
    def __init__(self):
        self.name = 'ButtonListener'

    def button(self, event):
        global buttons
        new_buttons = event['val']
        changes = new_buttons ^ buttons
        if changes is not 0:
            for i in range(2):
                if changes & (1 << i):
                    print(self.name+':')
                    if new_buttons & (1 << i):
                        print('Button %d is down' % (i+1))
                    else:
                        print('Button %d is up' % (i+1))
        buttons = new_buttons


ls = Listener()
sm = SpaceMouse()
print("devices found: ", SpaceMouse.get_devices())
sm.register_handler(ls.button, "button")
