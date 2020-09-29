#include "DebugUtils.h"

#ifdef REPORT

std::string Reporter::operator()()
      {
        if(file_.compare(0, 3, "../") == 0){
            return caller_ + "() in " + file_.substr(2) + "(" + std::to_string(line_) + "): ";
      	}else if(file_.compare(0, 3, "./") == 0){
            return caller_ + "() in /Utils" + file_.substr(2) + "(" + std::to_string(line_) + "): ";
        }
        return "0";
      }

// remove the symbol for the function, then define a new version that instead
// creates a stack temporary instance of Reporter initialized with the caller
#  undef dline
#  define dline Reporter(__FUNCTION__,__FILE__,__LINE__)
#endif