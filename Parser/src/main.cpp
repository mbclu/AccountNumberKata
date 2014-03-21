/*
 * main.cpp
 *
 *  Created on: Mar 15, 2014
 *      Author: Mitch
 */
#include "AccountFileReader.h"

namespace accounts {

int main(int argc, char** argv) {
	AccountFileReader accountFileReader;
	FileReadReturnCode = FILE_READ_RETURN_SUCCESS;
    std::string inFileName = "";
    std::string outFileName ="";
    std::ofstream outStream;

    switch(argc) {
    case 2:
    	inFileName = argv[1];
    	FileReadReturnCode = accountFileReader.readFile(inFileName.c_str());
        std::cout << accountFileReader.printAccounts();
    	break;
    case 3:
    	inFileName = argv[1];
    	outFileName = argv[2];
    	FileReadReturnCode = accountFileReader.readFile(inFileName.c_str());
        outStream.open(outFileName.c_str(), std::ios::trunc);
        if (outStream.is_open()) {
        	std::cout << accountFileReader.printAccounts();
        } else {
            std::cout << "Output File Not Found!" << std::endl;
        }
    	break;
    default:
        std::cout << "Usage: InputFile" << std::endl;
        std::cout << "or   : InputFile OutputFile" << std::endl;
    	break;
    }

    return FileReadReturnCode;
}

} /* namespace accounts */
