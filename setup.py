from distutils.core import setup, Extension
import sys

platform = sys.platform

if 'linux' in platform:
    module1 = Extension('py3dcnx', sources=['py3dcnx.c', 'py3dcnx_hidapi.c'],
                        libraries=['hidapi-hidraw'])
elif platform == 'darwin':
    module1 = Extension('py3dcnx', sources=['py3dcnx.c', 'py3dcnx_hidapi.c'],
                        libraries=['hidapi'])
elif 'win' in platform:
    module1 = Extension('py3dcnx',
                        sources=['py3dcnx.c', 'py3dcnx_hidapi.c'],
                        library_dirs=['/usr/local/lib'],
                        libraries=['hidapi'])


setup(name='Py3Dcnx',
      version='1.0',
      description='Python module for interfacing 3Dconnexion mice',
      ext_modules=[module1])
