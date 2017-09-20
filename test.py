from py3dcnx import SpaceMouse


def button(event):
    print(event)


sm = SpaceMouse()
sm.register_handler(button, "button")
