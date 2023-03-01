#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Brick Break Game"); // 프로그램명(윈도우 창) 정하기
	ofBackground(255); // 배경색 지정

	//--------------------------------------- 이미지, 오디오 파일 불러오기 ---------------------------------------------
	Start_Image.load("BrickBreak.jpg"); // 배경 이미지 불러오기
	hp_image.load("heart.png"); // 목숨 이미지 불러오기
	star_image.load("star.jpg"); // 채워진 별 이미지 파일 불러오기
	blank_star_image.load("star_blank.jpg"); // 빈 별 이미지 파일 불러오기
	lion_image.load("lion.png"); // 벽돌 뒤에 숨어있는 그림 파일 불러오기
	gameover_image.load("gameover.jpg"); // 게임 오버 화면 이미지 파일 불러오기
	pause_image.load("pause.jpg"); // 플레이 도중 멈췄을 떄 화면 이미지 파일 불러오기
	game_clear_image.load("clear.jpg"); // 게임 클리어 화면 이미지 파일 불러오기
	note_image.load("music.png"); // BGM 버튼 옆에 음표 이미지 파일 불러오기

	click_sound.load("click.mp3"); // 클릭 사운드 파일 불러오기
	bgm.load("bgm.mp3"); // bgm 사운드 파일 1 불러오기
	bgm2.load("bgm2.mp3"); // bgm 사운드 파일 2 불러오기
	bgm3.load("bgm3.mp3"); // bgm 사운드 파일 3 불러오기
	gameclear_sound.load("clear.mp3"); // 클리어 사운드 파일 불러오기
	bump_sound.load("ball.wav"); // 공 튕기는 사운드 파일 불러오기

	//--------------------------------------- 변수 초기값 설정 --------------------------------------------------------------
	gameover = 0; // 게임오버 변수. 0이면 게임 중, 1이면 게임오버
	time = 0.0; // 진행 시간 저장하는 변수
	hp = 3; // 목숨 변수. 기본값 3
	bgm.play(); // bgm 플레이
}

