#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	private:
		int block_height = 40, block_width = 64; // 벽돌 자체의 높이, 너비 정하는 변수
		int vertical_block_num = 8, horizontal_block_num = 16; // 가로 세로 벽돌 개수 정하는 변수

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void rectangle(); // 사각형 난이도 조절 함수
		void heart(); // 하트 난이도 조절 함수
		void save_score(); // 점수 파일 세이브
		void load_score(); // 점수 파일 로드

		bool start_page = true; // 시작 화면 그릴지 말지 정하는 변수 
		bool menu_page = false; // 메뉴 화면 그릴지 말지 정하는 변수
		bool playing = false; // 게임 플레이 중인지 정하는 변수
		bool moving = false; // 공이 멈춰있으면 0, 공이 움직이면 1
		bool game_pause = false; // 게임 플레이 도중, 일시 정지 화면 그릴지 말지 정하는 변수
		bool game_clear = false; // 게임 클리어 판단 변수
		float time; // 시간 측정 변수
		
		ofImage Start_Image; // 시작 화면 그림 변수
		ofImage hp_image; // 목숨 그림 변수
		ofImage star_image; // 꽉 찬 별 그림 변수
		ofImage blank_star_image; // 속이 빈 별 그림 변수
		ofImage lion_image; // 블록 안에 그려져셔, 블록 꺠면 확인할 수 있는 그림 변수
		ofImage gameover_image; // 게임 오버 화면 그림 변수
		ofImage pause_image; // 정지 화면 그림 변수
		ofImage game_clear_image; // 게임 클리어 화면 그림 변수
		ofImage note_image; // BGM 버튼 옆에 음표 그림 변수

		ofSoundPlayer bump_sound; // 공 튕길때 나오는 소리 변수
		ofSoundPlayer bgm; // bgm 음악 파일 나타내는 변수 1
		ofSoundPlayer bgm2; // bgm 음악 파일 나타내는 변수 2
		ofSoundPlayer bgm3; // bgm 음악 파일 나타내는 변수 3
		ofSoundPlayer click_sound; // 클릭했을 때 들리는 소리 변수
		ofSoundPlayer gameclear_sound; // 게임 클리어 했을 때 나오는 소리 변수

		int bricks[8][16]; // 벽돌
		int xPos, xDir, yPos, yDir; // 공의 x좌표, x 방향 증가량, y좌표, y 방향 증가량 저장하는 변수
		int padX, padWidth; // 막대의 위치, 막대의 크기 저장하는 변수
		int ball_rad = 15; // 공의 크기 저장하는 변수
		int gameover; // 게임오버 여부 저장하는 변수
		int hp; // 목숨 개수 저장하는 변수
		int score[10] = { 0 }; // 각 스테이지 별 점수 저장하는 변수
		int brick_num; // 생겨난 벽돌 총 개수를 저장하는 변수
		int break_brick; // 부순 벽돌 개수 저장하는 변수
		int stage; // 어느 스테이지 진행하는지 나타내는 변수
		int bgm_num = 1;
};
