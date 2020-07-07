/******************************************************
*** Designer      : 杉田
*** Date          : 2020.6.24
*** Purpose       : W5 パズル作成画面
*******************************************************/


#include "DxLib.h"
#include "MouseState.h"
#include "Controller.h"
#include "MakePuzzle.h"
#include "Information.h"
#include "SceneMgr.h"
#include "Information.h"
#include <string.h>


/******************************************************
/******************************************************
*** Function Name	: InitializeMakePuzzle
*** Designer		: 杉田
*** Date			: 2020.6.28
*** Function		: パズル作成画面を表示する
*** Return			: MakePuzzleScr
******************************************************/
int InitializeMakePuzzle(MakePuzzle_t* create) {
	Mouse_t mouse;
	Puzzle_t puzzle;
	GetMouseState(&mouse);
	
	int backImageHandle = LoadGraph("graph/backButton.bmp");
	int resetImageHandle = LoadGraph("graph/resetButton.bmp");
	int penImageHandle = LoadGraph("graph/penButton.bmp");
	int eraserImageHandle = LoadGraph("graph/eraserButton.bmp");

	setButton(5, 630, 95, 720, backImageHandle, NULL, mouse, &(create->backButton));
	setButton(150, 630, 240, 720, resetImageHandle, NULL, mouse, &(create->resetButton));
	setButton(20, 20, 110, 110, eraserImageHandle, NULL, mouse, &(create->eraserButton));

	DrawGraph(create->backButton.mX1, create->backButton.mY1, create->backButton.mImageHandle, FALSE);
	DrawGraph(create->resetButton.mX1, create->resetButton.mY1, create->resetButton.mImageHandle, FALSE);
	DrawGraph(create->eraserButton.mX1, create->eraserButton.mY1, create->eraserButton.mImageHandle, FALSE);

	DrawBox(290, 30, 380, 80, create->black, FALSE);
	DrawBox(440, 30, 530, 80, create->black, FALSE);
	DrawBox(590, 30, 680, 80, create->black, FALSE);
	//DrawBox(740, 30, 830, 80, create->black, FALSE);
	//DrawBox(890, 30, 980, 80, create->black, FALSE);

	
	DrawBox(830, 130, 1000, 180, create->black, FALSE);
	DrawBox(830, 280, 1000, 330, create->black, FALSE);
	//DrawBox(830, 430, 1000, 480, GetColor(0, 0, 0), FALSE);


	DrawFormatString(300, 50, create->black, "10 × 10");
	DrawFormatString(450, 50, create->black, "15 × 15");
	DrawFormatString(600, 50, create->black, "20 × 20");
	//DrawFormatString(750, 50, create->black, "15 × 20");
	//DrawFormatString(900, 50, create->black, "20 × 20");
	DrawFormatString(850, 150, create->black, "画像を取り込む");
	DrawFormatString(850, 300, create->black, "パズルを投稿する");
	// DrawFormatString(850, 450, GetColor(0, 0, 0), "パズルに変換");


	// パズルの初期画面表示と縮小パズルの初期画面表示　色は白
	for (int j = 0; j < create->size; j++) {
		for (int i = 0; i < create->size; i++) {
			int S = create->posi + i * create->sellsize + 200; // パズルマスの横
			int T = create->posi + j * create->sellsize; // パズルマスの縦
			int s = create->posi + i * create->semisize - 50; // 縮小パズルマスの横
			int t = create->posi + j * create->semisize + 100; // 縮小パズルマスの縦
			puzzle.x_size = create->size;
			puzzle.y_size = create->size;
			DrawBox(s, t, s + create->semisize - 1, t + create->semisize - 1, create->white, TRUE);
			DrawBox(S, T, S + create->sellsize - 1, T + create->sellsize - 1, create->white, TRUE);
		}
	}

	// 縮小パズルの初期画面表示、色は白
	/*for (int j = 0; j < Size; j++) {
		for (int i = 0; i < Size; i++) {
			int s = Posi + i * semisize-50; // パズルマスの横
			int t = Posi + j * semisize + 50; // パズルマスの縦
			DrawBox(s, t, s + semisize - 1, t + semisize - 1, white, TRUE);
		}
	}*/

	// 色を選択するマスを表示
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 8; i++) {
			int S = create->posi + i * create->selectsize + 270; // パズルマスの横
			int T = create->posi + j * create->selectsize; // パズルマスの縦
			DrawBox(S, T + 520, S + create->selectsize - 1, T + create->selectsize - 1 + 520, create->col[i][j], TRUE); // 460とかはパズル画面表示の調整
		}
	}

	return MakePuzzleScr;
}

