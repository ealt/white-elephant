build:
	python setup.py build

install:
	python setup.py install

test:
	python white_elephant_test.py
	python perm_iter_test.py
	python heap_test.py
	python queue_test.py