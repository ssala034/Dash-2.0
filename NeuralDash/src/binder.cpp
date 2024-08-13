#include <pybind11/pybind11.h>
#include "mymath.hpp"
#include <vector>
#include "../../player.hpp"
#include "../../collisions.hpp"
#include "../../objects.hpp"
#include "../../NeuralNet.hpp"
#include "../../window.hpp"
#include "../../gameEngine.hpp"


#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)



namespace py = pybind11;

PYBIND11_MODULE(dash_bindings, m_handle) {
    m_handle.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: cmake_example

        .. autosummary::
           :toctree: _generate

           add
           subtract
            & more
    )pbdoc";

    m_handle.def("add", &add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");

    m_handle.def("subtract", [](int i, int j) { return i - j; });

    py::class_<gameEngine::Player>(m_handle, "PyPlayer").def(py::init<>());
    py::class_<gameEngine::Objects>(m_handle, "PyObjects").def(py::init<int>());
    m_handle.def("getID", &gameEngine::Objects::getId);
    m_handle.def("get_position", &gameEngine::Objects::getPosition);
    m_handle.def("get_spirte", &gameEngine::Objects::getPosition);
    m_handle.def("spawn", &gameEngine::Player::spawn);
    m_handle.def("get_position", &gameEngine::Player::getPosition);
    m_handle.def("move", &gameEngine::Player::move);
    m_handle.def("update", &gameEngine::Player::update);
    m_handle.def("reset", &gameEngine::Player::reset);
    m_handle.def("jump", &gameEngine::Player::jump);
    m_handle.def("can_jump", &gameEngine::Player::canJump);
    m_handle.def("createGame", &gameEngine::createGame);
    m_handle.def("window", &gameEngine::window::createWindow).def(py::<init>(gameEngine::Player & player));
    m_handle.def("collision2" &gameEngine::checkCollision);
    m_handle.def("collision", &gameEngine::checkCollisionFromTop);





#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
