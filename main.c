#include "raylib.h"
#include "raymath.h"
#include <math.h>
#define WIDTH 640
#define HEIGHT 640

static Vector2 P1, P2, P3;
static int D1, D2, D3;
static float T;
static float L;

static bool color;
static Image img;
static Texture txt;

int main(void)
{
	InitWindow(WIDTH, HEIGHT, "interfere");

	SetTargetFPS(60);

	T = 0.1;
	L = 16;

	img = GenImageColor(WIDTH, HEIGHT, WHITE);
	txt = LoadTextureFromImage(img);

	while (!WindowShouldClose()) {
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			P1 = GetMousePosition();
			if (IsKeyPressed(KEY_SPACE))
				D1 = (D1 + 1) % 4;
		}
		if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
			P2 = GetMousePosition();
			if (IsKeyPressed(KEY_SPACE))
				D2 = (D2 + 1) % 4;
		}
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
			P3 = GetMousePosition();
			if (IsKeyPressed(KEY_SPACE))
				D3 = (D3 + 1) % 4;
		}
		if (IsKeyPressed(KEY_ENTER))
			color = !color;

		for (int x = 0; x < WIDTH; x++)
			for (int y = 0; y < HEIGHT; y++) {
				static Vector2 Q;
				static int A, B, C;
				static int off;
				static float t;

				Q = (Vector2) {
				x, y};
				t = GetTime();

				off = 0;
				if (D1 == 0)
					A = (sinf
					     (Vector2Distance(Q, P1) / L -
					      t / T)
					     + 1) / 2 * 255;
				else if (D1 == 1)
					A = (sinf(fabsf(Q.x - P1.x) / L - t / T)
					     + 1) / 2 * 255;
				else if (D1 == 2)
					A = (sinf(fabsf(Q.y - P1.y) / L - t / T)
					     + 1) / 2 * 255;
				else {
					A = 0;
					off++;
				}
				if (D2 == 0)
					B = (sinf
					     (Vector2Distance(Q, P2) / L -
					      t / T)
					     + 1) / 2 * 255;
				else if (D2 == 1)
					B = (sinf(fabsf(Q.x - P2.x) / L - t / T)
					     + 1) / 2 * 255;
				else if (D2 == 2)
					B = (sinf(fabsf(Q.y - P2.y) / L - t / T)
					     + 1) / 2 * 255;
				else {
					B = 0;
					off++;
				}
				if (D3 == 0)
					C = (sinf
					     (Vector2Distance(Q, P3) / L -
					      t / T)
					     + 1) / 2 * 255;
				else if (D3 == 1)
					C = (sinf(fabsf(Q.x - P3.x) / L - t / T)
					     + 1) / 2 * 255;
				else if (D3 == 2)
					C = (sinf(fabsf(Q.y - P3.y) / L - t / T)
					     + 1) / 2 * 255;
				else {
					C = 0;
					off++;
				}
				if (color)
					ImageDrawPixelV(&img, Q, (Color) {
							A, B, C, 255}
				);
				else
				ImageDrawPixelV(&img, Q, (Color) {
						(A + B + C) / (3 - off),
						(A + B + C) / (3 - off),
						(A + B + C) / (3 - off), 255}
				);
			}
		UpdateTexture(txt, img.data);

		BeginDrawing();

		DrawTexture(txt, 0, 0, WHITE);
		DrawCircleV(P1, L / 4, (Color) {
			    128 + GetImageColor(img, P1.x, P1.y).r / 2, 0, 0,
			    255}
		);
		DrawCircleV(P2, L / 4, (Color) {
			    0, 128 + GetImageColor(img, P2.x, P2.y).g / 2, 0,
			    255}
		);
		DrawCircleV(P3, L / 4, (Color) {
			    0, 0, 128 + GetImageColor(img, P3.x, P3.y).b / 2,
			    255}
		);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
