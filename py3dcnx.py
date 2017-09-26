import _py3dcnx
from multiprocessing import Process

event_types = ['button', 'rotate', 'translate']


class SpaceMouse:
    def __init__(self, num=0):
        self.handlers = dict()
        self.num = num
        self.start()
        return

    def start(self):
        self.thread = Process(target=self.event_loop_thread, args=(self.num,))
        self.thread.start()

    def event_loop_thread(self, num):
        while True:
            event = _py3dcnx.get_event(self.num)
            if event is None:
                print("Cannot read from the space mouse\n")
                return
            if event['type'] in self.handlers.keys():
                self.handlers[event['type']](event)

    def register_handler(self, handler, event='all', data=None):
        self.thread.terminate()
        if event is 'all':
            for e in event_types:
                self.handlers[e] = handler
        elif event in event_types:
            self.handlers[event] = handler
        self.start()

    def get_devices(self):
        return _py3dcnx.get_devices()

    def get_event(self):
        return _py3dcnx.get_event(self.num)
