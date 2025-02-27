#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Game;
class Point;

//게임 보드 클래스
class Board
{
	int point1; //내 점수
	int point2; //컴퓨터 점수
	char board[8][9] = { //초기 게임 보드
		"--------",
		"--------",
		"--------",
		"---XO---",
		"---OX---",
		"--------",
		"--------",
		"--------" };
	int boardW[8][8] = { //보드의 각 가중치
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
	void Show(); //board 변수를 출력하는 함수
	friend Game; //friend선언
	friend Point; //friend선언
};

//점수 클래스
class Point
{
public:
	int MyPoint(Board b); //내 점수를 점수를 반환하는 함수
	int ComPoint(Board b); //컴퓨터 점수를 반환하는 함수
};

//게임 진행 클래스
class Game
{
	int row, col; //입력 받은 행, 열 위치를 저장할 변수
	int array[8][2] = { //8개 방향의 좌표
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
	void Mycheck(Board* b); //사용자가 놓을 위치를 결정해 board 변수를 변경하는 함수
	void Comcheck(Board* b); //컴퓨터가 놓을 위치를 결정해 board 변수를 변경하는 함수
	bool end(Board b); //게임이 끝났는지 확인하는 함수 (끝날 경우 1을 반환)
};

void Game::Mycheck(Board* b)
{
	stack<int> s1; //뒤집을 수 있는 돌의 위치를 저장할 스택
	int row_copy; int col_copy; //사용자에게 입력받은 row, col값을 보관하는 변수

	cout << "내 차래" << endl;
	cout << "위치 선택(ex: 행 열): ";
	cin >> row >> col;
	row -= 1; col -= 1; //0부터 시작이라 -1
	row_copy = row; col_copy = col; //원래 row, col값 보관

	//입력받은 위치에서 8개의 방향으로 탐색
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			row += array[i][j]; col += array[i][j + 1]; //탐색

			if (row < 0 || col < 0 || row > 7 || col > 7) //보드를 벗어난 경우
			{
				row = row_copy; col = col_copy; //원래 row, col 값으로 복원
				break; //다음 방향 탐색
			}
			else if (b->board[row][col] == '-') //빈칸인 경우
			{
				row = row_copy; col = col_copy;
				break; //다음 방향 탐색
			}

			else if (b->board[row][col] == 'X')//같은 돌, 뒤집을 수 없다.
			{
				row = row_copy; col = col_copy;
				break; //다음 방향 탐색
			}

			else //if (b.board[row][col] == 'O'), 다른 돌인 경우, 뒤집을 가능성이 있는 경우
			{
				//뒤집을 수 있는 자리 스택에 넣기
				s1.push(col);
				s1.push(row);

				while (b->board[row][col] != 'X') //탐색 반복
				{
					row += array[i][j]; col += array[i][j + 1]; //같은 방향으로 계속 탐색

					if (b->board[row][col] == NULL || b->board[row][col] == '-') //빈칸이거나 보드를 벗어난 경우 놓을 수 없음
					{
						while (!s1.empty()) //스택 비우기
						{
							s1.pop();
						}
						break;
					}
					if (b->board[row][col] == 'X') break; //나와 같은 돌을 만나면 중지

					s1.push(col);
					s1.push(row);
				}
				row = row_copy; col = col_copy; //복원
			}
		}
		if (!s1.empty()) break;
	}

	//스택이 비어있는 경우 뒤집을 돌이 없으므로 놓을 수 없다.
	if (s1.empty())
	{
		printf("놓을 수 없음\n");
	}
	//놓을 수 있는 경우
	else
	{
		row = row_copy; col = col_copy;
		b->board[row][col] = 'X'; //내가 입력한 좌표에 표시
		while (!s1.empty()) //돌 뒤집기
		{
			int i = s1.top(); s1.pop(); //바꿀 위치 행
			int j = s1.top(); s1.pop(); //바꿀 위치 열
			b->board[i][j] = 'X'; //O을 X로 변경
		}
	}

}

