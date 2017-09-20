import _py3dcnx
from threading import Thread


class SpaceMouse:
    def __init__(self, num=0):
        self.handlers = dict()
        self.num = num
        self.thread = Thread(target=self.event_loop_thread, args=(num,))
        self.thread.start()
        return

    def event_loop_thread(self, num):
        while True:
            event = _py3dcnx.get_event(self.num)
            if event is None:
                print("Cannot read from the space mouse\n")
                return
            if event['type'] in self.handlers.keys():
                self.handlers[event['type']](event)

    def register_handler(self, handler, event="all"):
        self.handlers[event] = handler
        return

    def get_devices(self):
        return _py3dcnx.get_devices()

    def get_event(self):
        return _py3dcnx.get_event(self.num)
