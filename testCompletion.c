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


// Shift for which int is being drawn in the time (0 through 4)
int shift = 0;


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

static void test_drawLine() {
    drawLine("horizontal", 100, 100);
    uchar r, g, b;
    get_pixel(100, 110, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawLine: horizontal pixel\n"); }
    else { printf("FAIL: drawLine: horizontal pixel — got (%d, %d, %d)\n", r, g, b); }

    drawLine("vertical", 100, 100);
    get_pixel(110, 100, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawLine: vertical pixel\n"); }
    else { printf("FAIL: drawLine: vertical pixel — got (%d, %d, %d)\n", r, g, b); }
}


static void drawZero() {
	drawLine("horizontal", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[1][0], timeCoordsFirst[1][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[3][0], timeCoordsFirst[3][1] + 35*shift);
}

static void test_drawZero() {
    drawZero();
    uchar r, g, b;

    get_pixel(timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawZero segment A drawn\n"); }
    else { printf("FAIL: drawZero segment A — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[0][0] + 5, timeCoordsFirst[0][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawZero segment F drawn\n"); }
    else { printf("FAIL: drawZero segment F — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[2][0] + 5, timeCoordsFirst[2][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawZero segment E drawn\n"); }
    else { printf("FAIL: drawZero segment E — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawZero segment D drawn\n"); }
    else { printf("FAIL: drawZero segment D — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[1][0] + 5, timeCoordsFirst[1][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawZero segment B drawn\n"); }
    else { printf("FAIL: drawZero segment B — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[3][0] + 5, timeCoordsFirst[3][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawZero segment C drawn\n"); }
    else { printf("FAIL: drawZero segment C — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("FAIL: drawZero segment G should not be drawn\n"); }
    else { printf("PASS: drawZero segment G correctly unset\n"); }
}


static void drawOne() {
    drawLine("vertical", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
}

static void test_drawOne() {
    drawOne();
    uchar r, g, b;

    get_pixel(timeCoordsFirst[0][0] + 5, timeCoordsFirst[0][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawOne segment F drawn\n"); }
    else { printf("FAIL: drawOne: segment F — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[2][0] + 5, timeCoordsFirst[2][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawOne segment E drawn\n"); }
    else { printf("FAIL: drawOne segment E — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("FAIL: drawOne segment G should not be drawn\n"); }
    else { printf("PASS: drawOne segment G correctly unset\n"); }
}


static void drawTwo() {
    drawLine("horizontal", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[1][0], timeCoordsFirst[1][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 35*shift);
}

static void test_drawTwo() {
    drawTwo();
    uchar r, g, b;

    get_pixel(timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawTwo segment A drawn\n"); }
    else { printf("FAIL: drawTwo segment A — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[1][0] + 5, timeCoordsFirst[1][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawTwo segment B drawn\n"); }
    else { printf("FAIL: drawTwo segment B — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[2][0] + 5, timeCoordsFirst[2][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawTwo segment G drawn\n"); }
    else { printf("FAIL: drawTwo segment G — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[2][0] + 5, timeCoordsFirst[2][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawTwo segment E drawn\n"); }
    else { printf("FAIL: drawTwo segment E — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawTwo segment D drawn\n"); }
    else { printf("FAIL: drawTwo segment D — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[0][0] + 5, timeCoordsFirst[0][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("FAIL: drawTwo segment F should not be drawn\n"); }
    else { printf("PASS: drawTwo segment F correctly unset\n "); }
}


static void drawThree() {
    drawLine("horizontal", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[1][0], timeCoordsFirst[1][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[3][0], timeCoordsFirst[3][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 35*shift);
}

static void test_drawThree() {
    drawThree();
    uchar r, g, b;

    get_pixel(timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawThree segment A drawn\n"); }
    else { printf("FAIL: drawThree segment A — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[1][0] + 5, timeCoordsFirst[1][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawThree segment B drawn\n"); }
    else { printf("FAIL: drawThree segment B — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[2][0] + 5, timeCoordsFirst[2][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawThree segment G drawn\n"); }
    else { printf("FAIL: drawThree segment G — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[3][0] + 5, timeCoordsFirst[3][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawThree segment C drawn\n"); }
    else { printf("FAIL: drawThree segment C — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawThree segment D drawn\n"); }
    else { printf("FAIL: drawThree segment D — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[0][0] + 5, timeCoordsFirst[0][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("FAIL: drawThree segment F should not be drawn\n"); }
    else { printf("PASS: drawThree segment F correctly unset\n "); }
}


static void drawFour() {
    drawLine("vertical", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[1][0], timeCoordsFirst[1][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[3][0], timeCoordsFirst[3][1] + 35*shift);
}

static void test_drawFour() {
    drawFour();
    uchar r, g, b;

    get_pixel(timeCoordsFirst[0][0] + 5, timeCoordsFirst[0][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawFour segment F drawn\n"); }
    else { printf("FAIL: drawFour segment F — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[1][0] + 5, timeCoordsFirst[1][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawFour segment B drawn\n"); }
    else { printf("FAIL: drawFour segment B — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[2][0] + 5, timeCoordsFirst[2][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawFour segment G drawn\n"); }
    else { printf("FAIL: drawFour segment G — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[3][0] + 5, timeCoordsFirst[3][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawFour segment C drawn\n"); }
    else { printf("FAIL: drawFour segment C — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("FAIL: drawFour segment A should not be drawn\n"); }
    else { printf("PASS: drawFour segment A correctly unset\n "); }
}


static void drawFive() {
    drawLine("horizontal", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[3][0], timeCoordsFirst[3][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 35*shift);
}

static void test_drawFive() {
    drawFive();
    uchar r, g, b;

    get_pixel(timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawFive segment A drawn\n"); }
    else { printf("FAIL: drawFive segment A — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[0][0] + 5, timeCoordsFirst[0][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawFive segment F drawn\n"); }
    else { printf("FAIL: drawFive segment F — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[2][0] + 5, timeCoordsFirst[2][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawFive segment G drawn\n"); }
    else { printf("FAIL: drawFive segment G — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[3][0] + 5, timeCoordsFirst[3][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawFive segment C drawn\n"); }
    else { printf("FAIL: drawFive segment C — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawFive segment D drawn\n"); }
    else { printf("FAIL: drawFive segment D — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[1][0] + 5, timeCoordsFirst[1][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("FAIL: drawFive segment B should not be drawn\n"); }
    else { printf("PASS: drawFive segment B correctly unset\n "); }
}


static void drawSix() {
    drawLine("horizontal", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[3][0], timeCoordsFirst[3][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 35*shift);
}

static void test_drawSix() {
    drawSix();
    uchar r, g, b;

    get_pixel(timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawSix segment A drawn\n"); }
    else { printf("FAIL: drawSix segment A — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[0][0] + 5, timeCoordsFirst[0][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawSix segment F drawn\n"); }
    else { printf("FAIL: drawSix segment F — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[2][0] + 5, timeCoordsFirst[2][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawSix segment G drawn\n"); }
    else { printf("FAIL: drawSix segment G — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[2][0] + 5, timeCoordsFirst[2][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawSix segment E drawn\n"); }
    else { printf("FAIL: drawSix segment E — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[3][0] + 5, timeCoordsFirst[3][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawSix segment C drawn\n"); }
    else { printf("FAIL: drawSix segment C — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawSix segment D drawn\n"); }
    else { printf("FAIL: drawSix segment D — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[1][0] + 5, timeCoordsFirst[1][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("FAIL: drawSix segment B should not be drawn\n"); }
    else { printf("PASS: drawSix segment B correctly unset\n "); }
}


static void drawSeven() {
    drawLine("horizontal", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[1][0], timeCoordsFirst[1][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[3][0], timeCoordsFirst[3][1] + 35*shift);
}

static void test_drawSeven() {
    drawSeven();
    uchar r, g, b;

    get_pixel(timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawSeven segment A drawn\n"); }
    else { printf("FAIL: drawSeven segment A — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[1][0] + 5, timeCoordsFirst[1][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawSeven segment B drawn\n"); }
    else { printf("FAIL: drawSeven segment B — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[3][0] + 5, timeCoordsFirst[3][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawSeven segment C drawn\n"); }
    else { printf("FAIL: drawSeven segment C — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[0][0] + 5, timeCoordsFirst[0][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("FAIL: drawSeven segment F should not be drawn\n"); }
    else { printf("PASS: drawSeven segment F correctly unset\n "); }
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

static void test_drawEight() {
    drawEight();
    uchar r, g, b;

    get_pixel(timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawEight segment A drawn\n"); }
    else { printf("FAIL: drawEight segment A — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[0][0] + 5, timeCoordsFirst[0][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawEight segment F drawn\n"); }
    else { printf("FAIL: drawEight segment F — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[2][0] + 5, timeCoordsFirst[2][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawEight segment G drawn\n"); }
    else { printf("FAIL: drawEight segment G — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[2][0] + 5, timeCoordsFirst[2][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawEight segment E drawn\n"); }
    else { printf("FAIL: drawEight segment E — got (%d, %d, %d)\n", r, g, b); }
    
    get_pixel(timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawEight segment D drawn\n"); }
    else { printf("FAIL: drawEight segment D — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[1][0] + 5, timeCoordsFirst[1][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawEight segment B drawn\n"); }
    else { printf("FAIL: drawEight segment B — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[3][0] + 5, timeCoordsFirst[3][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawEight segment C drawn\n"); }
    else { printf("FAIL: drawEight segment C — got (%d, %d, %d)\n", r, g, b); }
}


static void drawNine() {
    drawLine("horizontal", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[2][0], timeCoordsFirst[2][1] + 35*shift);
	drawLine("horizontal", timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[1][0], timeCoordsFirst[1][1] + 35*shift);
	drawLine("vertical", timeCoordsFirst[3][0], timeCoordsFirst[3][1] + 35*shift);
}

static void test_drawNine() {
    drawNine();
    uchar r, g, b;

    get_pixel(timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawNine segment A drawn\n"); }
    else { printf("FAIL: drawNine segment A — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[0][0] + 5, timeCoordsFirst[0][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawNine segment F drawn\n"); }
    else { printf("FAIL: drawNine segment F — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[2][0] + 5, timeCoordsFirst[2][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawNine segment G drawn\n"); }
    else { printf("FAIL: drawNine segment G — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[4][0], timeCoordsFirst[4][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawNine segment D drawn\n"); }
    else { printf("FAIL: drawNine segment D — got (%d, %d, %d)\n", r, g, b); }
    
    get_pixel(timeCoordsFirst[1][0] + 5, timeCoordsFirst[1][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawNine segment B drawn\n"); }
    else { printf("FAIL: drawNine segment B — got (%d, %d, %d)\n", r, g, b); }
    
    get_pixel(timeCoordsFirst[3][0] + 5, timeCoordsFirst[3][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: drawNine segment C drawn\n"); }
    else { printf("FAIL: drawNine segment C — got (%d, %d, %d)\n", r, g, b); }

    get_pixel(timeCoordsFirst[2][0] + 5, timeCoordsFirst[2][1], &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("FAIL: drawNine segment E should not be drawn\n"); }
    else { printf("PASS: drawNine segment E correctly unset\n "); }
}


static void checkChar(char character) {
    printf("checkChar: character is %c\n", character);
	if (character == '0'){ drawZero(); printf("checkChar: drawZero called\n"); }
	else if (character == '1'){ drawOne(); printf("checkChar: drawOne called\n"); }
	else if (character == '2') { drawTwo(); printf("checkChar: drawTwo called\n"); }
	else if (character == '3') { drawThree(); printf("checkChar: drawThree called\n"); }
	else if (character == '4') { drawFour(); printf("checkChar: drawFour called\n"); }
	else if (character == '5') { drawFive(); printf("checkChar: drawFive called\n"); }
	else if (character == '6') { drawSix(); printf("checkChar: drawSix called\n"); }
	else if (character == '7') { drawSeven(); printf("checkChar: drawSeven called\n"); }
	else if (character == '8') { drawEight(); printf("checkChar: drawEight called\n"); }
	else if (character == '9') { drawNine(); printf("checkChar: drawNine called\n"); }
}

static void test_checkChar() {
    checkChar('0');
    uchar r, g, b;

    get_pixel(timeCoordsFirst[0][0], timeCoordsFirst[0][1] + 5, &r, &g, &b);
    if (r == 255 && g == 0 && b == 0) { printf("PASS: checkChar('0') dispatched correctly\n"); }
    else { printf("FAIL: checkChar('0') — got (%d, %d, %d)\n", r, g, b); }
}



int main() {
    if (start_camera() != 0) {
        printf("Failed to start camera\n");
        return 1;
    }

	take_picture();
    test_drawLine();

    take_picture();
    test_drawZero();
    
    take_picture();
    test_drawOne();

    take_picture();
    test_drawTwo();

    take_picture();
    test_drawThree();

    take_picture();
    test_drawFour();

    take_picture();
    test_drawFive();

    take_picture();
    test_drawSix();
    
    take_picture();
    test_drawSeven();

    take_picture();
    test_drawEight();

    take_picture();
    test_drawNine();

    take_picture();
    test_checkChar();
  return 0;
}
