arucopy
=======

Python Marker recognition using aruco library.
This uses cv::VideoCapture to get image in c++ code.
This is not compatible with python-opencv yet.

precondition
-------------
- [aruco](http://sourceforge.net/projects/aruco/)
- boost.python

build and install
-------------

```bash
$ cd arucopy
$ python setup.py build
$ sudo python setup.py install
```

sample
-------------

```python
import arucopy
md = arucopy.MarkerDetector()
markers = md.detect() # for one shot
while True:
    md.detect()
    md.draw()
```
