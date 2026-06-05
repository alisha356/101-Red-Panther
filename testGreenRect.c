#include <stdio.h>
#include <string.h>
#include "camera_x11.h"


static void setGreenRect() {
	for (int row = 0; row < 50; row++) {
		for (int col = 0; col < 70; col++) {
			set_pixel(row, col, 0, 255, 0);
		}
	}
}


static void test_setGreenRect() {
    setGreenRect();
    uchar r, g, b;

    get_pixel(25, 35, &r, &g, &b);
    if (r == 0 && g == 255 && b == 0) {
		printf("PASS: test_setGreenRect inner pixel\n"); 
	} 
	else { 
		printf("FAIL: test_setGreenRect inner pixel — got (%d, %d, %d)\n", r, g, b); 
	}

    get_pixel(100, 100, &r, &g, &b);
    if (r == 0 && g == 255 && b == 0) { 
		printf("FAIL: test_setGreenRect outer pixel should not be green\n"); 
	} 
	else { 
		printf("PASS: test_setGreenRect outer pixel correctly unaffected\n"); 
	}
}


int main() {
	if (start_camera() != 0) {
        printf("Failed to start camera\n");
        return 1;
    }

	take_picture();
	test_setGreenRect();
	
	return 0;
}
