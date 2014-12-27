arucopy
=======

aruco library for boost.python

precondition
-------------
- [aruco](http://sourceforge.net/projects/aruco/)
- boost.python
- python2.7 (If you want to use different version, edit CMakeLists.txt)

build
-------------

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
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
