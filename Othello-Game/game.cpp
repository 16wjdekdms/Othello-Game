#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Game;
class Point;

//���� ���� Ŭ����
class Board
{
	int point1; //�� ����
	int point2; //��ǻ�� ����
	char board[8][9] = { //�ʱ� ���� ����
		"--------",
		"--------",
		"--------",
		"---XO---",
		"---OX---",
		"--------",
		"--------",
		"--------" };
	int boardW[8][8] = { //������ �� ����ġ
		1000, 1, 10, 10, 10, 10, 1, 1000,
		1, 1, 5, 5, 5, 5, 1, 1,
		10, 5, 5, 5, 5, 5, 5, 10,
		10, 5, 5, 5, 5, 5, 5, 10,
		10, 5, 5, 5, 5, 5, 5, 10,
		10, 5, 5, 5, 5, 5, 5, 10,
		1, 1, 5, 5, 5, 5, 1, 1,
		1000, 1, 10, 10,10, 10, 1, 1000
	};
public:
	void Show(); //board ������ ����ϴ� �Լ�
	friend Game; //friend����
	friend Point; //friend����
};

//���� Ŭ����
class Point
{
public:
	int MyPoint(Board b); //�� ������ ������ ��ȯ�ϴ� �Լ�
	int ComPoint(Board b); //��ǻ�� ������ ��ȯ�ϴ� �Լ�
};

//���� ���� Ŭ����
class Game
{
	int row, col; //�Է� ���� ��, �� ��ġ�� ������ ����
	int array[8][2] = { //8�� ������ ��ǥ
		{-1,-1},
		{-1, 0},
		{-1, 1},
		{0, -1},
		{0, 1},
		{1, -1},
		{1, 0},
		{1, 1}
	};
public:
	void Mycheck(Board* b); //����ڰ� ���� ��ġ�� ������ board ������ �����ϴ� �Լ�
	void Comcheck(Board* b); //��ǻ�Ͱ� ���� ��ġ�� ������ board ������ �����ϴ� �Լ�
	bool end(Board b); //������ �������� Ȯ���ϴ� �Լ� (���� ��� 1�� ��ȯ)
};

void Game::Mycheck(Board* b)
{
	stack<int> s1; //������ �� �ִ� ���� ��ġ�� ������ ����
	int row_copy; int col_copy; //����ڿ��� �Է¹��� row, col���� �����ϴ� ����

	cout << "�� ����" << endl;
	cout << "��ġ ����(ex: �� ��): ";
	cin >> row >> col;
	row -= 1; col -= 1; //0���� �����̶� -1
	row_copy = row; col_copy = col; //���� row, col�� ����

	//�Է¹��� ��ġ���� 8���� �������� Ž��
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			row += array[i][j]; col += array[i][j + 1]; //Ž��

			if (row < 0 || col < 0 || row > 7 || col > 7) //���带 ��� ���
			{
				row = row_copy; col = col_copy; //���� row, col ������ ����
				break; //���� ���� Ž��
			}
			else if (b->board[row][col] == '-') //��ĭ�� ���
			{
				row = row_copy; col = col_copy;
				break; //���� ���� Ž��
			}

			else if (b->board[row][col] == 'X')//���� ��, ������ �� ����.
			{
				row = row_copy; col = col_copy;
				break; //���� ���� Ž��
			}

			else //if (b.board[row][col] == 'O'), �ٸ� ���� ���, ������ ���ɼ��� �ִ� ���
			{
				//������ �� �ִ� �ڸ� ���ÿ� �ֱ�
				s1.push(col);
				s1.push(row);

				while (b->board[row][col] != 'X') //Ž�� �ݺ�
				{
					row += array[i][j]; col += array[i][j + 1]; //���� �������� ��� Ž��

					if (b->board[row][col] == NULL || b->board[row][col] == '-') //��ĭ�̰ų� ���带 ��� ��� ���� �� ����
					{
						while (!s1.empty()) //���� ����
						{
							s1.pop();
						}
						break;
					}
					if (b->board[row][col] == 'X') break; //���� ���� ���� ������ ����

					s1.push(col);
					s1.push(row);
				}
				row = row_copy; col = col_copy; //����
			}
		}
		if (!s1.empty()) break;
	}

	//������ ����ִ� ��� ������ ���� �����Ƿ� ���� �� ����.
	if (s1.empty())
	{
		printf("���� �� ����\n");
	}
	//���� �� �ִ� ���
	else
	{
		row = row_copy; col = col_copy;
		b->board[row][col] = 'X'; //���� �Է��� ��ǥ�� ǥ��
		while (!s1.empty()) //�� ������
		{
			int i = s1.top(); s1.pop(); //�ٲ� ��ġ ��
			int j = s1.top(); s1.pop(); //�ٲ� ��ġ ��
			b->board[i][j] = 'X'; //O�� X�� ����
		}
	}

}

