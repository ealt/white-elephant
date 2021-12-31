from distutils.core import setup, Extension
import yaml

with open('config.yaml', 'r') as f:
    config = yaml.safe_load(f)

py_lib_path = config['py_lib_path']

we_module = Extension(
    'white_elephant',
    sources=[
        'white_elephant.c',
        'simulate.c',
    ],
    include_dirs=[f'{py_lib_path}/dist-packages/numpy/core/include/'])

setup(ext_modules=[we_module])
