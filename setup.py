from distutils.core import setup, Extension
import sys

platform = sys.platform

if 'linux' in platform:
    module1 = Extension('_py3dcnx', sources=['py3dcnx.c', 'py3dcnx_hidapi.c',
                                             'hidapi/hid-linux.c'],
                        libraries=['udev'])
elif platform == 'darwin':
    module1 = Extension('_py3dcnx', sources=['py3dcnx.c', 'py3dcnx_hidapi.c',
                                             'hidapi/hid-mac.c'],
                        extra_link_args=['-framework', 'IOKit', '-framework',
                                         'CoreFoundation'])
elif 'win' in platform:
    module1 = Extension('_py3dcnx',
                        sources=['py3dcnx.c', 'py3dcnx_hidapi.c',
                                 'hidapi/hid-win.c'],
                        libraries=['setupapi'])

setup(name='Py3Dcnx',
      version='1.1',
      description='Python module for interfacing 3Dconnexion mice',
      ext_modules=[module1], py_modules=['py3dcnx'])
