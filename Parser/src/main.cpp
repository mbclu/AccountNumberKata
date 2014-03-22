/*
 * main.cpp
 *
 *  Created on: Mar 15, 2014
 *      Author: Mitch
 */
#include "AccountFileReader.h"

using namespace accounts;

int main ( int argc, char *argv[] ) {
	AccountFileReader accountFileReader;
	FileReadReturnCode retCode = FILE_READ_RETURN_SUCCESS;
    std::string inFileName = "";
    std::string outFileName ="";
    std::ofstream outStream;

    switch(argc) {
    case 2:
    	inFileName = argv[1];
    	retCode = accountFileReader.readFile(inFileName.c_str());
        std::cout << accountFileReader.printAccountsWithStatus();
    	break;
    case 3:
    	inFileName = argv[1];
    	outFileName = argv[2];
    	retCode = accountFileReader.readFile(inFileName.c_str());
        outStream.open(outFileName.c_str(), std::ios::trunc);
        if (outStream.is_open()) {
        	outStream << accountFileReader.printAccountsWithStatus();
        	outStream.close();
        	std::cout << "File : \"" << inFileName << "\" parsed.\r\n" <<
        			"Output written to : \"" << outFileName << "\"\r\n";
        } else {
            std::cout << "Output File Not Found!" << std::endl;
        }
    	break;
    default:
        std::cout << "Usage: InputFile" << std::endl;
        std::cout << "or   : InputFile OutputFile" << std::endl;
    	break;
    }

    return retCode;
}
