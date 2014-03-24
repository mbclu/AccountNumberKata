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

    // Check for either 2 or 3 arguments and get the file names to use
    switch(argc) {
    case 2:
    	inFileName = argv[1];
    	retCode = accountFileReader.readFile(inFileName.c_str());
        std::cout << accountFileReader.printAccounts(true);
    	break;
    case 3:
    	inFileName = argv[1];
    	outFileName = argv[2];
    	retCode = accountFileReader.readFile(inFileName.c_str());
        outStream.open(outFileName.c_str(), std::ios::trunc);
        if (outStream.is_open()) {
        	outStream << accountFileReader.printAccounts(true);
        	outStream.close();
        	std::cout << "File : \"" << inFileName << "\" parsed.\r\n" <<
        			"Output written to : \"" << outFileName << "\"\r\n";
        } else {
            std::cout << "Output File Not Found!" << std::endl;
        }
    	break;
    default:
        std::cout << "Incorrect Usage. Proper usage is as follows:" << std::endl;
        std::cout << "Parser.exe InputFile" << std::endl;
        std::cout << "Parser.exe InputFile OutputFile" << std::endl;
    	break;
    }

    // Check the return codes and provide some more helpful feedback
    switch (retCode) {
    case FILE_READ_RETURN_FILE_DOES_NOT_EXIST:
    	std::cout << 	"The input file \"" << inFileName <<
						"\" does not exist or could not be opened." << std::endl;
        break;
    case FILE_READ_RETURN_LINE_EMPTY:
    	std::cout << 	"The input file \"" << inFileName <<
						"\" contains an empty line at line : " <<
						accountFileReader.getTotalLineCountRead() << std::endl;
        break;
    case FILE_READ_RETURN_INVALID_LINE_LENGTH:
    	std::cout << 	"The input file \"" << inFileName <<
						"\" contains line of invalid length at line : " <<
						accountFileReader.getTotalLineCountRead() << std::endl;
        break;
    case FILE_READ_RETURN_INVALID_LINE_CHARS:
    	std::cout << 	"The input file \"" << inFileName <<
						"\" contains a line with invalid characters at line : " <<
						accountFileReader.getTotalLineCountRead() << std::endl;
        break;
    case FILE_READ_RETURN_INVALID_END_OF_ACCOUNT_CHARS:
        std::cout << 	"The input file \"" << inFileName <<
        				"\" contains an invalid account end-line at line : " <<
        				accountFileReader.getTotalLineCountRead() << std::endl;
        break;
    }

    return retCode;
}
