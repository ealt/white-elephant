from distutils.core import setup, Extension

we_module = Extension('white_elephant', sources=['white_elephant.c'])

setup(ext_modules=[we_module])