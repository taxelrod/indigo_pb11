// Package up a few functions for pybind11

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include "indigo_bus.h"
//#include "indigo_client.h"
//#include "indigo_xml.h"
#include <string.h>
#include <iostream>

extern "C" int wrap_attach(int i);
    

indigo_client *buildClient(std::function<int(int)>  attach_func) {
  
  class wrap {
  public:
    std::function<int(int)> wrap_func;
    
    wrap(std::function<int(int)> func) {
      wrap_func = func;
    }

    int wrap_attach(int i) {
      return wrap_func(i);
    }
  };

  wrap w(attach_func); 

  indigo_client *c = new indigo_client;
  c->attach = w.wrap_attach;
  std::cout << "attach from inside buildClient: " << (attach_func)(10) << '\n';;
  return c;
}

namespace py = pybind11;

PYBIND11_MODULE(i_client, m) {
  py::class_<indigo_client>(m, "Client")
    .def_readwrite("is_remote", &indigo_client::is_remote)
    .def_readwrite("attach", &indigo_client::attach) ;
  py::enum_<indigo_result>(m, "IndigoResult")
    .value("INDIGO_OK", INDIGO_OK)
    .export_values();

  m.def("buildClient", &buildClient);
}