void Game::Comcheck(Board* b)
{
	stack<int> s2; //���忡 'O'�� �ִ� ��ġ�� ������ ����
	stack<int> s3; //��ǻ�Ͱ� �� �� �ִ� ��ġ�� ������ ����
	stack<int> s4; //������ ���� ��ġ�� �����ϴ� ����
	stack<int> f; //����ġ�� 1000�� ��ġ�� ������ ���� 
	stack<int> s; //����ġ�� 10�� ��ġ�� ������ ����
	stack<int> t; //����ġ�� 5�� ��ġ�� ������ ����
	stack<int> l; //����ġ�� 1�� ��ġ�� ������ ����

	int row1; int col1; //��ǻ�� �� 'O'�� �ִ� ��ġ�� ������ ���� 
	int row2; int col2; //���� ���� �� �ִ� ��ġ�� ������ ����
	int row_copy; int col_copy; //row1, col1�� ���� ������ ����
	int row2_copy; int col2_copy; //row2, col2�� ���� ������ ����

	cout << endl << "��ǻ�� ����" << endl;

	//'O' �� ��ġ ã��
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (b->board[i][j] == 'O')
			{
				s2.push(j); s2.push(i); //��, �� ������ stack�� �ֱ�, ���� �� ��, �� ������ ���´�.
			}
		}
	}

	while (!empty(s2))
	{
		row1 = s2.top(); s2.pop();
		col1 = s2.top(); s2.pop();
		row_copy = row1; col_copy = col1; //���� row1, col1�� ����

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				row1 += array[i][j]; col1 += array[i][j + 1];

				if (row1 < 0 || col1 < 0 || row1 > 7 || col1 > 7) //���带 ��� ���
				{
					row1 = row_copy; col1 = col_copy; //���� row1, col1 ������ ����
					break; //���� ���� Ž��
				}
				else if (b->board[row1][col1] == '-') //��ĭ�� ���
				{
					row1 = row_copy; col1 = col_copy; //���� ������ ����
					break; //���� ���� Ž��
				}

				else if (b->board[row1][col1] == 'O')//���� ��, ������ �� ����.
				{
					row1 = row_copy; col1 = col_copy; //���� ������ ����
					break; //���� ���� Ž��
				}

				else //if (b.board[row1][col1] == 'X'), �ٸ� ���� ���, ������ ���ɼ��� �ִ� ���
				{
					while (b->board[row1][col1] != '-')
					{
						row1 += array[i][j]; col1 += array[i][j + 1]; //���� �������� ��� Ž��
						if (b->board[row1][col1] == '-') //- �ΰ�� ���� �� �ִ�.
						{
							s3.push(col1); s3.push(row1);//���� �� �ִ� ��ǥ ���ÿ� ����
							break; //���� ���� �� ����
						}
						if (b->board[row1][col1] == NULL || b->board[row1][col1] == 'O') { //���带 �Ѿ�ų� ���� ���� ���
							break; //���� �� ���� ��ġ�̹Ƿ� ����
						}
					}
					row1 = row_copy; col1 = col_copy;
				}
			}
		}
	}

	if (empty(s3)) {
		cout << "��ǻ��: ���� �ڸ� ����";
	}

	while (!empty(s3)) //empty�� ������ �ݺ�
	{
		row2 = s3.top(); s3.pop(); //���� �� �ִ� ��
		col2 = s3.top(); s3.pop(); //���� �� �ִ� ��

		//����ġ�� 1000�� ��� ���� f�� �ִ´�
		if (b->boardW[row2][col2] == 1000) {
			f.push(col2); f.push(row2);
		}

		//����ġ�� 10�� ��� ���� s�� �ִ´�
		else if (b->boardW[row2][col2] == 10) {
			s.push(col2); s.push(row2);
		}

		//����ġ�� 5�� ��� ���� t�� �ִ´�
		else if (b->boardW[row2][col2] == 5) {
			t.push(col2); t.push(row2);
		}

		//����ġ�� 1�� ��� ���� l�� �ִ´�
		else {
			l.push(col2); l.push(row2);
		}
	}

	//���� f�� ��� ���� �ʴٸ� 
	if (!f.empty()) {
		//row2, col2�� ���� f�� �ִ� ������ ����
		row2 = f.top(); f.pop();
		col2 = f.top(); f.pop();
	}

	//���� s�� ��� ���� �ʴٸ� 
	else if (!s.empty()) {
		//row2, col2�� ���� f�� �ִ� ������ ����
		row2 = s.top(); s.pop();
		col2 = s.top(); s.pop();
	}

	//���� s�� ��� ���� �ʴٸ� 
	else if (!t.empty()) {
		//row2, col2�� ���� f�� �ִ� ������ ����
		row2 = t.top(); t.pop();
		col2 = t.top(); t.pop();
	}

	//���� s�� ��� ���� �ʴٸ�
	else if (!l.empty()) {
		//row2, col2�� ���� f�� �ִ� ������ ����
		row2 = l.top(); l.pop();
		col2 = l.top(); l.pop();
	}

	b->board[row2][col2] = 'O';
	row2_copy = row2; col2_copy = col2;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			row2 += array[i][j]; col2 += array[i][j + 1];

			if (row2 < 0 || col2 < 0 || row2 > 7 || col2 > 7) //���带 ��� ���
			{
				row2 = row2_copy; col2 = col2_copy; //���� row, col ������ ����
				break; //���� ���� Ž��
			}
			else if (b->board[row2][col2] == '-') //��ĭ
			{
				row2 = row2_copy; col2 = col2_copy;
				break;
			}

			else if (b->board[row2][col2] == '0')//���� ��, ������ �� ����.
			{
				row2 = row2_copy; col2 = col2_copy;
				break;
			}

			else //if (b.board[row][col] == 'X'), �ٸ� ���� ���, ������ ���ɼ��� �ִ� ���
			{
				//������ �� �ִ� �ڸ� ���ÿ� �ֱ�
				s4.push(col2);
				s4.push(row2);

				while (b->board[row2][col2] != 'O') //O �ΰ�� ���� �� �ִ�.
				{
					row2 += array[i][j]; col2 += array[i][j + 1]; //���� �������� Ž��

					if (b->board[row2][col2] == NULL || b->board[row2][col2] == '-') //��ĭ�̰ų� ���带 ��� ��� ������ �� ����
					{
						while (!s4.empty()) //���� ����
						{
							s4.pop();
						}
						break;
					}
					if (b->board[row][col] == 'O') break; //���� ���� ���� ������ ����

					s4.push(col2);
					s4.push(row2);
				}

				row2 = row2_copy; col2 = col2_copy;
			}
		}
		if (!s4.empty()) break;
	}

	while (!s4.empty()) //�� ������
	{
		int i = s4.top(); s4.pop();
		int j = s4.top(); s4.pop();
		b->board[i][j] = 'O';
	}
}

