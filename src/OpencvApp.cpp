
#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <string>
#include <map>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"

using namespace cv;

#define MAX_CMD_WORDS   (5)

const char* HELP_MSG = "Available commands: \n\n\
load, ld  <name> <filename> - Load image file <filename> to the slot <name>\n\
store, s  <name> <filename> - Save image from the slot <name> to the file <filename>\n\
blur <from_name> <to_name> <size> - Blur image from the slot <from_name> with bluring size <size> and place it to the slot <to_name>\n\
resize <from_name> <to_name> <new_width> <new_height> - Resize image from the slot <from_name> to the <new_width> <new_height> size and place it to the slot <to_name>\n\
exit, quit, q - exit\n\
help, h - this text\n";

int main( int argc, char** argv )
{
    std::map <std::string, Mat> mapImages;

    do {
        std::string input_line;
        std::getline(std::cin, input_line);
        std::istringstream iss(input_line);
        std::string strArg[MAX_CMD_WORDS];
        int nArgs = 0;
        while ( getline( iss, strArg[nArgs], ' ')){
            if (nArgs >= MAX_CMD_WORDS){
                printf( "Invalid number of args\n");
                break;
            }
            if(0==nArgs)std::transform(strArg[nArgs].begin(), strArg[nArgs].end(), strArg[nArgs].begin(), ::toupper);// convert command to uppercase
            if (!strArg[nArgs].empty()) //skip extra spaces
                nArgs++;
        }

        if(strArg[0]=="H" || strArg[0]=="HELP"){
            printf( HELP_MSG );
            continue;
        }

        if(strArg[0]=="Q" || strArg[0]=="QUIT" || strArg[0]=="EXIT"){
            printf( "Quit\n");
            break;
        }

        if(strArg[0]=="LD" || strArg[0]=="LOAD"){
            printf( "Load %s ", strArg[2].c_str());

            if (nArgs < 3) {
                printf("Too few arguments - %d\n", nArgs);
                continue;
            }

            Mat image;
            image = imread(strArg[2], IMREAD_COLOR);
            if( image.empty()){
                printf( "\nCould not open file %s\n", strArg[2].c_str());
                continue;
            }
            std::map<std::string, Mat>::iterator it = mapImages.find(strArg[1]);
            if (it != mapImages.end())
                (*it).second = image;
            else
                mapImages.insert(std::pair<std::string, Mat>(strArg[1], image));
            printf("\n");
            continue;
        }

        if(strArg[0]=="S" || strArg[0]=="STORE"){
            printf( "Store ");

            if (nArgs < 3) {
                printf("Too few arguments - %d\n", nArgs);
                continue;
            }

            std::map<std::string, Mat>::iterator it = mapImages.find(strArg[1]);
            if (it == mapImages.end()) {
                printf( "Image slot %s is not found\n", strArg[1].c_str());
                continue;
            }
            if( (*it).second.empty()){
                printf( "Image in the slot %s is empty\n", strArg[1].c_str());
                continue;
            }

            try{
                imwrite(strArg[2], (*it).second);
            }
            catch( cv::Exception& e ){
                const char* err_msg = e.what();
                std::cout << "exception caught: " << err_msg << std::endl;
            }
            printf("\n");
            continue;
        }

        if(strArg[0]=="RESIZE"){

            printf( "Resize ");

            if (nArgs < 5) {
                printf("Too few arguments - %d\n", nArgs);
                continue;
            }

            int new_width = std::stoi(strArg[3]);
            if(new_width<=0 || new_width >= 65535)
            {
                printf( "Invalid new_width %d\n", new_width);
                continue;
            }
            int new_height = std::stoi(strArg[4]);
            if(new_height<=0 || new_height >= 65535)
            {
                printf( "Invalid new_height %d\n", new_height);
                continue;
            }

            std::map<std::string, Mat>::iterator it = mapImages.find(strArg[1]);
            if (it == mapImages.end()) {
                printf( "Image slot %s is not found\n", strArg[1].c_str());
                continue;
            }
            if( (*it).second.empty()){
                printf( "Image in the slot %s is empty\n", strArg[1].c_str());
                continue;
            }

            Mat image;
            resize((*it).second, image, Size(new_width, new_height));
            it = mapImages.find(strArg[2]);
            if (it != mapImages.end())
                (*it).second = image;
            else
                mapImages.insert(std::pair<std::string, Mat>(strArg[2], image));
            printf( "\n");
            continue;
        }

        if(strArg[0]=="BLUR"){
            printf( "Blur ");
            if (nArgs < 4) {
                printf("Too few arguments - %d\n", nArgs);
                continue;
            }

            int nSize = std::stoi(strArg[3]);
            if(nSize<=0 || nSize >= 65535)
            {
                printf( "Invalid size %d\n", nSize);
                continue;
            }

            std::map<std::string, Mat>::iterator it = mapImages.find(strArg[1]);
            if (it == mapImages.end()) {
                printf( "Image slot %s is not found\n", strArg[1].c_str());
                continue;
            }
            if( (*it).second.empty()){
                printf( "Image in the slot %s is empty\n", strArg[1].c_str());
                continue;
            }

            Mat image;
            blur( (*it).second, image, Size( nSize, nSize ), Point(-1,-1));
            it = mapImages.find(strArg[2]);
            if (it != mapImages.end())
                (*it).second = image;
            else
                mapImages.insert(std::pair<std::string, Mat>(strArg[2], image));

            printf( "\n");
            continue;
        }

        printf( "Invalid command\n");

    } while (true);

    return 0;
}