//--------------------------------------------------------------
void ofApp::update() {
	if (moving) { // 공이 움직이는 변수 값이 1인 경우
		xPos += xDir; // 공의 x 좌표가 xDir 만큼 증가
		yPos += yDir; // 공의 y 좌표가 yDir 만큼 증가
		time += 0.01; // 시간 변수 0.01씩 증가
	}
	if(!game_pause && 0 <= ofGetMouseX() && ofGetMouseX() <= 1024 - padWidth + 20)
		padX = ofGetMouseX(); // 공의 x 좌표를 마우스 위치로 설정

	// ------------------------------------------- 벽돌 부딪혔을 때 움직임 설정, 스테이지 4, 5, 9, 10 은 벽돌 체력 2개, 나머지 스테이지는 벽돌 체력 1개 ---------------------------------------
	if (stage % 5 == 4 || stage % 5 == 0) { // 스테이지 4, 5, 9, 10의 경우
		if (yPos < block_height * vertical_block_num + ball_rad) // 공의 y 좌표가 막대 위쪽에 위치하면서
			if (bricks[yPos / block_height][xPos / block_width] == 1) { // bricks 값이 1인 경우
				bump_sound.play(); // 공 튕기는 소리 플레이
				bricks[yPos / block_height][xPos / block_width] = 2; // bricks 값을 2로 변경
				if (xPos < (xPos / block_width) * block_width && yPos >(yPos / block_height) * block_height) {
					if (abs((xPos / block_width) * block_width - xPos) <= ball_rad) {
						xDir *= -1;
					}
				}
				else if (xPos < (xPos / block_width + 1) * block_width - 2 && yPos >(yPos / block_height + 1) * block_height - 2) {
					if (yPos - ((yPos / block_height + 1) * block_height - 2) <= ball_rad) {
						yDir *= -1;
					}
				}
				else if (xPos > (xPos / block_width + 1) * block_width - 2 && yPos < (yPos / block_height + 1) * block_height - 2) {
					if (((xPos / block_width + 1) * block_width - 2) - xPos <= ball_rad) {
						xDir *= -1;
					}
				}
				else if (xPos > (xPos / block_width) * block_width && yPos < (yPos / block_height) * block_height) {
					if ((yPos / block_height) * block_height - yPos <= ball_rad) {
						yDir *= -1;
					}
				}
				else
					yDir *= -1;
			}
			else if (bricks[yPos / block_height][xPos / block_width] == 2) { // bricks 값이 2인 경우
				bump_sound.play(); // 공 튕기는 소리 플레이
				bricks[yPos / block_height][xPos / block_width] = 0; // bricks 값을 0으로 변경
				if (xPos < (xPos / block_width) * block_width && yPos >(yPos / block_height) * block_height) {
					if (abs((xPos / block_width) * block_width - xPos) <= ball_rad) {
						xDir *= -1;
					}
				}
				else if (xPos < (xPos / block_width + 1) * block_width - 2 && yPos >(yPos / block_height + 1) * block_height - 2) {
					if (yPos - ((yPos / block_height + 1) * block_height - 2) <= ball_rad) {
						yDir *= -1;
					}
				}
				else if (xPos > (xPos / block_width + 1) * block_width - 2 && yPos < (yPos / block_height + 1) * block_height - 2) {
					if (((xPos / block_width + 1) * block_width - 2) - xPos <= ball_rad) {
						xDir *= -1;
					}
				}
				else if (xPos > (xPos / block_width) * block_width && yPos < (yPos / block_height) * block_height) {
					if ((yPos / block_height) * block_height - yPos <= ball_rad) {
						yDir *= -1;
					}
				}
				else
					yDir *= -1;
				break_brick++; // 부순 벽돌 개수 1개 증가
			}
	}
	else if (stage % 5 >= 1 && stage % 5 <= 3) { // 스테이지가 1, 2, 3, 6, 7, 8 인 경우
		if (yPos < block_height * vertical_block_num + ball_rad) // 공의 y 좌표가 막대 위쪽에 위치하면서
			if (bricks[yPos / block_height][xPos / block_width] == 1) { // bricks 값이 1인 경우
				bump_sound.play(); // 공 튕기는 소리 플레이
				bricks[yPos / block_height][xPos / block_width] = 0; // bricks 값을 0으로 변경
				if (xPos < (xPos / block_width) * block_width && yPos >(yPos / block_height) * block_height) {
					if (abs((xPos / block_width) * block_width - xPos) <= ball_rad) {
						xDir *= -1;
					}
				}
				else if (xPos < (xPos / block_width + 1) * block_width - 2 && yPos >(yPos / block_height + 1) * block_height - 2) {
					if (yPos - ((yPos / block_height + 1) * block_height - 2) <= ball_rad) {
						yDir *= -1;
					}
				}
				else if (xPos > (xPos / block_width + 1) * block_width - 2 && yPos < (yPos / block_height + 1) * block_height - 2) {
					if (((xPos / block_width + 1) * block_width - 2) - xPos <= ball_rad) {
						xDir *= -1;
					}
				}
				else if (xPos > (xPos / block_width) * block_width && yPos < (yPos / block_height) * block_height) {
					if ((yPos / block_height) * block_height - yPos <= ball_rad) {
						yDir *= -1;
					}
				}
				else
					yDir *= -1;
				break_brick++; // 부순 벽돌 개수 1개 증가
			}
	}
	// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	if (moving == 1 && break_brick == brick_num) { // 게임 클리어 했을 때
		moving = 0; // 공의 움직임 변수 0으로 초기화
		game_clear = 1; // 게임 클리어 변수 1로 초기화
		playing = 0; // 게임 플레이 중 여부 변수 0으로 초기화
		score[stage - 1] = hp; // 게임 클리어 했을 때 체력을 점수로 기록, 점수는 메뉴 페이지에서 별 개수로 나타남
		gameclear_sound.play(); // 게임 클리어 오디오 출력
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	// ---------------------------------------------- 초기 화면 --------------------------
	if (start_page) { // 시작 화면 변수 값이 1이면
		Start_Image.draw(0, 80);
	} // 시작 이미지 파일 그리기

	if (gameover) { // 게임 오버 변수 값이 1이면
		ofSetColor(255); // 흰색
		gameover_image.draw(120, 120); // 게임 오버 메세지 파일 그리기 (r 누르면 같은 스테이지 리트라이, q 누르면 메뉴 페이지로)

		return;
	}

	if (game_clear) { // 게임 클리어 변수 값이 1이면
		ofSetColor(ofColor::aqua);
		game_clear_image.draw(120, 120); // 게임 클리어 화면 그리기
		ofSetColor(255); // 흰색
		for (int k = 0; k < score[stage-1]; k++) // 클리어 한 점수에 따라 채워진 별, 빈 별 그리기
			star_image.draw(300 + 150 * k, 280, 80, 80); // 채워진 별 그리기
		for (int j = score[stage - 1]; j < 3; j++)
			blank_star_image.draw(300 + 150 * j, 280, 80, 80); // 빈 별 그리기
	}

	// ---------------------------------------------- 메뉴 화면 ----------------------------
	if (menu_page) { // 메뉴 페이지 변수 값이 1이면
		ofSetColor(ofColor::lemonChiffon);
		ofDrawRectangle(600, 200, 200, 60);
		ofSetColor(0);
		ofDrawBitmapString("Save", 685, 235); // 세이브 버튼 그리기

		ofSetColor(ofColor::lemonChiffon);
		ofDrawRectangle(600, 300, 200, 60);
		ofSetColor(0);
		ofDrawBitmapString("Load", 685, 335); // 로드 버튼 그리기

		note_image.draw(480, 50, 30, 30); // 음표 이미지 그리기
		ofSetColor(ofColor::lemonChiffon);
		ofDrawRectangle(550, 50, 300, 30); // BGM 버튼 중간 직사각형 그리기
		ofDrawTriangle(540, 50, 540, 80, 520, 65); // BGM 버튼 좌측 삼각형 그리기
		ofDrawTriangle(860, 50, 860, 80, 880, 65); // BGM 버튼 우측 삼각형 그리기
		ofSetColor(0);
		if (bgm_num == 1)
			ofDrawBitmapString("BGM 1", 680, 73); // BGM 1 나타내기
		else if (bgm_num == 2)
			ofDrawBitmapString("BGM 2", 680, 73); // BGM 2 나타내기
		else if (bgm_num == 3)
			ofDrawBitmapString("BGM 3", 680, 73); // BGM 3 나타내기

		for (int i = 0; i < 5; i++) {
			ofSetColor(0); // 검은색
			ofDrawBitmapString("Rectangle", 20, 120); // "Rectangle"이라는 문자열 그리기

			ofSetColor(135, 206, 250); // 하늘색
			string level_back = to_string(i + 1);
			string level_front = "Lv. ";
			level_front = level_front + level_back; // level_front라는 string 변수에 "Lv. i"(i 값은 반복문 시행되면서 바뀜)라는 문자열을 저장 

			ofDrawRectangle(20 + 100 * i, 150, 90, 125); // 직사각형 그리기
			ofSetColor(255); // 검은색
			ofDrawBitmapString(level_front, 20 + 100 * i, 250); // level_front 문자열 그리기

			for (int k = 0; k < score[i]; k++)
				star_image.draw(25 + 30 * k + 100 * i, 200, 20, 20); // 점수만큼 채워진 별 그리기
			for (int j = score[i]; j < 3; j++)
				blank_star_image.draw(25 + 30 * j + 100 * i, 200, 20, 20); // (3 - 점수)개의 빈 별 그리기
		}

		ofSetColor(0); // 검은색
		ofDrawBitmapString("Heart", 20, 420); // "Heart"라는 문자열 출력

		for (int i = 0; i < 5; i++) {
			ofSetColor(135, 206, 250); // 하늘색
			string levelN = to_string(i + 1);
			string levelName = "Lv. ";
			levelName = levelName + levelN; // level_front라는 string 변수에 "Lv. i"(i 값은 반복문 시행되면서 바뀜)라는 문자열을 저장 
			 
			ofDrawRectangle(20 + 100 * i, 450, 90, 125); // 직사각형 그리기
			ofSetColor(255); // 검은색
			ofDrawBitmapString(levelName, 20 + 100 * i, 550); // level_front 문자열 그리기

			for (int k = 0; k < score[i + 5]; k++) 
				star_image.draw(25 + 30 * k + 100 * i, 500, 20, 20); // 점수만큼 채워진 별 그리기
			for (int j = score[i + 5]; j < 3; j++)
				blank_star_image.draw(25 + 30 * j + 100 * i, 500, 20, 20); // (3 - 점수)개의 빈 별 그리기
		}
	}

	// ---------------------------------------------- 플레이 화면 -------------------------
	if (playing) { // 게임 플레이 변수 값이 1이면
		for(int i = 0; i < hp; i++)
			hp_image.draw(600 + 30 * i, 30, 10, 10); // 목숨 개수 만큼 이미지 그리기

		ofSetColor(255); // 흰색
		if (stage >= 1 && stage <= 5)
			lion_image.draw(300, 100, 400, 200); // 벽돌 뒤에 그림 그리기
		else if (stage >= 6 && stage <= 10)
			lion_image.draw(400, 150, 300, 100); // 벽돌 뒤에 그림 그리기

		for (int i = 0; i < vertical_block_num; i++) // 벽돌 세로개의 개수만큼
			for (int j = 0; j < horizontal_block_num; j++){ // 벽돌 가로개의 개수만큼
				if (bricks[i][j] == 1) { // bricks 값이 1이면
					ofSetColor(ofColor::seaGreen);
					ofDrawRectangle(j*block_width, i*block_height, block_width - 2, block_height - 2); // 직사각형 그리기
				}
				else if (bricks[i][j] == 2) {
					ofSetColor(ofColor::skyBlue);
					ofDrawRectangle(j*block_width, i*block_height, block_width - 2, block_height - 2); // 직사각형 그리기
				}
			}

		if (!moving && !game_pause) { // (공이 움직이지 않으면서 일시 정지 변수 값이 0인 경우) = 게임 바로 시작했을 때나 공을 떨어뜨렸을 때
			xPos = padX + padWidth / 2; // 공의 x 좌표 값을 막대 중앙으로 설정
			yPos = ofGetHeight() - 50 - ball_rad; // 공의 y 좌표 값을 막대 바로 위로 설정
		}

		ofSetColor(ofColor::deepSkyBlue);
		ofCircle(xPos, yPos, ball_rad); // 원 그리기(= 공)

		ofSetColor(ofColor::hotPink);
		ofLine(padX, ofGetHeight() - 50, padX + padWidth, ofGetHeight() - 50); // 선 그리기(= 막대)

		ofDrawBitmapString("time : ", 10, 30); // "time : "이라는 문자열 그리기
		ofDrawBitmapString(to_string(time), 100, 30); // time 값을 string 변수로 바꿔서 그리기

		if (ofGetMousePressed(OF_MOUSE_BUTTON_RIGHT)) {
			moving = true;
		} // 마우스 우클릭하면 게임 시작

		if (xPos < ball_rad || xPos > ofGetWidth() - ball_rad) { // 왼쪽, 오른쪽 벽 부딪힌 경우
			xDir *= -1;
			bump_sound.play(); // 공 튕기는 소리 플레이
		}

		if (yPos < ball_rad) { // 천장 부딪힌 경우
			yDir *= -1;
			bump_sound.play(); // 공 튕기는 소리 플레이
		}

		if (yPos == ofGetHeight() - 50 - ball_rad) { // 바에 부딪힌 경우
			if (moving) { // 움직임 변수 값이 1인 경우
				if (xPos >= padX && xPos <= padX + padWidth) {
					yDir *= -1;
					bump_sound.play(); // 공 튕기는 소리 플레이
				}
			}
		}

		if (yPos >= ofGetHeight() - ball_rad) { // 공의 y좌표가 막대 위치보다 크면(= 막대 아래에 공이 위치하면)
			hp--; // 목숨 1개 차감
			time = 0; // 시간은 다시 0으로 초기화
			moving = 0; // 공이 움직임 여부 변수 0으로 초기화

			if (hp == 0) // 목숨이 0개면
				gameover = 1; // 게임 오버
		}
	}


	//-------------------------------------- 게임 플레이 중 멈춤 화면----------------------------------------------
	if (game_pause) { // 일시 정지 변수 값이 1이면
		ofSetColor(ofColor::blue);
		pause_image.draw(120, 120); // 일시 정지 화면 그리기
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//--------------------------------------------- 시작 화면 ---------------------------------------------------
	if (start_page) { // 시작 화면에서
		if (key == ' ') { // 스페이스바 누르면
			menu_page = 1; // 메뉴 페이지 변수 1로 초기화
			start_page = 0; // 시작 화면 변수 0으로 초기화
		}
	}

	//---------------------------------------------- 게임 플레이 도중 ------------------------------------------------
	if (playing && (key == 's' || key == 'S')) { // 게임 플레이 도중 s 키 누르면
		moving = 0; // 공 움직임 멈추기
		game_pause = 1; // 일시 정지 변수 1로 초기화
	}

	//-------------------------------------------- 게임 오버 화면 ------------------------------------------------------
	if (gameover && (key == 'q' || key == 'Q')) { // 게임 오버 상태에서 q 키 누르면 -> 메뉴화면으로
		gameover = 0; // 게임 오버 변수 0으로 초기화
		moving = 0; // 공 움직임 변수 0으로 초기화
		playing = 0; // 게임 플레이 도중 나타내는 변수 0으로 초기화
		menu_page = 1; // 메뉴 페이지 변수 1로 초기화
		hp = 3; // 목숨 변수 3으로 초기화
		time = 0; // 시간 변수 0으로 초기화
		xPos = padX + padWidth / 2; // 공의 x축 좌표를, 막대 중앙으로 초기화
		yPos = ofGetHeight() - 50 - ball_rad; // 공의 y축 좌표를, 막대 바로 위로 초기화
	}

	if (gameover && (key == 'r' || key == 'R')) { // 게임 오버 상태에서 r 키 누르면 -> 같은 스테이지 재도전
		gameover = 0; // 게임 오버 변수 0으로 초기화
		moving = 0; // 공 움직임 변수 0으로 초기화
		playing = 1; // 게임 플레이 도중 나타내는 변수 1로 초기화
		hp = 3; // 목숨 변수 3으로 초기화
		time = 0; // 시간 변수 0으로 초기화
		xPos = padX + padWidth / 2; // 공의 x축 좌표를, 막대 중앙으로 초기화
		yPos = ofGetHeight() - 50 - ball_rad; // 공의 y축 좌표를, 막대 바로 위로 초기화

		if (1 <= stage && stage <= 5)
			rectangle();
		else if (6 <= stage && stage <= 10)
			heart(); // 스테이지 별로 난이도 함수 재 호출
	}

	//------------------ (테스트용 키세팅) l 누르면 게임 클리어, k 누르면 게임 오버 -------------------------
	/*if (key == 'l' || key == 'L')
		break_brick = 96;
	if (key == 'k' || key == 'K')
		gameover = 1;*/
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	//------------------------------------- 메뉴 페이지 -------------------------------------------------
	if (menu_page) { // 메뉴 페이지에서 난이도 선택하는 과정
		if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
			//-------------------------------------------- 스테이지 설정 ------------------------------------------------------
			if (20 <= x && x <= 110 && 150 <= y && y <= 275) {
				stage = 1;
				rectangle();
				click_sound.play(); // 클릭 사운드 출력
				menu_page = 0; // 메뉴 페이지 비활성화
				playing = 1; // 게임 플레이 화면 활성화
			}
			else if (120 <= x && x <= 210 && 150 <= y && y <= 275) {
				stage = 2;
				rectangle();
				click_sound.play(); // 클릭 사운드 출력
				menu_page = 0; // 메뉴 페이지 비활성화
				playing = 1; // 게임 플레이 화면 활성화
			}
			else if (220 <= x && x <= 310 && 150 <= y && y <= 275) {
				stage = 3;
				rectangle();
				click_sound.play(); // 클릭 사운드 출력
				menu_page = 0; // 메뉴 페이지 비활성화
				playing = 1; // 게임 플레이 화면 활성화
			}
			else if (320 <= x && x <= 410 && 150 <= y && y <= 275) {
				stage = 4;
				rectangle();
				click_sound.play(); // 클릭 사운드 출력
				menu_page = 0; // 메뉴 페이지 비활성화
				playing = 1; // 게임 플레이 화면 활성화
			}
			else if (420 <= x && x <= 510 && 150 <= y && y <= 275) {
				stage = 5;
				rectangle();
				click_sound.play(); // 클릭 사운드 출력
				menu_page = 0; // 메뉴 페이지 비활성화
				playing = 1; // 게임 플레이 화면 활성화
			}
			else if (20 <= x && x <= 110 && 450 <= y && y <= 575) {
				stage = 6;
				heart();
				click_sound.play(); // 클릭 사운드 출력
				menu_page = 0; // 메뉴 페이지 비활성화
				playing = 1; // 게임 플레이 화면 활성화
			}
			else if (120 <= x && x <= 210 && 450 <= y && y <= 575) {
				stage = 7;
				heart();
				click_sound.play(); // 클릭 사운드 출력
				menu_page = 0; // 메뉴 페이지 비활성화
				playing = 1; // 게임 플레이 화면 활성화
			}
			else if (220 <= x && x <= 310 && 450 <= y && y <= 575) {
				stage = 8;
				heart();
				click_sound.play(); // 클릭 사운드 출력
				menu_page = 0; // 메뉴 페이지 비활성화
				playing = 1; // 게임 플레이 화면 활성화
			}
			else if (320 <= x && x <= 410 && 450 <= y && y <= 575) {
				stage = 9;
				heart();
				click_sound.play(); // 클릭 사운드 출력
				menu_page = 0; // 메뉴 페이지 비활성화
				playing = 1; // 게임 플레이 화면 활성화
			}
			else if (420 <= x && x <= 510 && 450 <= y && y <= 575) {
				stage = 10;
				heart();
				click_sound.play(); // 클릭 사운드 출력
				menu_page = 0; // 메뉴 페이지 비활성화
				playing = 1; // 게임 플레이 화면 활성화
			}
			//------------------------------- 스테이지 설정 끝 -----------------------------------------------------

			//------------------------------- 세이브, 로드 버튼 -----------------------------------------------------
			if (600 <= x && x <= 800 && 200 <= y && y <= 260) {
				save_score();
			}
			else if (600 <= x && x <= 800 && 300 <= y && y <= 360) {
				load_score();
			}
			//------------------------------- 세이브, 로드 버튼 끝 --------------------------------------------

			//------------------------------- BGM 버튼 ---------------------------------------------------
			if (bgm_num == 1 && (860 <= x && x <= 880 && 50 <= y && y <= 80)) { // bgm 블록에서 오른쪽 화살표 클릭하면
				bgm.stop(); // bgm 소리 종료
				bgm2.play(); // bgm 2 소리 플레이
				bgm_num = 2; // bgm_num 변수 2로 초기화
			}
			else if (bgm_num == 2 && (860 <= x && x <= 880 && 50 <= y && y <= 80)) {
				bgm2.stop(); // bgm 2 소리 종료
				bgm3.play(); // bgm 3 소리 플레이
				bgm_num = 3; // bgm_num 변수 3으로 초기화
			}
			else if (bgm_num == 3 && (520 <= x && x <= 540 && 50 <= y && y <= 80)) {
				bgm3.stop(); // bgm 3 소리 종료
				bgm2.play(); // bgm 2 소리 플레이
				bgm_num = 2; // bgm_num 변수 2로 초기화
			}
			else if (bgm_num == 2 && (520 <= x && x <= 540 && 50 <= y && y <= 80)) {
				bgm2.stop(); // bgm 2 소리 종료
				bgm.play(); // bgm 소리 플레이
				bgm_num = 1; // bgm_num 변수 1로 초기화
			}

			//------------------------------- BGM 버튼 끝 ------------------------------------------------
		}
	}

	//------------------------------------------ 일시 정지 화면 ----------------------------------------------
	if (game_pause) { // 게임 도중 일시 정지 시킨 경우
		if (240 <= x && x <= 440 && 340 <= y && y <= 380) { // 다시 진행
			game_pause = 0; // 일시 정지 변수 0으로 초기화
			moving = 1; // 공의 움직임 여부 변수 1로 초기화
		}
		else if (510 <= x && x <= 590 && 340 <= y && y <= 380) { // 리트라이
			game_pause = 0; // 일시 정지 변수 0으로 초기화
			moving = 0; // 공의 움직임 여부 변수 0으로 초기화
			playing = 1; // 게임 플레이 화면 활성화
			hp = 3; // 목숨 변수 3으로 초기화
			time = 0; // 시간 변수 0으로 초기화
			xPos = padX + padWidth / 2; // 공의 x축 좌표를, 막대 중앙으로 초기화
			yPos = ofGetHeight() - 50 - ball_rad; // 공의 y축 좌표를, 막대 바로 위로 초기화

			if (1 <= stage && stage <= 5)
				rectangle();
			else if (6 <= stage && stage <= 10)
				heart();
		}
		else if (660 <= x && x <= 740 && 340 <= y && y <= 380) { // 메뉴 페이지로
			game_pause = 0; // 일시 정지 변수 0으로 초기화
			moving = 0; // 공의 움직임 여부 변수 0으로 초기화
			playing = 0; // 게임 플레이 화면 비활성화
			menu_page = 1; // 메뉴 페이지 화면 활성화
			hp = 3; // 목숨 변수 3으로 초기화
			time = 0; // 시간 변수 0으로 초기화
			xPos = padX + padWidth / 2; // 공의 x축 좌표를, 막대 중앙으로 초기화
			yPos = ofGetHeight() - 50 - ball_rad; // 공의 y축 좌표를, 막대 바로 위로 초기화
		}
	}

	//------------------------------- 게임 클리어 화면 ----------------------------------------------------
	if (game_clear && ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) { // 게임 클리어한 경우
		if (650 <= x && x <= 730 && 380 <= y && y <= 410) {
			gameclear_sound.stop(); // 게임 클리어 사운드 멈추기
			game_clear = 0; // 다음 게임을 위해, 클리어 변수는 다시 0
			moving = 0; // 다음 게임을 위해, 공 움직임 여부 변수 값 0으로 초기화
			playing = 0; // 다음 게임을 위해, 플레이 중 여부 변수 값 0으로 초기화
			menu_page = 1; // 메뉴 페이지로 돌아가기 위해, 메뉴 화면 변수 1로 초기화
			hp = 3; // 다음 게임을 위해, 목숨 변수 3으로 초기화
			time = 0; // 다음 게임을 위해, 시간 변수 0으로 초기화
			xPos = padX + padWidth / 2; // 다음 게임을 위해, 공 위치 초기 상태로
			yPos = ofGetHeight() - 50 - ball_rad; // 다음 게임을 위해, 공 위치 초기 상태로
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//----------------------------------------- 난이도 조절 함수 ----------------------------------

void ofApp::rectangle() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 16; j++)
			bricks[i][j] = 0; // 기존 블록들 초기화

	for (int i = 2; i < 8; i++)
		for (int j = 0; j < 16; j++)
			bricks[i][j] = 1; // 사각형 모양 만들기

	switch (stage) { // 스테이지 별로 난이도 설정
	case 1:
		xDir = yDir = 10;
		padWidth = 250;
		brick_num = 96;
		break_brick = 0;
		break;
	case 2:
		xDir = yDir = 10;
		padWidth = 250;
		brick_num = 96;
		break_brick = 0;
		break;
	case 3:
		xDir = yDir = 10;
		padWidth = 200;
		brick_num = 96;
		break_brick = 0;
		break;
	case 4:
		xDir = yDir = 15;
		padWidth = 250;
		ball_rad = 13;
		brick_num = 96;
		break_brick = 0;
		break;
	case 5:
		xDir = yDir = 10;
		padWidth = 200;
		ball_rad = 13;
		brick_num = 96;
		break_brick = 0;
		break;
	}
}

void ofApp::heart() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 16; j++)
			bricks[i][j] = 0; // 기존 블록 초기화

	bricks[1][4] = bricks[1][11] = 1;
	bricks[2][3] = bricks[2][4] = bricks[2][5] = bricks[2][10] = bricks[2][11] = bricks[2][12] = 1;
	for (int i = 2; i <= 6; i++)
		bricks[3][i] = 1;
	for (int i = 3; i <= 7; i++)
		bricks[3][7 + i] = 1;
	for (int i = 1; i <= 14; i++)
		bricks[4][i] = 1;
	for (int i = 3; i <= 12; i++)
		bricks[5][i] = 1;
	for (int i = 5; i <= 10; i++)
		bricks[6][i] = 1;
	bricks[7][7] = bricks[7][8] = 1; // 하트 모양 만들기

	switch (stage) { // 스테이지 별로 난이도 조절
	case 6:
		xDir = yDir = 8;
		padWidth = 300;
		brick_num = 50;
		break_brick = 0;
		break;
	case 7:
		xDir = yDir = 10;
		padWidth = 250;
		brick_num = 50;
		break_brick = 0;
		break;
	case 8:
		xDir = yDir = 10;
		padWidth = 200;
		brick_num = 50;
		break_brick = 0;
		break;
	case 9:
		xDir = yDir = 15;
		padWidth = 250;
		ball_rad = 13;
		brick_num = 50;
		break_brick = 0;
		break;
	case 10:
		xDir = yDir = 10;
		padWidth = 200;
		ball_rad = 13;
		brick_num = 50;
		break_brick = 0;
		break;
	}
}

//------------------------------------------- 난이도 조절 함수 끝 ------------------------------------------

//--------------------------------------- 세이브, 로드 함수 --------------------------------------

void ofApp::load_score() { // 점수 로드 해주는 함수
	ifstream file_op("rank.txt"); // rank.txt 파일 오픈
	int tmp, i = 0; 

	if (file_op.is_open()) { // 파일이 열려있으면
		while (file_op >> tmp) { // 오픈한 파일의 값을 읽어서 tmp 값 초기화
			score[i] = tmp; // score 배열의 값에 tmp 값 대입
			i++;
		}
	}
	else // 파일 못열면 에러메세지 출력
		cout << "file open error!" << endl;

	file_op.close(); // 파일 닫기
}

void ofApp::save_score() { // 점수 세이브 해주는 함수
	ofstream file_op("rank.txt"); // rank.txt 파일 오픈
	int tmp, i = 0;
	
	for (int i = 0; i < 10; i++) {
		file_op << score[i] << endl; // score 배열의 값들을 rank.txt 파일에 덮어쓰기
	}

	file_op.close(); // 파일 닫기
}
//---------------------------------------- 세이브, 로드 함수 끝 ----------------------------------

