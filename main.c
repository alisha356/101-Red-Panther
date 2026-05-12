/*
 * The code below is meant to detect whether the Red Ruby
 * is present. The starategy implemented by the code is not very effective. 
 * Study the code so that you understand what the strategy is and how 
 * it is implemented. Then design and implement a better startegy.
 * */


// Arthur solid on the position of red pixels - forget averaging
// Howard solid on the value of green and blue reflected by the white paper



#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "camera_x11.h"



// To test, should work 
static void setGreenRect() {
	for (int row = 0; row < 50; row++) {
		for (int col = 0; col < 70; col++) {
			set_pixel(row, col, 0, 255, 0);
		}
	}
}


// To test, should work
static void setScreenRed() {
	for (int row = 0; row < 480; row++) {
		for (int col = 0; col < 640; col++) {
			set_pixel(row, col, 255, 0, 0);
		}
	}
}



int main() {
	if (start_camera() != 0) {
        printf("Failed to start camera\n");
        return 1;
    }

	bool rubyStolen = False;
	int runs = 0;

	while (rubyStolen == False) {
		take_picture();
		setGreenRect();   // To test, should work 
		display_picture();
		int redPx = 0; 

		runs += 1;

		// for all pixels in latest image
		for (int row = 0 ; row < 480; row++) {
			for (int col = 0; col < 640; col++) {
				if (row > 60 && row < 420 && col > 80 && col < 560) {
					uchar r, g ,b ;
					get_pixel(row, col, &r, &g ,&b);
					// printf("R: %d G: %d B: %d\n", r, g, b);
					if (r > (g+10) && r > (b+10)) {
						// printf("Red pixel at row: %d and col: %d\n", row, col);
						redPx += 1;
					}
				}
			}
		}

		if ((redPx < 20000 || redPx > 28000) && runs > 6) {
			rubyStolen = True;
			printf("Ruby stolen!\n");
		}
		printf("Red px: %d\n", redPx);
	}
	if (runs == 6) {
		setScreenRed();   // To test, should work (hopefully)
		display_picture();
		sleep(2);
	}

  return 0;
}
