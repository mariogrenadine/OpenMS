// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2022.
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Moritz Berger, Tetana Krymovska $
// $Authors: Moritz Berger, Tetana Krymovska$
// --------------------------------------------------------------------------

#include <OpenMS/CONCEPT/Colorizer.h>
#include <iostream>

#ifdef OPENMS_WINDOWSPLATTFORM
  #include <OpenMS/APPLICATIONS/ConsoleUtils.h>
  #include <windows.h>
#endif

namespace OpenMS
{

  // Constructor
  Colorizer::Colorizer(const Color color) : color_((int)color) 
  // color must be in initializer list, because of const keyword
  {
  }

  /// Default destructor
  Colorizer::~Colorizer()
  {
// if colorizer object is destroyed, set console color back to def col.
#if defined(__linux__) || defined(__OSX__)
    std::cout << colors_[int(Color::RESET)]; //check
    // std::cout << resetColor(cout);
    // std::cerr << resetColor(cerr);
#endif
  }

  ///
  void Colorizer::colorStream(std::ostream& stream) const
  {
#if defined(_WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)

    if (&std::cout == &stream)
    {
      // set color of output
      ConsoleUtils::getInstance().setCoutColor(colors_[color_]);
    }
    else if (&std::cerr == &stream)
    {
      ///set color of error stream
      ConsoleUtils::getInstance().setCerrColor(colors_[color_]);
    }

#elif defined(__linux__) || defined(__OSX__)
  //check if the output is being fed to file or console
  //supress output of ANSI codes into the file
    stream << " ...S HOHOHOHO E..." 
    << " coutNR: " << &std::cout 
    << " streamNR " << &stream
    << " cerrNR: " << &std::cerr; //delete


    if (&std::cout == &stream)
    {
    stream << this->colors_[this->color_]; //delete
      if(isatty(STDOUT_FILENO) || isatty(STDERR_FILENO))
      {
        //write coloring escape codes into the string
        stream << this->colors_[this->color_];
        // stream << "\033[33m"; //delete
      }
    }
    else if (&std::cerr == &stream)
    {
    stream << this->colors_[this->color_]; //delete
      if(isatty(STDOUT_FILENO) || isatty(STDERR_FILENO))
      {
        stream << this->colors_[this->color_];
        // stream << "\033[35m"; //delete

      }
    }
#endif
  }

  ///
  void Colorizer::resetColor(std::ostream& stream)
  {
#ifdef OPENMS_WINDOWSPLATTFORM
    if (&std::cout == &stream)
    {
      ///reset color of output
      ConsoleUtils::getInstance().resetCoutColor();
    }
    else if (&std::cerr == &stream)
    {
      ///reset color of error stream
      ConsoleUtils::getInstance().resetCerrColor();
    }
    
#elif defined(__linux__) || defined(__OSX__)
  //   check if the output is being fed to file or console
  //   supress output of ANSI codes into the file

     if (&std::cout == &stream)
    {
      if(isatty(STDOUT_FILENO) || isatty(STDERR_FILENO))
      {
        //write RESET ANSI code to string
        stream << this->colors_[int(Color::RESET)];
      }
    }
    else if (&std::cerr == &stream)
    {
      if(isatty(STDOUT_FILENO) || isatty(STDERR_FILENO))
      {
        stream << this->colors_[int(Color::RESET)];
      }
    }
#endif
  }

  ///
  std::string Colorizer::getDataAsString()
  {
    return input_.str();
  }

  // Helper function, to manipulate the output stream in class.
  void Colorizer::outputToStream(std::ostream& o_stream)
  {
    /// color the stream (or console)
    colorStream(o_stream);

    // paste text
    o_stream << this->input_.str();

    // if flag reset is set: reset comand line. else dont reset.
    if (this->reset_)
    {
      resetColor(o_stream);
    }
  }

  ///
  Colorizer& Colorizer::reset()
  {
    this->input_.str("");
    reset_ = true;
    return *this;
  }

  ///
  bool Colorizer::getReset()
  {
    return this->reset_;
  }

  // std::stringstream Colorizer::getInput(){
  //   return this->input_;
  // }

  // overload the shift operator (<<)
  std::ostream& operator<<(std::ostream& o_stream, 
                          OpenMS::Colorizer& col)
  {
    // colorize string with color set in the object
    col.outputToStream(o_stream);
    return o_stream;
  }


  // Objekte des typs colorizer
  OpenMS::Colorizer black(Color::BLACK);
  OpenMS::Colorizer red(Color::RED);
  OpenMS::Colorizer green(Color::GREEN);
  OpenMS::Colorizer yellow(Color::YELLOW);
  OpenMS::Colorizer blue(Color::BLUE);
  OpenMS::Colorizer magenta(Color::MAGENTA);
  OpenMS::Colorizer cyan(Color::CYAN);
  OpenMS::Colorizer white(Color::WHITE);

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

class ColorizerTester: public Colorizer

        /*only used in Colorizer_test.cpp for testing Colorizer method
      functionality. While using Colorizer instances, only cout or cerr
      streams are being colorized. 

      Methods with underscore "_" at the name end are used to
      reveal functionality of protected class functions in the unit test.
      
      For separate Colorizer method testing, stringstreams are used instead. 
      This class modified these methods to use Colorizer functionality on 
      stringstreams instead of cout/cerr streams. Such methods have "Simple"
      attached to the method name.
      
      This class should not be used outside Colorizer_test.cpp
      */
{
    public:

    ///Constructor
    ColorizerTester(const Color color);

    /// Default destructor
    ~ColorizerTester();

    //original methods revealing functionality for public use
    void outputToStream_(std::ostream& o_stream);

    void colorStream_(std::ostream& stream);

    void resetColor_(std::ostream& stream);

    std::string getDataAsString_();


    //modified methods for stringstream instead of cerr/cout
    void outputToStreamSimple(std::ostream& o_stream);

    void colorStreamSimple(std::ostream& stream);

    void resetColorSimple(std::ostream& stream);

   // bool getReset_();

    std::string getDataAsStringSimple();
};


} // namespace OpenMS
