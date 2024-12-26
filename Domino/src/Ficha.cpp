#include <iostream>
#include "Ficha.h"

void Ficha::cambiar_ficha(int id, int lado) {
	switch (id) {
	case 1:
		identificador = 1;
		numero1 = 0;
		numero2 = 1;
		this->lado = lado;
		break;
	case 2:
		identificador = 2;
		numero1 = 0;
		numero2 = 2;
		this->lado = lado;
		break;
	case 3:
		identificador = 3;
		numero1 = 0;
		numero2 = 3;
		this->lado = lado;
		break;
	case 4:
		identificador = 4;
		numero1 = 0;
		numero2 = 4;
		this->lado = lado;
		break;
	case 5:
		identificador = 5;
		numero1 = 0;
		numero2 = 5;
		this->lado = lado;
		break;
	case 6:
		identificador = 6;
		numero1 = 0;
		numero2 = 6;
		this->lado = lado;
		break;
	case 7:
		identificador = 7;
		numero1 = 1;
		numero2 = 2;
		this->lado = lado;
		break;
	case 8:
		identificador = 8;
		numero1 = 1;
		numero2 = 3;
		this->lado = lado;
		break;
	case 9:
		identificador = 9;
		numero1 = 1;
		numero2 = 4;
		this->lado = lado;
		break;
	case 10:
		identificador = 10;
		numero1 = 1;
		numero2 = 5;
		this->lado = lado;
		break;
	case 11:
		identificador = 11;
		numero1 = 1;
		numero2 = 6;
		this->lado = lado;
		break;
	case 12:
		identificador = 12;
		numero1 = 2;
		numero2 = 3;
		this->lado = lado;
		break;
	case 13:
		identificador = 13;
		numero1 = 2;
		numero2 = 4;
		this->lado = lado;
		break;
	case 14:
		identificador = 14;
		numero1 = 2;
		numero2 = 5;
		this->lado = lado;
		break;
	case 15:
		identificador = 15;
		numero1 = 2;
		numero2 = 6;
		this->lado = lado;
		break;
	case 16:
		identificador = 16;
		numero1 = 3;
		numero2 = 4;
		this->lado = lado;
		break;
	case 17:
		identificador = 17;
		numero1 = 3;
		numero2 = 5;
		this->lado = lado;
		break;
	case 18:
		identificador = 18;
		numero1 = 3;
		numero2 = 6;
		this->lado = lado;
		break;
	case 19:
		identificador = 19;
		numero1 = 4;
		numero2 = 5;
		this->lado = lado;
		break;
	case 20:
		identificador = 20;
		numero1 = 4;
		numero2 = 6;
		this->lado = lado;
		break;
	case 21:
		identificador = 21;
		numero1 = 5;
		numero2 = 6;
		this->lado = lado;
		break;
	case 22:
		identificador = 22;
		numero1 = 0;
		numero2 = 0;
		this->lado = lado;
		break;
	case 23:
		identificador = 23;
		numero1 = 1;
		numero2 = 1;
		this->lado = lado;
		break;
	case 24:
		identificador = 24;
		numero1 = 2;
		numero2 = 2;
		this->lado = lado;
		break;
	case 25:
		identificador = 25;
		numero1 = 3;
		numero2 = 3;
		this->lado = lado;
		break;
	case 26:
		identificador = 26;
		numero1 = 4;
		numero2 = 4;
		this->lado = lado;
		break;
	case 27:
		identificador = 27;
		numero1 = 5;
		numero2 = 5;
		this->lado = lado;
		break;
	case 28:
		identificador = 28;
		numero1 = 6;
		numero2 = 6;
		this->lado = lado;
		break;
	default:
		identificador = 0;
		numero1 = -1;
		numero2 = -1;
		this->lado = lado;
		break;
	}
}

void Ficha::dibuja(int lado, char pos) {
	switch (identificador) {
		case 1:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_01_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_01_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_01_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_01_v_1.png").id);
				return;
			}
			break;
		case 2:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_02_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_02_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_02_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_02_v_1.png").id);
				return;
			}
			break;
		case 3:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_03_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_03_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_03_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_03_v_1.png").id);
				return;
			}
			break;
		case 4:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_04_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_04_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_04_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_04_v_1.png").id);
				return;
			}
			break;
		case 5:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_05_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_05_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_05_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_05_v_1.png").id);
				return;
			}
			break;
		case 6:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_06_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_06_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_06_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_06_v_1.png").id);
				return;
			}
			break;
		case 7:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_12_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_12_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_12_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_12_v_1.png").id);
				return;
			}
			break;
		case 8:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_13_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_13_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_13_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_13_v_1.png").id);
				return;
			}
			break;
		case 9:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_14_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_14_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_14_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_14_v_1.png").id);
				return;
			}
			break;
		case 10:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_15_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_15_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_15_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_15_v_1.png").id);
				return;
			}
			break;
		case 11:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_16_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_16_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_16_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_16_v_1.png").id);
				return;
			}
			break;
		case 12:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_23_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_23_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_23_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_23_v_1.png").id);
				return;
			}
			break;
		case 13:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_24_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_24_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_24_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_24_v_1.png").id);
				return;
			}
			break;
		case 14:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_25_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_25_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_25_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_25_v_1.png").id);
				return;
			}
			break;
		case 15:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_26_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_26_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_26_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_26_v_1.png").id);
				return;
			}
			break;
		case 16:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_34_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_34_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_34_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_34_v_1.png").id);
				return;
			}
			break;
		case 17:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_35_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_35_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_35_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_35_v_1.png").id);
				return;
			}
			break;
		case 18:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_36_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_36_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_36_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_36_v_1.png").id);
				return;
			}
			break;
		case 19:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_45_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_45_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_45_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_45_v_1.png").id);
				return;
			}
			break;
		case 20:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_46_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_46_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_46_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_46_v_1.png").id);
				return;
			}
			break;
		case 21:
			if (lado == 0 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_56_h_0.png").id);
				return;
			}
			if (lado == 0 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_56_v_0.png").id);
				return;
			}
			if (lado == 1 && pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_56_h_1.png").id);
				return;
			}
			if (lado == 1 && pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_56_v_1.png").id);
				return;
			}
			break;
		case 22:
			if (pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_00_h.png").id);
				return;
			}
			if (pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_00_v.png").id);
				return;
			}
			break;
		case 23:
			if (pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_11_h.png").id);
				return;
			}
			if (pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_11_v.png").id);
				return;
			}
			break;
		case 24:
			if(pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_22_h.png").id);
				return;
			}
			if (pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_22_v.png").id);
				return;
			}
			break;
		case 25:
			if (pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_33_h.png").id);
				return;
			}
			if (pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_33_v.png").id);
				return;
			}
			break;
		case 26:
			if (pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_44_h.png").id);
				return;
			}
			if (pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_44_v.png").id);
				return;
			}
			break;
		case 27:
			if (pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_55_h.png").id);
				return;
			}
			if (pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_55_v.png").id);
				return;
			}
			break;
		case 28:
			if (pos == 'h') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_66_h.png").id);
				return;
			}
			if (pos == 'v') {
				glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/ficha_66_v.png").id);
				return;
			}
			break;
	}
}

void Ficha::set_num1(int num1) {
	numero1 = num1;
}

void Ficha::set_num2(int num2) {
	numero2 = num2;
}

void Ficha::default_id() {
	identificador = 0;
	numero1 = -1;
	numero2 = -1;
}