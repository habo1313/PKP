from libcpp.string cimport string
from libcpp.vector cimport vector
from libcpp cimport bool

cdef extern from "reactor.hpp" namespace "pkp":
    cdef cppclass CxxReactor "pkp::Reactor":
        CxxReactor(string, vector[double])
        void solve(double t, double T, double dt, bool verbose)
        vector[double] getParameters()
        vector[double] getTimes()
        vector[vector[double]] getStates()
        void dump(string csv, string sep)
        void printParameters()


cdef class Reactor:
    cdef CxxReactor* _c_reactor
    def __cinit__(self, name, parameters):
        cdef string c_name = name.encode()
        cdef vector[double] c_parameters = parameters
        self._c_reactor = new CxxReactor(c_name, c_parameters)

    def solve(self, t, T, dt, verbose=True):
        cdef double t_c = t
        cdef double T_c = T
        cdef double dt_c = dt
        cdef bool verbose_c = verbose
        self._c_reactor.solve(t_c, T_c, dt_c, verbose_c)
