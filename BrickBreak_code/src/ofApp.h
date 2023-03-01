#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	private:
		int block_height = 40, block_width = 64; // ���� ��ü�� ����, �ʺ� ���ϴ� ����
		int vertical_block_num = 8, horizontal_block_num = 16; // ���� ���� ���� ���� ���ϴ� ����

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

		void rectangle(); // �簢�� ���̵� ���� �Լ�
		void heart(); // ��Ʈ ���̵� ���� �Լ�
		void save_score(); // ���� ���� ���̺�
		void load_score(); // ���� ���� �ε�

		bool start_page = true; // ���� ȭ�� �׸��� ���� ���ϴ� ���� 
		bool menu_page = false; // �޴� ȭ�� �׸��� ���� ���ϴ� ����
		bool playing = false; // ���� �÷��� ������ ���ϴ� ����
		bool moving = false; // ���� ���������� 0, ���� �����̸� 1
		bool game_pause = false; // ���� �÷��� ����, �Ͻ� ���� ȭ�� �׸��� ���� ���ϴ� ����
		bool game_clear = false; // ���� Ŭ���� �Ǵ� ����
		float time; // �ð� ���� ����
		
		ofImage Start_Image; // ���� ȭ�� �׸� ����
		ofImage hp_image; // ��� �׸� ����
		ofImage star_image; // �� �� �� �׸� ����
		ofImage blank_star_image; // ���� �� �� �׸� ����
		ofImage lion_image; // ��� �ȿ� �׷�����, ��� �Ƹ� Ȯ���� �� �ִ� �׸� ����
		ofImage gameover_image; // ���� ���� ȭ�� �׸� ����
		ofImage pause_image; // ���� ȭ�� �׸� ����
		ofImage game_clear_image; // ���� Ŭ���� ȭ�� �׸� ����
		ofImage note_image; // BGM ��ư ���� ��ǥ �׸� ����

		ofSoundPlayer bump_sound; // �� ƨ�涧 ������ �Ҹ� ����
		ofSoundPlayer bgm; // bgm ���� ���� ��Ÿ���� ���� 1
		ofSoundPlayer bgm2; // bgm ���� ���� ��Ÿ���� ���� 2
		ofSoundPlayer bgm3; // bgm ���� ���� ��Ÿ���� ���� 3
		ofSoundPlayer click_sound; // Ŭ������ �� �鸮�� �Ҹ� ����
		ofSoundPlayer gameclear_sound; // ���� Ŭ���� ���� �� ������ �Ҹ� ����

		int bricks[8][16]; // ����
		int xPos, xDir, yPos, yDir; // ���� x��ǥ, x ���� ������, y��ǥ, y ���� ������ �����ϴ� ����
		int padX, padWidth; // ������ ��ġ, ������ ũ�� �����ϴ� ����
		int ball_rad = 15; // ���� ũ�� �����ϴ� ����
		int gameover; // ���ӿ��� ���� �����ϴ� ����
		int hp; // ��� ���� �����ϴ� ����
		int score[10] = { 0 }; // �� �������� �� ���� �����ϴ� ����
		int brick_num; // ���ܳ� ���� �� ������ �����ϴ� ����
		int break_brick; // �μ� ���� ���� �����ϴ� ����
		int stage; // ��� �������� �����ϴ��� ��Ÿ���� ����
		int bgm_num = 1;
};
