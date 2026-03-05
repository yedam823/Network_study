## 볼 밸런싱 시뮬레이션

빔 위에 있는 공을 PID를 사용하여 중앙에 유지하는 시스템이다.

<aside>

목표위치 (0) → PID → 빔 각도 → 공 가속도 계산 → 공위치 업데이트 → 다시 PID 입력

</aside>

이렇게 중앙에 유지하는 과정의 수치를 csv 파일로 만들어 matplotlib를 이용해 그래프로 표시한다. 

### 물리모델

- 기울어진 빔 위에서 굴러가면 a = g*sin(θ)
- 작은 각도라 가정하면 sin(θ)≈θ

그래서 단순 모델은

```c
float acceleration = (5.0f/7.0f) * g* sinf(theta); // 작은 각도를 가정함
velocity += acceleration * dt; // 속도 늘리기
position += velocity * dt + 0.5f * acceleration * dt * dt; //위치 업데이트
```

### PID 제어

- P는 현재 오차에 비례하여 조절함
- I는 과거 누적된 오차를 합산하여 오차를 제거함 (적분 제어)
- D는 오차의 변화율을 계산하여 급격한 속도 변화를 줄이고, 오버슈트를 줄임 (미분제어)

### 파일 구조

<aside>

main.cpp

PID.h

PID.cpp

physics.h

physics.cpp

</aside>

- PID : 제어 알고리즘
- physics : 공 운동 계산
- main : 루프관리

## 추후 개발
시뮬레이터 구현