bool Game::end(Board b)
{
	int total = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (b.board[i][j] == '-') total++;
		}
	}
	if (total == 0) return true; //'-'�� ���忡 ���� ��� ����
	else return false; //�� �ܴ̿� ���� ����
}

void Board::Show()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
}

int Point::MyPoint(Board b) //'x' ��
{
	int total = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (b.board[i][j] == 'X') total++;
		}
	}
	cout << " ---------------------------------" << endl;
	cout << "| �� ����: " << total << "�� ";

	return total;
}

int Point::ComPoint(Board b) //'o' ��
{
	int total = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (b.board[i][j] == 'O') total++;
		}
	}

	cout << "| ��ǻ�� ����: " << total << "�� |" << endl;
	cout << " ---------------------------------" << endl;

	return total;
}

int main()
{
	int i = 1; //������ �����ϱ� ���� ����
	Board b; Game g; Point p; //��ü ����
	cout << "< ���� ȭ�� >" << endl << endl;
	b.Show(); //ó�� ���� ���� ȭ�� ���
	while (1)
	{
		if (g.end(b))
		{
			cout << "���� ����" << endl;
			break;
		}
		cout << endl << "---------" << i << "��° ��" << "---------" << endl << endl;

		g.Mycheck(&b); //����� �� �α�
		b.Show(); //�ٲ� ���� ���
		g.Comcheck(&b); //��ǻ�� �� �α�
		b.Show(); //�ٲ� ���� ���
		p.MyPoint(b); p.ComPoint(b); //���� ö��
		i++; //�� ����
	}
}