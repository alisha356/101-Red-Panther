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
#include <time.h>
#include "camera_x11.h"


// {row, col} = {y, x}
int timeCoordsFirst[6][2] = {
	{215, 185}, {215, 210},
	{240, 185}, {240, 210},
	{265, 185}, {265, 210}
};


// Shift for which int is being drawn in the time (0 through 3)
int shift = 0;


static void setGreenRect() {
	for (int row = 0; row < 50; row++) {
		for (int col = 0; col < 70; col++) {
			set_pixel(row, col, 0, 255, 0);
		}
	}
}


static void setScreenRed() {
	for (int row = 0; row < 480; row++) {
		for (int col = 0; col < 640; col++) {
			set_pixel(row, col, 255, 0, 0);
		}
	}
}


static void drawLine(const char *direction, int row, int col) {
	int length = 25;
	if (strcmp(direction, "horizontal") == 0) {
		for (int num = 0; num < length; num++) {
			set_pixel(row, col + num, 255, 0, 0);
			set_pixel(row + 1, col + num, 255, 0, 0);
		}
	}
	else if (strcmp(direction, "vertical") == 0) {
		for (int num = 0; num < length; num++) {
			set_pixel(row + num, col, 255, 0, 0);
			set_pixel(row + num, col + 1, 255, 0, 0);
        }
	}
}


static void drawZero() {
	drawLine("horizontal", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[1][0], timeCoordsFirst[1][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[3][0], timeCoordsFirst[3][1] + 35*shift);
}


static void drawOne() {
	drawLine("vertical", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
}


static void drawTwo() {
	drawLine("horizontal", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[1][0], timeCoordsFirst[1][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 35*shift);
}


static void drawThree() {
	drawLine("horizontal", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[1][0], timeCoordsFirst[1][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[3][0], timeCoordsFirst[3][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 35*shift);
}


static void drawFour() {
	drawLine("vertical", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[1][0], timeCoordsFirst[1][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[3][0], timeCoordsFirst[3][1] + 35*shift);
}


static void drawFive() {
	drawLine("horizontal", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[3][0], timeCoordsFirst[3][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 35*shift);
}


static void drawSix() {
	drawLine("horizontal", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[3][0], timeCoordsFirst[3][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 35*shift);
}


static void drawSeven() {
	drawLine("horizontal", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[1][0], timeCoordsFirst[1][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[3][0], timeCoordsFirst[3][1] + 35*shift);
}


static void drawEight() {
	drawLine("horizontal", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[1][0], timeCoordsFirst[1][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[3][0], timeCoordsFirst[3][1] + 35*shift);
}


static void drawNine() {
	drawLine("horizontal", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[1][0], timeCoordsFirst[1][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[3][0], timeCoordsFirst[3][1] + 35*shift);
}


static void checkChar(char character) {
	if (character == '0'){ drawZero(); }
	else if (character == '1'){ drawOne(); }
	else if (character == '2') { drawTwo(); }
	else if (character == '3') { drawThree(); }
	else if (character == '4') { drawFour(); }
	else if (character == '5') { drawFive(); }
	else if (character == '6') { drawSix(); }
	else if (character == '7') { drawSeven(); }
	else if (character == '8') { drawEight(); }
	else if (character == '9') { drawNine(); }
}


int main() {
	if (start_camera() != 0) {
        printf("Failed to start camera\n");
        return 1;
    }

	time_t raw_time;
	struct tm *info;

	FILE *fptr;
	
	bool rubyStolen = False;
	int runs = 0;
	
	while (rubyStolen == False) {
		time(&raw_time);
		info = localtime(&raw_time);
		char *currentTime = asctime(info);

		take_picture();
		setGreenRect();
		display_picture();
		int redPx = 0; 

		runs += 1;

		for (int row = 0 ; row < 480; row++) {
			for (int col = 0; col < 640; col++) {
				if (row > 60 && row < 420 && col > 80 && col < 560) {
					uchar r, g ,b ;
					get_pixel(row, col, &r, &g ,&b);
					if (r > (g+20) && r > (b+20)) {
						redPx += 1;
					}
				}
			}
		}

		if ((redPx < 18500 || redPx > 23000) && runs > 10) {
			if (runs > 10 && runs < 15) {
				setScreenRed();
				display_picture();
				sleep(5);
				rubyStolen = True;
			}
			else {
				take_picture();
				printf("Ruby stolen!\n");

				checkChar(currentTime[11]);
				shift++;
				checkChar(currentTime[12]);
				shift++;
				drawLine("horizontal", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
				shift++;
				checkChar(currentTime[14]);
				shift++;
				checkChar(currentTime[15]);
				shift = 0;

				fptr = fopen("rubyLogFile.txt", "w");
				if (fptr == NULL) {
					printf("Error: Could not create file.\n");
					return 1;
				}

				fprintf(fptr, "Stolen at %s", currentTime);
				fclose(fptr);

				display_picture();
				rubyStolen = True;
				sleep(10);
			}
		}
	}

  return 0;
}
