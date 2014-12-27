#include <iostream>

#include <aruco/aruco.h>
#include <aruco/cvdrawingutils.h>
#include <boost/python.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>

class MarkerDetector {
public:
  MarkerDetector()
    : m_cap()
    , m_detector()
    , m_markers()
    , m_img() {
    m_cap.set(CV_CAP_PROP_FORMAT, CV_8UC1);
    if (!m_cap.open()) {
      std::cerr << "failed to open camera" << std::endl;
    }
  }
  ~MarkerDetector() {
    m_cap.release();
  }
  boost::python::list detect() {
    m_markers.clear();
    m_cap.grab();
    m_cap.retrieve(m_img);
    m_detector.detect(m_img, m_markers);
    boost::python::list py_list;
    for (std::vector<aruco::Marker>::const_iterator it = m_markers.begin();
	 it != m_markers.end(); ++it) {
      boost::python::dict py_dict;
      py_dict["id"] = it->id;
      py_dict["center_x"] = it->getCenter().x;
      py_dict["center_y"] = it->getCenter().y;
      py_dict["area"] = it->getArea();
      py_list.append(py_dict);
    }
    return py_list;
  }

  void draw() {
    for (unsigned int i = 0; i < m_markers.size(); ++i) {
      std::cout << m_markers[i] << std::endl;
      m_markers[i].draw(m_img, cv::Scalar(0, 0, 255), 2);
    }
    cv::imshow("markers", m_img);
    cv::waitKey(1);
  }

private:
  raspicam::RaspiCam_Cv m_cap;
  aruco::MarkerDetector m_detector;
  std::vector<aruco::Marker> m_markers;
  cv::Mat m_img;
};

BOOST_PYTHON_MODULE(arucopy) {
  boost::python::class_<MarkerDetector>("MarkerDetector")
    .def("detect", &MarkerDetector::detect)
    .def("draw", &MarkerDetector::draw);
}
