import _py3dcnx
import threading

event_types = ['button', 'rotate', 'translate']


class SpaceMouse:

    def __init__(self, num=0):
        self.handlers = dict()
        self.num = num
        self.end = False
        self.read_timeout = 100
        self.start()

    def start(self):
        self.end = False
        self.thread = threading.Thread(target=self.event_loop_thread, args=(self.num,))
        self.thread.start()

    def event_loop_thread(self, num):
        while not self.end:
            event = _py3dcnx.get_event(self.num, self.read_timeout)
            if event and event['type'] in self.handlers.keys():
                self.handlers[event['type']](event)

    def register_handler(self, handler, event='all', data=None):
        self.end = True
        self.thread.join(1)
        if event is 'all':
            for e in event_types:
                self.handlers[e] = handler
        elif event in event_types:
            self.handlers[event] = handler
        self.start()

    def get_event(self):
        return _py3dcnx.get_event(self.num)

    def shutdown(self):
        self.end = True
        self.thread.join(1)
        self.handlers.clear()

    @staticmethod
    def get_devices():
        return _py3dcnx.get_devices()
