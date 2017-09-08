from distutils.core import setup, Extension

module1 = Extension('py3dcnx',
                    sources=['py3dcnx.c', 'py3dcnx_hidapi.c'])

setup(name='Py3Dcnx',
      version='1.0',
      description='Python module for interfacing 3Dconnexion mice',
      ext_modules=[module1])
