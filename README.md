# 🏆 Othello Game (C++)
C++로 구현한 **오델로(Othello) 게임**입니다.  
사용자(X)와 컴퓨터(O)가 번갈아 가며 말을 두며, **컴퓨터가 유리한 위치를 찾아 자동으로 둡니다.**  
![Image](https://github.com/user-attachments/assets/fc303c43-be86-414a-84b4-7760414f9321)
## 🎮 게임 소개
- **8x8 오델로 보드**에서 진행됩니다.
- **사용자(X) vs 컴퓨터(O)** 방식으로 플레이됩니다.
- **컴퓨터는 가중치 기반 AI**를 사용하여 최적의 위치를 선택합니다.
- 승패는 **더 많은 돌을 차지한 플레이어**가 결정합니다.

## 🛠️ 주요 기능
✅ **게임판 출력** (8x8 배열)  
✅ **사용자(X) 입력** (위치 선택 & 돌 뒤집기)  
✅ **컴퓨터(O) 자동 선택** (가중치 기반 AI 적용)  
✅ **게임 종료 & 점수 계산**  
✅ **C++ 객체지향 프로그래밍(OOP) 적용**  

## 🖥️ 실행 방법
### 1️⃣ **GitHub에서 프로젝트 클론**
```bash
git clone https://github.com/사용자명/저장소명.git
cd 저장소명
```
### 2️⃣ **Visual Studio 2022에서 실행 (Windows)**  
1. Visual Studio 2022 실행
2. 파일 → 열기 → 폴더 열기 를 선택하고 클론한 프로젝트 폴더 선택
3. Ctrl + Shift + B 또는 빌드 → 빌드 솔루션 클릭
4. Ctrl + F5 또는 디버그 → 디버깅 없이 시작 클릭하여 실행
   
### 3️⃣ **명령어로 실행 (Windows)**
```bash
cd 경로\저장소명
cl othello.cpp /EHsc
othello.exe
```
### 4️⃣ **Linux/macOS (g++ 컴파일러 사용)**
```bash
g++ -o othello othello.cpp
./othello
