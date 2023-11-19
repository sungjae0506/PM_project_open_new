# PM_project_open_new

파일 구조 (src)
<pre>
C:.
├─asset
│      image.cpp
│      image.h
│      sound_loader.cpp
│      sound_loader.h
│      texture_loader.cpp
│      texture_loader.h
│
├─game
│      bubble.cpp
│      bubble.h
│      enemy.cpp
│      enemy.h
│      entity.h
│      game_manager.cpp
│      game_manager.h
│      map.cpp
│      map.h
│      player.cpp
│      player.h
│
├─main
│      callback.cpp
│      callback.h
│      main.cpp
│
├─not_used
│      background.cpp
│      background.h
│      test.cpp
│
├─UI
│      button.cpp
│      button.h
│      canvas.cpp
│      canvas.h
│      event.h
│      page.cpp
│      page.h
│      text.cpp
│      text.h
│      window.cpp
│      window.h
│
└─util
        object.cpp
        object.h
        range.cpp
        range.h
</pre>

파일 구조(요약)
<pre>
asset: 이미지, 사운드 로딩 (웬만해선 건드릴 필요 없음)
game: 게임 관리
main: main.cpp와 callback 함수
not_used: 말 그대로 필요없는 것
UI: 윈도우, 페이지, 캔버스, 텍스트, 버튼 등을 정의 (이것도 웬만해선 건드릴 필요 없음)
util: object, range를 정의 (이것도 웬만해선 건드릴 필요 없음)
</pre>

Todo (요약)
<pre>
1. gameManager 클래스
2. player 클래스
3. bubble 클래스
4. enemy 클래스
5. main.cpp 에서 레이아웃 설정 및 callback 함수 바인딩
</pre>

함수 및 클래스 사용법
<pre>
1. Range
        직사각형 범위를 표현할 때 사용
        Range range(x0, y0, x1, y1) 으로 객체 생성시 (x0, y0)가 좌하단, (x1, y1)이 우상단인 범위로 저장
2. 
</pre>