/***************************************
*** Function Name	: UpdateMakePuzzle
*** Designer		: 杉田
*** Date			: 2020.6.28
*** Function		: パズル作成画面の更新
*** Return			: 遷移先の画面を指定
*******************************************/

int UpdateMakePuzzle(MakePuzzle_t* create) {
	InitializeMakePuzzle(create);
	Mouse_t mouse;
	Puzzle_t puzzle;
	GetMouseState(&mouse);

	// サイズ選択ボタンが押されたらパズルのサイズを変更する
	if ((&mouse)->mButton == left && click(&(mouse), 290, 30, 380, 80)) {
		create->size = 10;
		create->sellsize = 50;
		create->semisize = 20;
		puzzle.x_size = create->size;
		puzzle.y_size = create->size;

	}
	if ((&mouse)->mButton == left && click(&(mouse), 440, 30, 530, 80)) {
		create->size = 15; 
		create->sellsize = 33;
		create->semisize = 13;
		puzzle.x_size = create->size;
		puzzle.y_size = create->size;

	}
	if ((&mouse)->mButton == left && click(&(mouse), 590, 30, 680, 80)) {
		create->size = 20;
		create->sellsize = 25;
		create->semisize = 10;
		puzzle.x_size = create->size;
		puzzle.y_size = create->size;

	}

	// 消しゴムボタンが押されたら白色の情報を保持
	if ((&mouse)->mButton == left && click(&(mouse), 20, 20, 110, 110)) {
		create->tmp = create->white;
	}

	// 選択する色をクリックしたら、その色を保持する
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 8; i++) {
			int S = create->posi + i * create->selectsize + 270; // パズルマスの横
			int T = create->posi + j * create->selectsize; // パズルマスの縦
			// 左クリックされたら色の情報を保持
			if ((&mouse)->mButton == left && click(&(mouse), S, T + 520, S + create->selectsize - 1, T + create->selectsize - 1 + 520)) {
				create->tmp = create->col[i][j];
			}
		}
	}

	// パズルの画面表示
	for (int j = 0; j < create->size; j++) {
		for (int i = 0; i < create->size; i++) {
			int S = create->posi + i * create->sellsize + 200; // パズルマスの横
			int T = create->posi + j * create->sellsize; // パズルマスの縦
			int s = create->posi + i * create->semisize - 50;
			int t = create->posi + j * create->semisize + 100;

			// マスを左クリックし, 色を反映させる
			if ((&mouse)->mButton == left && click(&(mouse), S, T, S + create->sellsize - 1, T + create->sellsize - 1)) {

				// 色塗り中であり, マスに色が塗られていない、または白色の場合リストに格納
				if (create->colorlist[i][j] == NULL || create->colorlist[i][j] == create->white) {
					create->colorlist[i][j] = create->tmp;
				}
				// 消しゴムボタンにより, 塗られているマスを白にするときの処理
				else if (create->tmp == create->white) {
					create->colorlist[i][j] = create->tmp;
				}
			}
			// colorlistの色情報を画面に反映
			if (create->colorlist[i][j] != 0) {
				DrawBox(S, T, S + create->sellsize - 1, T + create->sellsize - 1, create->colorlist[i][j], TRUE);

				// 縮小パズルのマスを黒く塗る
				if (create->colorlist[i][j] != create->white)
					DrawBox(s, t, s + create->semisize - 1, t + create->semisize - 1, create->black, TRUE);

				puzzle.puzzleData[i][j] = create->colorlist[i][j];
			}
		}
	}

	// 二重ループでパズル画面をチェック
	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < 20; i++) {
			int S = create->posi + i * create->sellsize + 200; // パズルマスの横
			int T = create->posi + j * create->sellsize; // パズルマスの縦

				// リセットボタンが押されたらすべてのマスを初期状態（白色）にする
			if ((&mouse)->mButton == left && click(&(mouse), 150, 630, 240, 720)) {
				create->colorlist[i][j] = create->white;
			}
		}
	}

	// 画像を取り込むボタンが押されたらエクスプローラーを起動し、パズル作成処理部に選択された画像を送信する
	// とりあえず、今は画像を取り込むまで
	if ((&mouse)->mButton == left && click(&(mouse), 830, 130, 1000, 180)) {
		int GrHandle = 0;
		char FullPath[MAX_PATH], FileName[MAX_PATH];

		// ウインドウモードで起動
		ChangeWindowMode(TRUE);

		OPENFILENAME ofn;

		memset(&ofn, 0, sizeof(OPENFILENAME));
		memset(FullPath, 0, sizeof(FullPath));
		memset(FileName, 0, sizeof(FileName));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = GetMainWindowHandle();

		// 説明の末尾に \0 を記載して、その後ろに表示するファイルの指定、最後に \0\0 を記述
		ofn.lpstrFilter = "Bitmap File  or  Jpeg File  or  Png File\0*.bmp;*.jpg;*.png\0\0";

		// lpstrFile に指定する配列にファイルのフルパスが代入される
		ofn.lpstrFile = FullPath;
		ofn.nMaxFile = sizeof(FullPath);

		// lpstrFileTitle に指定する配列にファイル名( フォルダパスが無い )が代入される
		ofn.lpstrFileTitle = FileName;
		ofn.nMaxFileTitle = sizeof(FileName);

		ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
		ofn.lpstrDefExt = "";

		// lpstrTitle に表示されるダイアログの説明を代入
		ofn.lpstrTitle = "画像ファイルの読み込み";

		// パスの指定が成功した場合は GetOpenFileName の戻り値は 0 以外になる
		if (GetOpenFileName(&ofn) != 0)
		{
			// ファイル名を取得できたら画像を読み込む
			GrHandle = LoadGraph(FullPath);
		}
	}
	DrawBox(830, 280, 1000, 330, create->black, FALSE);


	if ((&mouse)->mButton == left && click((&mouse), 830, 280, 1000, 330)) {
		// アップロードする

		//DrawBox(530, 350, 620, 440, create->black, FALSE);
		//DrawFormatString(540, 360, create->black, "本当に投稿しますか？");

	}

	// 戻るボタンが押されたらメニュー画面に移動
	if ((&mouse)->mButton == left && click((&mouse), 5, 630, 95, 720)) {
		return MenuScr;
	}

	ScreenFlip();
	return MakePuzzleScr;
}


/******************************
*** Function Name	: FinalizelizeMakePuzzle
*** Designer		: 杉田
*** Date			: 2020.6.28
*** Function		: パズル作成画面を終了する
					
*** Return			: 戻り値なし
******************************/
void FinalizeMakePuzzle(MakePuzzle_t* create) {
	InitGraph();
	InitFontToHandle();
}



/******************************
*** Function Name	: click
*** Designer		: 笹川
*** Date			: 2020.6.28
*** Function		: クリック判定
*** Return			: 成功: 1 or 失敗: 0
******************************/
int click(Mouse_t* mouse, int x1, int y1, int x2, int y2) {
	if (mouse->mX > x1 && mouse->mX < x2 && mouse->mY > y1 && mouse->mY < y2) {
		return 1;
	}
	return 0;
}