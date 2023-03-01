#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Brick Break Game"); // ���α׷���(������ â) ���ϱ�
	ofBackground(255); // ���� ����

	//--------------------------------------- �̹���, ����� ���� �ҷ����� ---------------------------------------------
	Start_Image.load("BrickBreak.jpg"); // ��� �̹��� �ҷ�����
	hp_image.load("heart.png"); // ��� �̹��� �ҷ�����
	star_image.load("star.jpg"); // ä���� �� �̹��� ���� �ҷ�����
	blank_star_image.load("star_blank.jpg"); // �� �� �̹��� ���� �ҷ�����
	lion_image.load("lion.png"); // ���� �ڿ� �����ִ� �׸� ���� �ҷ�����
	gameover_image.load("gameover.jpg"); // ���� ���� ȭ�� �̹��� ���� �ҷ�����
	pause_image.load("pause.jpg"); // �÷��� ���� ������ �� ȭ�� �̹��� ���� �ҷ�����
	game_clear_image.load("clear.jpg"); // ���� Ŭ���� ȭ�� �̹��� ���� �ҷ�����
	note_image.load("music.png"); // BGM ��ư ���� ��ǥ �̹��� ���� �ҷ�����

	click_sound.load("click.mp3"); // Ŭ�� ���� ���� �ҷ�����
	bgm.load("bgm.mp3"); // bgm ���� ���� 1 �ҷ�����
	bgm2.load("bgm2.mp3"); // bgm ���� ���� 2 �ҷ�����
	bgm3.load("bgm3.mp3"); // bgm ���� ���� 3 �ҷ�����
	gameclear_sound.load("clear.mp3"); // Ŭ���� ���� ���� �ҷ�����
	bump_sound.load("ball.wav"); // �� ƨ��� ���� ���� �ҷ�����

	//--------------------------------------- ���� �ʱⰪ ���� --------------------------------------------------------------
	gameover = 0; // ���ӿ��� ����. 0�̸� ���� ��, 1�̸� ���ӿ���
	time = 0.0; // ���� �ð� �����ϴ� ����
	hp = 3; // ��� ����. �⺻�� 3
	bgm.play(); // bgm �÷���
}