void Game::Comcheck(Board* b)
{
	stack<int> s2; //보드에 'O'가 있는 위치를 저장할 스택
	stack<int> s3; //컴퓨터가 놀 수 있는 위치를 저장할 스택
	stack<int> s4; //뒤집힐 돌의 위치를 저장하는 스택
	stack<int> f; //가중치가 1000인 위치를 저장할 스택 
	stack<int> s; //가중치가 10인 위치를 저장할 스택
	stack<int> t; //가중치가 5인 위치를 저장할 스택
	stack<int> l; //가중치가 1인 위치를 저장할 스택

	int row1; int col1; //컴퓨터 돌 'O'이 있는 위치를 저장할 변수 
	int row2; int col2; //돌을 놓을 수 있는 위치를 저장할 변수
	int row_copy; int col_copy; //row1, col1의 값을 저장할 변수
	int row2_copy; int col2_copy; //row2, col2의 값을 저장할 변수

	cout << endl << "컴퓨터 차래" << endl;

	//'O' 돌 위치 찾기
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (b->board[i][j] == 'O')
			{
				s2.push(j); s2.push(i); //열, 행 순으로 stack에 넣기, 나올 때 행, 열 순으로 나온다.
			}
		}
	}

	while (!empty(s2))
	{
		row1 = s2.top(); s2.pop();
		col1 = s2.top(); s2.pop();
		row_copy = row1; col_copy = col1; //원래 row1, col1값 보관

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				row1 += array[i][j]; col1 += array[i][j + 1];

				if (row1 < 0 || col1 < 0 || row1 > 7 || col1 > 7) //보드를 벗어난 경우
				{
					row1 = row_copy; col1 = col_copy; //원래 row1, col1 값으로 복원
					break; //다음 방향 탐색
				}
				else if (b->board[row1][col1] == '-') //빈칸인 경우
				{
					row1 = row_copy; col1 = col_copy; //원래 값으로 복원
					break; //다음 방향 탐색
				}

				else if (b->board[row1][col1] == 'O')//같은 돌, 뒤집을 수 없다.
				{
					row1 = row_copy; col1 = col_copy; //원래 값으로 복원
					break; //다음 방향 탐색
				}

				else //if (b.board[row1][col1] == 'X'), 다른 돌인 경우, 뒤집을 가능성이 있는 경우
				{
					while (b->board[row1][col1] != '-')
					{
						row1 += array[i][j]; col1 += array[i][j + 1]; //같은 방향으로 계속 탐색
						if (b->board[row1][col1] == '-') //- 인경우 놓을 수 있다.
						{
							s3.push(col1); s3.push(row1);//놓을 수 있는 좌표 스택에 저장
							break; //스택 저장 후 종료
						}
						if (b->board[row1][col1] == NULL || b->board[row1][col1] == 'O') { //보드를 넘어가거나 같은 돌인 경우
							break; //놓을 수 없는 위치이므로 종료
						}
					}
					row1 = row_copy; col1 = col_copy;
				}
			}
		}
	}

	if (empty(s3)) {
		cout << "컴퓨터: 놓을 자리 없음";
	}

	while (!empty(s3)) //empty일 때까지 반복
	{
		row2 = s3.top(); s3.pop(); //놓을 수 있는 행
		col2 = s3.top(); s3.pop(); //놓을 수 있는 열

		//가중치가 1000일 경우 스택 f에 넣는다
		if (b->boardW[row2][col2] == 1000) {
			f.push(col2); f.push(row2);
		}

		//가중치가 10일 경우 스택 s에 넣는다
		else if (b->boardW[row2][col2] == 10) {
			s.push(col2); s.push(row2);
		}

		//가중치가 5일 경우 스택 t에 넣는다
		else if (b->boardW[row2][col2] == 5) {
			t.push(col2); t.push(row2);
		}

		//가중치가 1일 경우 스택 l에 넣는다
		else {
			l.push(col2); l.push(row2);
		}
	}

	//스택 f가 비어 있지 않다면 
	if (!f.empty()) {
		//row2, col2를 스택 f에 있는 값으로 변경
		row2 = f.top(); f.pop();
		col2 = f.top(); f.pop();
	}

	//스택 s가 비어 있지 않다면 
	else if (!s.empty()) {
		//row2, col2를 스택 f에 있는 값으로 변경
		row2 = s.top(); s.pop();
		col2 = s.top(); s.pop();
	}

	//스택 s가 비어 있지 않다면 
	else if (!t.empty()) {
		//row2, col2를 스택 f에 있는 값으로 변경
		row2 = t.top(); t.pop();
		col2 = t.top(); t.pop();
	}

	//스택 s가 비어 있지 않다면
	else if (!l.empty()) {
		//row2, col2를 스택 f에 있는 값으로 변경
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

			if (row2 < 0 || col2 < 0 || row2 > 7 || col2 > 7) //보드를 벗어난 경우
			{
				row2 = row2_copy; col2 = col2_copy; //원래 row, col 값으로 복원
				break; //다음 방향 탐색
			}
			else if (b->board[row2][col2] == '-') //빈칸
			{
				row2 = row2_copy; col2 = col2_copy;
				break;
			}

			else if (b->board[row2][col2] == '0')//같은 돌, 뒤집을 수 없다.
			{
				row2 = row2_copy; col2 = col2_copy;
				break;
			}

			else //if (b.board[row][col] == 'X'), 다른 돌인 경우, 뒤집을 가능성이 있는 경우
			{
				//뒤집을 수 있는 자리 스택에 넣기
				s4.push(col2);
				s4.push(row2);

				while (b->board[row2][col2] != 'O') //O 인경우 놓을 수 있다.
				{
					row2 += array[i][j]; col2 += array[i][j + 1]; //같은 방향으로 탐색

					if (b->board[row2][col2] == NULL || b->board[row2][col2] == '-') //빈칸이거나 보드를 벗어난 경우 뒤집을 수 없음
					{
						while (!s4.empty()) //스택 비우기
						{
							s4.pop();
						}
						break;
					}
					if (b->board[row][col] == 'O') break; //나와 같은 돌을 만나면 중지

					s4.push(col2);
					s4.push(row2);
				}

				row2 = row2_copy; col2 = col2_copy;
			}
		}
		if (!s4.empty()) break;
	}

	while (!s4.empty()) //돌 뒤집기
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
	if (total == 0) return true; //'-'가 보드에 없는 경우 종료
	else return false; //그 이외는 게임 진행
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

int Point::MyPoint(Board b) //'x' 수
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
	cout << "| 내 점수: " << total << "점 ";

	return total;
}

int Point::ComPoint(Board b) //'o' 수
{
	int total = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (b.board[i][j] == 'O') total++;
		}
	}

	cout << "| 컴퓨터 점수: " << total << "점 |" << endl;
	cout << " ---------------------------------" << endl;

	return total;
}

int main()
{
	int i = 1; //순서를 구분하기 위한 변수
	Board b; Game g; Point p; //객체 생성
	cout << "< 게임 화면 >" << endl << endl;
	b.Show(); //처음 게임 보드 화면 출력
	while (1)
	{
		if (g.end(b))
		{
			cout << "게임 종료" << endl;
			break;
		}
		cout << endl << "---------" << i << "번째 턴" << "---------" << endl << endl;

		g.Mycheck(&b); //사용자 돌 두기
		b.Show(); //바뀐 보드 출력
		g.Comcheck(&b); //컴퓨터 돌 두기
		b.Show(); //바뀐 보드 출력
		p.MyPoint(b); p.ComPoint(b); //점수 철력
		i++; //턴 증가
	}
}