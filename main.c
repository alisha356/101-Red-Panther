/*
 * The code below is meant to detect whether the Red Ruby
 * is present. The starategy implemented by the code is not very effective. 
 * Study the code so that you understand what the strategy is and how 
 * it is implemented. Then design and implement a better startegy.
 * */


// Arthur solid on the position of red pixels - forget averaging
// Howard solid on the value of green and blue reflected by the white paper



#include <stdio.h>
// #include <unistd.h>		// For sleep
#include "camera_x11.h"

int main() {
	
	 if (start_camera() != 0) {
        printf("Failed to start camera\n");
        return 1;
    }

  
  // make 1000 runs  
  for (int countrun = 0; countrun < 1000; countrun++) {
	take_picture();
	display_picture();
	int redPx = 0; 

    // for all pixels in latest image
    for (int row = 0 ; row < 480 ; row++) {	
		for (int col = 0; col < 640; col++) {
			uchar r, g ,b ;
			get_pixel(row, col, &r, &g ,&b);
			// printf("R: %d G: %d B: %d\n", r, g, b);
			if (r > (g+10) && r > (b+10)) {
				// printf("Red pixel at row: %d and col: %d\n", row, col);
				redPx += 1;
			}
		}
	}

	printf("Countrun: %d\n",countrun);
	printf("Red px: %d\n", redPx);
  }


  return 0;
}
