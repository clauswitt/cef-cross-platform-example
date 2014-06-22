#ifndef EXAMPLE_HPP 
#define EXAMPLE_HPP 

#include "include/cef_client.h"

class ExampleRequestContextHandler : public CefRequestContextHandler {
public:
  ExampleRequestContextHandler() : refct_() { }
  ~ExampleRequestContextHandler() { }
  IMPLEMENT_REFCOUNTING(ExampleRequestContextHandler)
};

class ExampleHandler : public CefClient {
public:
  ExampleHandler() : refct_() { }
  ~ExampleHandler() { }
  IMPLEMENT_REFCOUNTING(ExampleHandler)
};

#endif
