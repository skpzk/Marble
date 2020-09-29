#ifndef debugutils_h_
#define debugutils_h_
#define REPORT

#include <iostream>
#include <string>

void dline();

#ifdef REPORT
  // class to capture the caller and print it.  
  class Reporter
  {
    public:
      Reporter(std::string Caller, std::string File, int Line)
        : caller_(Caller)
        , file_(File)
        , line_(Line)
      {}

      std::string operator()();

    private:
      std::string   caller_;
      std::string   file_;
      int           line_;

  };

// remove the symbol for the function, then define a new version that instead
// creates a stack temporary instance of Reporter initialized with the caller
#  undef dline
#  define dline Reporter(__FUNCTION__,__FILE__,__LINE__)
#endif

/*
void Caller2()
{
  // Works for inline as well.
  std::cout << dline() << "output here" << std::endl;
}*/

#endif