from py3dcnx import SpaceMouse

buttons = 0


def button(event):
    global buttons
    new_buttons = event['val']
    changes = new_buttons ^ buttons
    if changes is not 0:
        for i in range(2):
            if changes & (1 << i):
                if new_buttons & (1 << i):
                    print('Button %d is down' % (i+1))
                else:
                    print('Button %d is up' % (i+1))
    buttons = new_buttons


sm = SpaceMouse()
sm.register_handler(button, "button")
