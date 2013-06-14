// Copyright PS Computer Services Ltd 2003-2010

#include <iostream>
#include <string>
#include <fstream>

#include "rtf.h"
#include "aux.h"
#include "ccontrolword.h"


#include "boost/program_options.hpp"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/filesystem/exception.hpp"
#include "boost/filesystem/convenience.hpp"

namespace fs = boost::filesystem;


int main(int argc, char *argv[]){
    bool verbose = false;
    bool quiet = true;
    bool toStdOut = false;
    bool allowTags = false;
    boost::filesystem::path sourceFile("");
    boost::filesystem::path destinationFile("");
    // Configure valid options and get user's options
    try {
        getOptions( argc, argv, verbose, quiet, toStdOut, sourceFile, destinationFile, allowTags);    	
    }
    catch(...){
        std::cerr << "Error while getting options." << std::endl;
        return 1 ;
    }
    // Open RTF input file
    if( verbose && !toStdOut){
      std::cout << "Opening RTF file: " << sourceFile << std::endl;
    } 
    fs::ifstream is( sourceFile );
    // Output plain text...
    if( toStdOut ){
      if( verbose ){
		if( allowTags ){
			std::cout << "Including angle brackets in output.  ";
		}
		else {
			std::cout << "Excluding angle brackets in output.  ";
		}		
        std::cout << "Outputting to console." << std::endl;
      }    
    
      convert( is, std::cout, 0, allowTags, verbose );
    }
    else {
      if( verbose ){
		if( allowTags ){
			std::cout << "Including angle brackets in output.  ";
		}
		else {
			std::cout << "Excluding angle brackets in output.  ";
		}		
        std::cout << "Outputting plaintext to file: " << destinationFile.string() << std::endl;
      }
      fs::ofstream os(destinationFile);
      convert( is, os, 0, allowTags, verbose );
    }

    return 0;                                                                                             
}                                  
