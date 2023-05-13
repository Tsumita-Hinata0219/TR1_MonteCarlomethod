#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
const char kWindowTitle[] = "LE2B_20_ツミタ_ヒナタ_";



struct Vector2
{
	float x;
	float y;
};



struct Circle
{
	Vector2 position;
	int rad;
	float angle;
	unsigned int color;
};


struct Point
{
	Vector2 position;
	int rad;
	float angle;
	int inFlag;
	int appeaFlag;
	unsigned int color;
};

struct Emit
{
	Vector2 position;
	Vector2 size;
	float angle;

	unsigned int color;
};

void centerVector(Point point[], int arr, Circle circle);


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int ScreenWidth = 1280;
	const int ScreenHeight = 720;
	Novice::Initialize(kWindowTitle, ScreenWidth, ScreenHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};



	Circle circle = {
		{(ScreenWidth / 2), (ScreenHeight / 2)},
		{300},
		{0.0f},
		{RED},
	};



	Emit emit = {
		{340, 60},
		{600, 600},
		{0.0f},
		{BLUE},
	};



	const int maxPoint = 600;
	Point point[maxPoint]{};
	for (int i = 0; i < maxPoint; i++)  
	{
		point[i].position.x = 0;
		point[i].position.y = 0;

		point[i].rad = 3;

		point[i].angle = 0.0f;

		point[i].inFlag = 0;

		point[i].color = BLACK;
	}


	int inPointCount = 0;
	int outPointCount = 0;


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///


		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0)
		{
			for (int i = 0; i < maxPoint; i++)
			{
				point[i].position.x = circle.position.x + rand() % 600 - 300;
				point[i].position.y = circle.position.y + rand() % 600 - 300;
			}
		}


		// サークル内のポイントのフラグを立てる
		centerVector(point, maxPoint, circle);

		// カウント！！！
		inPointCount = 0;
		outPointCount = 0;
		for (int i = 0; i < maxPoint; i++)
		{
			if (point[i].inFlag == 1)
			{
				inPointCount = inPointCount + 1;
			}
			else {
				outPointCount = outPointCount + 1;
			}
		}

		float pi = float(inPointCount) / float(maxPoint) * 4.0f;



		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		for (int i = 0; i < maxPoint; i++)
		{
			Novice::DrawEllipse(
				int (point[i].position.x), int(point[i].position.y),
				point[i].rad, point[i].rad,
				point[i].angle, point[i].color, kFillModeSolid);
		}


		Novice::DrawEllipse(
			int (circle.position.x), int(circle.position.y),
			circle.rad, circle.rad,
			circle.angle, circle.color, kFillModeWireFrame);

		Novice::DrawBox(
			int (emit.position.x), int (emit.position.y),
			int (emit.size.x), int (emit.size.y),
			emit.angle, emit.color, kFillModeWireFrame);


		Novice::ScreenPrintf(10, 70, "maxPoint = %d", maxPoint);
		Novice::ScreenPrintf(10, 100, "inPointCount = %d", inPointCount);
		Novice::ScreenPrintf(10, 120, "outPointCount = %d", outPointCount);
		Novice::ScreenPrintf(10, 160, "pi = inPoint / maxPoint * 4");
		Novice::ScreenPrintf(10, 180, "pi = %f", pi);

		

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}



void centerVector(Point point[], int arr, Circle circle)
{
	for (int i = 0; i < arr; i++)
	{
		Vector2 cpVector = {
			circle.position.x - point[i].position.x,
			circle.position.y - point[i].position.y
		};

		// ポイントとサークル間の距離
		float cpLength = sqrtf((cpVector.x * cpVector.x) + (cpVector.y * cpVector.y));

		// サークルの半径内のポイントはフラグをtrueにする
		if (circle.rad >= cpLength)
		{
			point[i].inFlag = true;
		}
		else {
			point[i].inFlag = false;
		}
	}
}