//--------------------------------------------------------------
void ofApp::update() {
	if (moving) { // ���� �����̴� ���� ���� 1�� ���
		xPos += xDir; // ���� x ��ǥ�� xDir ��ŭ ����
		yPos += yDir; // ���� y ��ǥ�� yDir ��ŭ ����
		time += 0.01; // �ð� ���� 0.01�� ����
	}
	if(!game_pause && 0 <= ofGetMouseX() && ofGetMouseX() <= 1024 - padWidth + 20)
		padX = ofGetMouseX(); // ���� x ��ǥ�� ���콺 ��ġ�� ����

	// ------------------------------------------- ���� �ε����� �� ������ ����, �������� 4, 5, 9, 10 �� ���� ü�� 2��, ������ ���������� ���� ü�� 1�� ---------------------------------------
	if (stage % 5 == 4 || stage % 5 == 0) { // �������� 4, 5, 9, 10�� ���
		if (yPos < block_height * vertical_block_num + ball_rad) // ���� y ��ǥ�� ���� ���ʿ� ��ġ�ϸ鼭
			if (bricks[yPos / block_height][xPos / block_width] == 1) { // bricks ���� 1�� ���
				bump_sound.play(); // �� ƨ��� �Ҹ� �÷���
				bricks[yPos / block_height][xPos / block_width] = 2; // bricks ���� 2�� ����
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
			else if (bricks[yPos / block_height][xPos / block_width] == 2) { // bricks ���� 2�� ���
				bump_sound.play(); // �� ƨ��� �Ҹ� �÷���
				bricks[yPos / block_height][xPos / block_width] = 0; // bricks ���� 0���� ����
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
				break_brick++; // �μ� ���� ���� 1�� ����
			}
	}
	else if (stage % 5 >= 1 && stage % 5 <= 3) { // ���������� 1, 2, 3, 6, 7, 8 �� ���
		if (yPos < block_height * vertical_block_num + ball_rad) // ���� y ��ǥ�� ���� ���ʿ� ��ġ�ϸ鼭
			if (bricks[yPos / block_height][xPos / block_width] == 1) { // bricks ���� 1�� ���
				bump_sound.play(); // �� ƨ��� �Ҹ� �÷���
				bricks[yPos / block_height][xPos / block_width] = 0; // bricks ���� 0���� ����
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
				break_brick++; // �μ� ���� ���� 1�� ����
			}
	}
	// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	if (moving == 1 && break_brick == brick_num) { // ���� Ŭ���� ���� ��
		moving = 0; // ���� ������ ���� 0���� �ʱ�ȭ
		game_clear = 1; // ���� Ŭ���� ���� 1�� �ʱ�ȭ
		playing = 0; // ���� �÷��� �� ���� ���� 0���� �ʱ�ȭ
		score[stage - 1] = hp; // ���� Ŭ���� ���� �� ü���� ������ ���, ������ �޴� ���������� �� ������ ��Ÿ��
		gameclear_sound.play(); // ���� Ŭ���� ����� ���
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	// ---------------------------------------------- �ʱ� ȭ�� --------------------------
	if (start_page) { // ���� ȭ�� ���� ���� 1�̸�
		Start_Image.draw(0, 80);
	} // ���� �̹��� ���� �׸���

	if (gameover) { // ���� ���� ���� ���� 1�̸�
		ofSetColor(255); // ���
		gameover_image.draw(120, 120); // ���� ���� �޼��� ���� �׸��� (r ������ ���� �������� ��Ʈ����, q ������ �޴� ��������)

		return;
	}

	if (game_clear) { // ���� Ŭ���� ���� ���� 1�̸�
		ofSetColor(ofColor::aqua);
		game_clear_image.draw(120, 120); // ���� Ŭ���� ȭ�� �׸���
		ofSetColor(255); // ���
		for (int k = 0; k < score[stage-1]; k++) // Ŭ���� �� ������ ���� ä���� ��, �� �� �׸���
			star_image.draw(300 + 150 * k, 280, 80, 80); // ä���� �� �׸���
		for (int j = score[stage - 1]; j < 3; j++)
			blank_star_image.draw(300 + 150 * j, 280, 80, 80); // �� �� �׸���
	}

	// ---------------------------------------------- �޴� ȭ�� ----------------------------
	if (menu_page) { // �޴� ������ ���� ���� 1�̸�
		ofSetColor(ofColor::lemonChiffon);
		ofDrawRectangle(600, 200, 200, 60);
		ofSetColor(0);
		ofDrawBitmapString("Save", 685, 235); // ���̺� ��ư �׸���

		ofSetColor(ofColor::lemonChiffon);
		ofDrawRectangle(600, 300, 200, 60);
		ofSetColor(0);
		ofDrawBitmapString("Load", 685, 335); // �ε� ��ư �׸���

		note_image.draw(480, 50, 30, 30); // ��ǥ �̹��� �׸���
		ofSetColor(ofColor::lemonChiffon);
		ofDrawRectangle(550, 50, 300, 30); // BGM ��ư �߰� ���簢�� �׸���
		ofDrawTriangle(540, 50, 540, 80, 520, 65); // BGM ��ư ���� �ﰢ�� �׸���
		ofDrawTriangle(860, 50, 860, 80, 880, 65); // BGM ��ư ���� �ﰢ�� �׸���
		ofSetColor(0);
		if (bgm_num == 1)
			ofDrawBitmapString("BGM 1", 680, 73); // BGM 1 ��Ÿ����
		else if (bgm_num == 2)
			ofDrawBitmapString("BGM 2", 680, 73); // BGM 2 ��Ÿ����
		else if (bgm_num == 3)
			ofDrawBitmapString("BGM 3", 680, 73); // BGM 3 ��Ÿ����

		for (int i = 0; i < 5; i++) {
			ofSetColor(0); // ������
			ofDrawBitmapString("Rectangle", 20, 120); // "Rectangle"�̶�� ���ڿ� �׸���

			ofSetColor(135, 206, 250); // �ϴû�
			string level_back = to_string(i + 1);
			string level_front = "Lv. ";
			level_front = level_front + level_back; // level_front��� string ������ "Lv. i"(i ���� �ݺ��� ����Ǹ鼭 �ٲ�)��� ���ڿ��� ���� 

			ofDrawRectangle(20 + 100 * i, 150, 90, 125); // ���簢�� �׸���
			ofSetColor(255); // ������
			ofDrawBitmapString(level_front, 20 + 100 * i, 250); // level_front ���ڿ� �׸���

			for (int k = 0; k < score[i]; k++)
				star_image.draw(25 + 30 * k + 100 * i, 200, 20, 20); // ������ŭ ä���� �� �׸���
			for (int j = score[i]; j < 3; j++)
				blank_star_image.draw(25 + 30 * j + 100 * i, 200, 20, 20); // (3 - ����)���� �� �� �׸���
		}

		ofSetColor(0); // ������
		ofDrawBitmapString("Heart", 20, 420); // "Heart"��� ���ڿ� ���

		for (int i = 0; i < 5; i++) {
			ofSetColor(135, 206, 250); // �ϴû�
			string levelN = to_string(i + 1);
			string levelName = "Lv. ";
			levelName = levelName + levelN; // level_front��� string ������ "Lv. i"(i ���� �ݺ��� ����Ǹ鼭 �ٲ�)��� ���ڿ��� ���� 
			 
			ofDrawRectangle(20 + 100 * i, 450, 90, 125); // ���簢�� �׸���
			ofSetColor(255); // ������
			ofDrawBitmapString(levelName, 20 + 100 * i, 550); // level_front ���ڿ� �׸���

			for (int k = 0; k < score[i + 5]; k++) 
				star_image.draw(25 + 30 * k + 100 * i, 500, 20, 20); // ������ŭ ä���� �� �׸���
			for (int j = score[i + 5]; j < 3; j++)
				blank_star_image.draw(25 + 30 * j + 100 * i, 500, 20, 20); // (3 - ����)���� �� �� �׸���
		}
	}

	// ---------------------------------------------- �÷��� ȭ�� -------------------------
	if (playing) { // ���� �÷��� ���� ���� 1�̸�
		for(int i = 0; i < hp; i++)
			hp_image.draw(600 + 30 * i, 30, 10, 10); // ��� ���� ��ŭ �̹��� �׸���

		ofSetColor(255); // ���
		if (stage >= 1 && stage <= 5)
			lion_image.draw(300, 100, 400, 200); // ���� �ڿ� �׸� �׸���
		else if (stage >= 6 && stage <= 10)
			lion_image.draw(400, 150, 300, 100); // ���� �ڿ� �׸� �׸���

		for (int i = 0; i < vertical_block_num; i++) // ���� ���ΰ��� ������ŭ
			for (int j = 0; j < horizontal_block_num; j++){ // ���� ���ΰ��� ������ŭ
				if (bricks[i][j] == 1) { // bricks ���� 1�̸�
					ofSetColor(ofColor::seaGreen);
					ofDrawRectangle(j*block_width, i*block_height, block_width - 2, block_height - 2); // ���簢�� �׸���
				}
				else if (bricks[i][j] == 2) {
					ofSetColor(ofColor::skyBlue);
					ofDrawRectangle(j*block_width, i*block_height, block_width - 2, block_height - 2); // ���簢�� �׸���
				}
			}

		if (!moving && !game_pause) { // (���� �������� �����鼭 �Ͻ� ���� ���� ���� 0�� ���) = ���� �ٷ� �������� ���� ���� ����߷��� ��
			xPos = padX + padWidth / 2; // ���� x ��ǥ ���� ���� �߾����� ����
			yPos = ofGetHeight() - 50 - ball_rad; // ���� y ��ǥ ���� ���� �ٷ� ���� ����
		}

		ofSetColor(ofColor::deepSkyBlue);
		ofCircle(xPos, yPos, ball_rad); // �� �׸���(= ��)

		ofSetColor(ofColor::hotPink);
		ofLine(padX, ofGetHeight() - 50, padX + padWidth, ofGetHeight() - 50); // �� �׸���(= ����)

		ofDrawBitmapString("time : ", 10, 30); // "time : "�̶�� ���ڿ� �׸���
		ofDrawBitmapString(to_string(time), 100, 30); // time ���� string ������ �ٲ㼭 �׸���

		if (ofGetMousePressed(OF_MOUSE_BUTTON_RIGHT)) {
			moving = true;
		} // ���콺 ��Ŭ���ϸ� ���� ����

		if (xPos < ball_rad || xPos > ofGetWidth() - ball_rad) { // ����, ������ �� �ε��� ���
			xDir *= -1;
			bump_sound.play(); // �� ƨ��� �Ҹ� �÷���
		}

		if (yPos < ball_rad) { // õ�� �ε��� ���
			yDir *= -1;
			bump_sound.play(); // �� ƨ��� �Ҹ� �÷���
		}

		if (yPos == ofGetHeight() - 50 - ball_rad) { // �ٿ� �ε��� ���
			if (moving) { // ������ ���� ���� 1�� ���
				if (xPos >= padX && xPos <= padX + padWidth) {
					yDir *= -1;
					bump_sound.play(); // �� ƨ��� �Ҹ� �÷���
				}
			}
		}

		if (yPos >= ofGetHeight() - ball_rad) { // ���� y��ǥ�� ���� ��ġ���� ũ��(= ���� �Ʒ��� ���� ��ġ�ϸ�)
			hp--; // ��� 1�� ����
			time = 0; // �ð��� �ٽ� 0���� �ʱ�ȭ
			moving = 0; // ���� ������ ���� ���� 0���� �ʱ�ȭ

			if (hp == 0) // ����� 0����
				gameover = 1; // ���� ����
		}
	}


	//-------------------------------------- ���� �÷��� �� ���� ȭ��----------------------------------------------
	if (game_pause) { // �Ͻ� ���� ���� ���� 1�̸�
		ofSetColor(ofColor::blue);
		pause_image.draw(120, 120); // �Ͻ� ���� ȭ�� �׸���
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//--------------------------------------------- ���� ȭ�� ---------------------------------------------------
	if (start_page) { // ���� ȭ�鿡��
		if (key == ' ') { // �����̽��� ������
			menu_page = 1; // �޴� ������ ���� 1�� �ʱ�ȭ
			start_page = 0; // ���� ȭ�� ���� 0���� �ʱ�ȭ
		}
	}

	//---------------------------------------------- ���� �÷��� ���� ------------------------------------------------
	if (playing && (key == 's' || key == 'S')) { // ���� �÷��� ���� s Ű ������
		moving = 0; // �� ������ ���߱�
		game_pause = 1; // �Ͻ� ���� ���� 1�� �ʱ�ȭ
	}

	//-------------------------------------------- ���� ���� ȭ�� ------------------------------------------------------
	if (gameover && (key == 'q' || key == 'Q')) { // ���� ���� ���¿��� q Ű ������ -> �޴�ȭ������
		gameover = 0; // ���� ���� ���� 0���� �ʱ�ȭ
		moving = 0; // �� ������ ���� 0���� �ʱ�ȭ
		playing = 0; // ���� �÷��� ���� ��Ÿ���� ���� 0���� �ʱ�ȭ
		menu_page = 1; // �޴� ������ ���� 1�� �ʱ�ȭ
		hp = 3; // ��� ���� 3���� �ʱ�ȭ
		time = 0; // �ð� ���� 0���� �ʱ�ȭ
		xPos = padX + padWidth / 2; // ���� x�� ��ǥ��, ���� �߾����� �ʱ�ȭ
		yPos = ofGetHeight() - 50 - ball_rad; // ���� y�� ��ǥ��, ���� �ٷ� ���� �ʱ�ȭ
	}

	if (gameover && (key == 'r' || key == 'R')) { // ���� ���� ���¿��� r Ű ������ -> ���� �������� �絵��
		gameover = 0; // ���� ���� ���� 0���� �ʱ�ȭ
		moving = 0; // �� ������ ���� 0���� �ʱ�ȭ
		playing = 1; // ���� �÷��� ���� ��Ÿ���� ���� 1�� �ʱ�ȭ
		hp = 3; // ��� ���� 3���� �ʱ�ȭ
		time = 0; // �ð� ���� 0���� �ʱ�ȭ
		xPos = padX + padWidth / 2; // ���� x�� ��ǥ��, ���� �߾����� �ʱ�ȭ
		yPos = ofGetHeight() - 50 - ball_rad; // ���� y�� ��ǥ��, ���� �ٷ� ���� �ʱ�ȭ

		if (1 <= stage && stage <= 5)
			rectangle();
		else if (6 <= stage && stage <= 10)
			heart(); // �������� ���� ���̵� �Լ� �� ȣ��
	}

	//------------------ (�׽�Ʈ�� Ű����) l ������ ���� Ŭ����, k ������ ���� ���� -------------------------
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
	//------------------------------------- �޴� ������ -------------------------------------------------
	if (menu_page) { // �޴� ���������� ���̵� �����ϴ� ����
		if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
			//-------------------------------------------- �������� ���� ------------------------------------------------------
			if (20 <= x && x <= 110 && 150 <= y && y <= 275) {
				stage = 1;
				rectangle();
				click_sound.play(); // Ŭ�� ���� ���
				menu_page = 0; // �޴� ������ ��Ȱ��ȭ
				playing = 1; // ���� �÷��� ȭ�� Ȱ��ȭ
			}
			else if (120 <= x && x <= 210 && 150 <= y && y <= 275) {
				stage = 2;
				rectangle();
				click_sound.play(); // Ŭ�� ���� ���
				menu_page = 0; // �޴� ������ ��Ȱ��ȭ
				playing = 1; // ���� �÷��� ȭ�� Ȱ��ȭ
			}
			else if (220 <= x && x <= 310 && 150 <= y && y <= 275) {
				stage = 3;
				rectangle();
				click_sound.play(); // Ŭ�� ���� ���
				menu_page = 0; // �޴� ������ ��Ȱ��ȭ
				playing = 1; // ���� �÷��� ȭ�� Ȱ��ȭ
			}
			else if (320 <= x && x <= 410 && 150 <= y && y <= 275) {
				stage = 4;
				rectangle();
				click_sound.play(); // Ŭ�� ���� ���
				menu_page = 0; // �޴� ������ ��Ȱ��ȭ
				playing = 1; // ���� �÷��� ȭ�� Ȱ��ȭ
			}
			else if (420 <= x && x <= 510 && 150 <= y && y <= 275) {
				stage = 5;
				rectangle();
				click_sound.play(); // Ŭ�� ���� ���
				menu_page = 0; // �޴� ������ ��Ȱ��ȭ
				playing = 1; // ���� �÷��� ȭ�� Ȱ��ȭ
			}
			else if (20 <= x && x <= 110 && 450 <= y && y <= 575) {
				stage = 6;
				heart();
				click_sound.play(); // Ŭ�� ���� ���
				menu_page = 0; // �޴� ������ ��Ȱ��ȭ
				playing = 1; // ���� �÷��� ȭ�� Ȱ��ȭ
			}
			else if (120 <= x && x <= 210 && 450 <= y && y <= 575) {
				stage = 7;
				heart();
				click_sound.play(); // Ŭ�� ���� ���
				menu_page = 0; // �޴� ������ ��Ȱ��ȭ
				playing = 1; // ���� �÷��� ȭ�� Ȱ��ȭ
			}
			else if (220 <= x && x <= 310 && 450 <= y && y <= 575) {
				stage = 8;
				heart();
				click_sound.play(); // Ŭ�� ���� ���
				menu_page = 0; // �޴� ������ ��Ȱ��ȭ
				playing = 1; // ���� �÷��� ȭ�� Ȱ��ȭ
			}
			else if (320 <= x && x <= 410 && 450 <= y && y <= 575) {
				stage = 9;
				heart();
				click_sound.play(); // Ŭ�� ���� ���
				menu_page = 0; // �޴� ������ ��Ȱ��ȭ
				playing = 1; // ���� �÷��� ȭ�� Ȱ��ȭ
			}
			else if (420 <= x && x <= 510 && 450 <= y && y <= 575) {
				stage = 10;
				heart();
				click_sound.play(); // Ŭ�� ���� ���
				menu_page = 0; // �޴� ������ ��Ȱ��ȭ
				playing = 1; // ���� �÷��� ȭ�� Ȱ��ȭ
			}
			//------------------------------- �������� ���� �� -----------------------------------------------------

			//------------------------------- ���̺�, �ε� ��ư -----------------------------------------------------
			if (600 <= x && x <= 800 && 200 <= y && y <= 260) {
				save_score();
			}
			else if (600 <= x && x <= 800 && 300 <= y && y <= 360) {
				load_score();
			}
			//------------------------------- ���̺�, �ε� ��ư �� --------------------------------------------

			//------------------------------- BGM ��ư ---------------------------------------------------
			if (bgm_num == 1 && (860 <= x && x <= 880 && 50 <= y && y <= 80)) { // bgm ��Ͽ��� ������ ȭ��ǥ Ŭ���ϸ�
				bgm.stop(); // bgm �Ҹ� ����
				bgm2.play(); // bgm 2 �Ҹ� �÷���
				bgm_num = 2; // bgm_num ���� 2�� �ʱ�ȭ
			}
			else if (bgm_num == 2 && (860 <= x && x <= 880 && 50 <= y && y <= 80)) {
				bgm2.stop(); // bgm 2 �Ҹ� ����
				bgm3.play(); // bgm 3 �Ҹ� �÷���
				bgm_num = 3; // bgm_num ���� 3���� �ʱ�ȭ
			}
			else if (bgm_num == 3 && (520 <= x && x <= 540 && 50 <= y && y <= 80)) {
				bgm3.stop(); // bgm 3 �Ҹ� ����
				bgm2.play(); // bgm 2 �Ҹ� �÷���
				bgm_num = 2; // bgm_num ���� 2�� �ʱ�ȭ
			}
			else if (bgm_num == 2 && (520 <= x && x <= 540 && 50 <= y && y <= 80)) {
				bgm2.stop(); // bgm 2 �Ҹ� ����
				bgm.play(); // bgm �Ҹ� �÷���
				bgm_num = 1; // bgm_num ���� 1�� �ʱ�ȭ
			}

			//------------------------------- BGM ��ư �� ------------------------------------------------
		}
	}

	//------------------------------------------ �Ͻ� ���� ȭ�� ----------------------------------------------
	if (game_pause) { // ���� ���� �Ͻ� ���� ��Ų ���
		if (240 <= x && x <= 440 && 340 <= y && y <= 380) { // �ٽ� ����
			game_pause = 0; // �Ͻ� ���� ���� 0���� �ʱ�ȭ
			moving = 1; // ���� ������ ���� ���� 1�� �ʱ�ȭ
		}
		else if (510 <= x && x <= 590 && 340 <= y && y <= 380) { // ��Ʈ����
			game_pause = 0; // �Ͻ� ���� ���� 0���� �ʱ�ȭ
			moving = 0; // ���� ������ ���� ���� 0���� �ʱ�ȭ
			playing = 1; // ���� �÷��� ȭ�� Ȱ��ȭ
			hp = 3; // ��� ���� 3���� �ʱ�ȭ
			time = 0; // �ð� ���� 0���� �ʱ�ȭ
			xPos = padX + padWidth / 2; // ���� x�� ��ǥ��, ���� �߾����� �ʱ�ȭ
			yPos = ofGetHeight() - 50 - ball_rad; // ���� y�� ��ǥ��, ���� �ٷ� ���� �ʱ�ȭ

			if (1 <= stage && stage <= 5)
				rectangle();
			else if (6 <= stage && stage <= 10)
				heart();
		}
		else if (660 <= x && x <= 740 && 340 <= y && y <= 380) { // �޴� ��������
			game_pause = 0; // �Ͻ� ���� ���� 0���� �ʱ�ȭ
			moving = 0; // ���� ������ ���� ���� 0���� �ʱ�ȭ
			playing = 0; // ���� �÷��� ȭ�� ��Ȱ��ȭ
			menu_page = 1; // �޴� ������ ȭ�� Ȱ��ȭ
			hp = 3; // ��� ���� 3���� �ʱ�ȭ
			time = 0; // �ð� ���� 0���� �ʱ�ȭ
			xPos = padX + padWidth / 2; // ���� x�� ��ǥ��, ���� �߾����� �ʱ�ȭ
			yPos = ofGetHeight() - 50 - ball_rad; // ���� y�� ��ǥ��, ���� �ٷ� ���� �ʱ�ȭ
		}
	}

	//------------------------------- ���� Ŭ���� ȭ�� ----------------------------------------------------
	if (game_clear && ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) { // ���� Ŭ������ ���
		if (650 <= x && x <= 730 && 380 <= y && y <= 410) {
			gameclear_sound.stop(); // ���� Ŭ���� ���� ���߱�
			game_clear = 0; // ���� ������ ����, Ŭ���� ������ �ٽ� 0
			moving = 0; // ���� ������ ����, �� ������ ���� ���� �� 0���� �ʱ�ȭ
			playing = 0; // ���� ������ ����, �÷��� �� ���� ���� �� 0���� �ʱ�ȭ
			menu_page = 1; // �޴� �������� ���ư��� ����, �޴� ȭ�� ���� 1�� �ʱ�ȭ
			hp = 3; // ���� ������ ����, ��� ���� 3���� �ʱ�ȭ
			time = 0; // ���� ������ ����, �ð� ���� 0���� �ʱ�ȭ
			xPos = padX + padWidth / 2; // ���� ������ ����, �� ��ġ �ʱ� ���·�
			yPos = ofGetHeight() - 50 - ball_rad; // ���� ������ ����, �� ��ġ �ʱ� ���·�
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

//----------------------------------------- ���̵� ���� �Լ� ----------------------------------

void ofApp::rectangle() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 16; j++)
			bricks[i][j] = 0; // ���� ��ϵ� �ʱ�ȭ

	for (int i = 2; i < 8; i++)
		for (int j = 0; j < 16; j++)
			bricks[i][j] = 1; // �簢�� ��� �����

	switch (stage) { // �������� ���� ���̵� ����
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
			bricks[i][j] = 0; // ���� ��� �ʱ�ȭ

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
	bricks[7][7] = bricks[7][8] = 1; // ��Ʈ ��� �����

	switch (stage) { // �������� ���� ���̵� ����
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

//------------------------------------------- ���̵� ���� �Լ� �� ------------------------------------------

//--------------------------------------- ���̺�, �ε� �Լ� --------------------------------------

void ofApp::load_score() { // ���� �ε� ���ִ� �Լ�
	ifstream file_op("rank.txt"); // rank.txt ���� ����
	int tmp, i = 0; 

	if (file_op.is_open()) { // ������ ����������
		while (file_op >> tmp) { // ������ ������ ���� �о tmp �� �ʱ�ȭ
			score[i] = tmp; // score �迭�� ���� tmp �� ����
			i++;
		}
	}
	else // ���� ������ �����޼��� ���
		cout << "file open error!" << endl;

	file_op.close(); // ���� �ݱ�
}

void ofApp::save_score() { // ���� ���̺� ���ִ� �Լ�
	ofstream file_op("rank.txt"); // rank.txt ���� ����
	int tmp, i = 0;
	
	for (int i = 0; i < 10; i++) {
		file_op << score[i] << endl; // score �迭�� ������ rank.txt ���Ͽ� �����
	}

	file_op.close(); // ���� �ݱ�
}
//---------------------------------------- ���̺�, �ε� �Լ� �� ----------------------------------

