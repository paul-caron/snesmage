/**
 SNESMAGE.CPP
 converts any image into a fullscreen (256x224 max) SNES group of 8x8 sprites
*/

#include <Magick++.h> 
#include <iostream> 
#include <vector>
#include <cmath>
#include <fstream>
using namespace std; 
using namespace Magick; 
int main(int argc,char **argv) 
{ 
  InitializeMagick(*argv);

  if(argc < 2){
    std::cout << "You must pass the input image filename as an argument\nsnesmage <image filename>\n" ;
    exit(EXIT_FAILURE);
  }

  Image image;

  try { 
    
    // Read a file into image object 
    image.read(argv[1]);

    // Resize the image to SNES fullscreen size
    image.resize("16x16");

    // Convert to grayscale
    image.type( GrayscaleType );

    // Write the resized image to a file (for debug purposes) 
    image.write( "resized.jpg" ); 

    // Get width and height of image
    unsigned width = image.columns();
    unsigned height = image.rows();

    // Output file stream
    std::ofstream fs("image.bin", std::ios::out | std::ios::binary);


    // 
    for(unsigned y = 0; y<height; y += 8){

      for(unsigned x = 0; x<width; x += 8){

        for(unsigned row = y; row < y + 8; row ++){

          std::vector<unsigned> row_values;

          for(unsigned column = x; column < x + 8; column ++){
            Color color = image.pixelColor(column, row);
            ColorRGB colorrgb(color);
            unsigned intensity = unsigned(colorrgb.green() * 16) - 0.001;
            row_values.push_back(intensity);
          }

          //from row values get bitplanes 0,1
          unsigned char bp0_row = 0;
          unsigned char bp1_row = 0;

          for(unsigned i = 0; i < row_values.size() ; i++){
            unsigned value = row_values[i];
            bp0_row += ((value & 0b0010)>>1)*pow(2, 7-i);
            bp1_row += ((value & 0b0001)>>0)*pow(2, 7-i);
          }
 
          
          fs.write(reinterpret_cast<const char *>(&bp1_row),1);
          fs.write(reinterpret_cast<const char *>(&bp0_row),1); 

        }


        for(unsigned row = y; row < y + 8; row ++){

          std::vector<unsigned> row_values;

          for(unsigned column = x; column < x + 8; column ++){
            Color color = image.pixelColor(column, row);
            ColorRGB colorrgb(color);
            unsigned intensity = unsigned(colorrgb.green() * 16) - 0.001;
            row_values.push_back(intensity);
          }

          //from row values get bitplanes 2,3
          unsigned char bp2_row = 0;
          unsigned char bp3_row = 0;

          for(unsigned i = 0; i < row_values.size() ; i++){
            unsigned value = row_values[i];
            bp2_row += ((value & 0b1000)>>3)*pow(2, 7-i);
            bp3_row += ((value & 0b0100)>>2)*pow(2, 7-i);
          }

          fs.write(reinterpret_cast<const char *>(&bp3_row),1);
          fs.write(reinterpret_cast<const char *>(&bp2_row),1);


        }

      }
    }

  } 
  catch( Exception &error_ ) 
    { 
      cout << "Caught exception: " << error_.what() << endl; 
      return 1; 
    } 
  return 0; 
}
