from distutils.core import setup, Extension
import yaml

with open('config.yaml', 'r') as f:
    config = yaml.safe_load(f)

py_pkgs_path = config['py_pkgs_path']

we_module = Extension('white_elephant',
                      sources=[
                          'white_elephant.c',
                          'simulate.c',
                          'count_array.c',
                      ],
                      include_dirs=[f'{py_pkgs_path}/numpy/core/include/'])

pi_module = Extension('perm_iter',
                      sources=[
                          'perm_iter_mod.c',
                          'perm_iter.c',
                      ],
                      include_dirs=[f'{py_pkgs_path}/numpy/core/include/'])

setup(ext_modules=[we_module, pi_module])
