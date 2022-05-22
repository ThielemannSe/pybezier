#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <string>
#include <vector>

#include <vec2.hpp>
#include <bezier.hpp>

namespace py = pybind11;

PYBIND11_MODULE(pybezier, m) {
    m.doc() = "C++ based Python extension providing functionality for bezier curves";

    // Vec2
    py::class_<PyBezier::Vec2>(m, "Vec2")
        .def(py::init<>())
        .def(py::init<float, float>())
        .def_property("x", &PyBezier::Vec2::getX, &PyBezier::Vec2::setX)
        .def_property("y", &PyBezier::Vec2::getY, &PyBezier::Vec2::setY)
        .def("length", &PyBezier::Vec2::length)
        .def("normalize", &PyBezier::Vec2::normalize)
        .def("distance", &PyBezier::Vec2::distance)

        .def("__repr__", 
            [](const PyBezier::Vec2& v) {
                return "Vec2( " + std::to_string(v.getX()) + " " + std::to_string(v.getY()) + " )";
            }
        );


    // Bezier
    py::class_<PyBezier::Bezier>(m, "Bezier")
        .def(py::init<std::vector<PyBezier::Vec2>& >())
        .def(py::init<std::vector<std::vector<float>>& >())
        .def("order", &PyBezier::Bezier::order)
        .def("length", &PyBezier::Bezier::length, py::arg("dx") = 0.01)
        .def("at", &PyBezier::Bezier::at, py::arg("t"))
        .def("multiple_at", &PyBezier::Bezier::multiple_at)
        .def("sample_equidistant", &PyBezier::Bezier::sample_equidistant)
        .def("curvature", &PyBezier::Bezier::curvature)
        .def("derivative", &PyBezier::Bezier::derivative)
        .def("__repr__", 
            [](const PyBezier::Bezier& b) {
                return "Bezier( order=" + std::to_string(b.order()) + " )";
            }
        );

}