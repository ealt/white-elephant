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
                          'perm_iter.c',
                          'elem.c',
                          'heap.c',
                          'queue.c',
                      ],
                      include_dirs=[f'{py_pkgs_path}/numpy/core/include/'])

pi_module = Extension('perm_iter',
                      sources=[
                          'perm_iter_mod.c',
                          'perm_iter.c',
                      ],
                      include_dirs=[f'{py_pkgs_path}/numpy/core/include/'])

h_module = Extension('heap',
                     sources=[
                         'heap_mod.c',
                         'heap.c',
                         'elem.c',
                     ],
                     include_dirs=[f'{py_pkgs_path}/numpy/core/include/'])

q_module = Extension('my_queue',
                     sources=[
                         'queue_mod.c',
                         'queue.c',
                         'elem.c',
                     ],
                     include_dirs=[f'{py_pkgs_path}/numpy/core/include/'])

setup(ext_modules=[we_module, pi_module, h_module, q_module])
