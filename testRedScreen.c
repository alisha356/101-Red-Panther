#include <stdio.h>
#include <string.h>
#include "camera_x11.h"


static void setScreenRed() {
	for (int row = 0; row < 480; row++) {
		for (int col = 0; col < 640; col++) {
			set_pixel(row, col, 255, 0, 0);
		}
	}
}


static void test_setScreenRed() {
	setScreenRed();
	uchar r, g, b;

	get_pixel(240, 320, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { 
		printf("PASS: test_setScreenRed centre pixel\n"); 
	}
	else { 
		printf("FAIL: test_setScreenRed centre pixel — got (%d, %d, %d)\n", r, g, b); 
	}
}


int main() {
	if (start_camera() != 0) {
        printf("Failed to start camera\n");
        return 1;
    }

	take_picture();
	test_setScreenRed();
	
	return 0;
}
