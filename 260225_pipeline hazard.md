## 해저드(Hazard)?

특정한 이유로 다음 clock cycle에 다음 명령어가 실행되지 않는 상황

### 3가지의 Hazard 원인

1. Structural Hazard
2. Data Hazard
3. Control Hazard

→ 모든 Hazard는 waiting으로 해결된다. (stall)

### Structural Hazard (구조적 해저드)

자원은 하나인데 여러 명령이 동시에 수행되려고 할 때 발생한다.

![Instruction 1에서는 data fetch를 위해, instruction4 에서는 instruction fetch를 위해 CC5일 때, mem에 접근하려고 하고 있다. 이때 구조적 해저드가 발생한다.](attachment:365bafec-76af-4ff2-93f5-e9349b4b608e:image.png)

Instruction 1에서는 data fetch를 위해, instruction4 에서는 instruction fetch를 위해 CC5일 때, mem에 접근하려고 하고 있다. 이때 구조적 해저드가 발생한다.

> 해결책
> 

hardware resource를 추가하면 된다.

또는 저장장소를 활용한다.

- 왜?
    
    하드웨어 리소스란, 소프트웨어가 실행되기 위해 점유하거나 제어해야하는 물리적 부품과 그 장치가 제공하는 능력을 말한다.
    
    예시) 소프트웨어가 요리 레시피라면 하드웨어 리소스는 주방, 식재료, 불판 이런것이다.
    

### Data Harzard (데이터 해저드)

아직 파이프라인 명령어가 끝나지 않은 register에 접근하여 명령어를 실행하려고 할 때 발생한다.

![ADD가 $2+$3의 겨로가를 $1에 저장하기 전에 SUB $1를 사용해버림. 이렇게 값이 저장되기 전에 읽으려하면 데이터 해저드가 발생](attachment:cd9d5833-31dd-4626-ad3a-5952b1cc8e0f:image.png)

ADD가 $2+$3의 겨로가를 $1에 저장하기 전에 SUB $1를 사용해버림. 이렇게 값이 저장되기 전에 읽으려하면 데이터 해저드가 발생

> 해결책
> 
1. freezing the pipeline - 앞의 명령어가 데이터를 write할 때까지 register update를 중지시킨다.

![데이터를 write 할 때까지 stall을 넣어 아무것도 하지 않는다. 2 clock 손해본다.](attachment:ad115138-12a6-429c-a90f-5165527afced:image.png)

데이터를 write 할 때까지 stall을 넣어 아무것도 하지 않는다. 2 clock 손해본다.

1. 전방 전달(forwarding) - write하기 전 write 내용이 계산되면 다음 명령어로 미리 받아온다.
    - 미리 계산해서 가져오는 것이다. clock 손해가 최대 1개다.

### 컨트롤 해저드 해결책

1. stall (걍 기다리기) - 최대 3 clock 손해 봄
2. oppimized branch procession - 3 clock 손해 → 1 clock 손해
    - branch가 됐는데 안됐는지 빨리 판단하고 주소 계산
    
      → 각 비트끼리 XOR한 32bit을 NOR 하여 미리 계산
    
3. branch prediction (branch 주소 예측) - hw적 수정
    - branch가 무조건 안될거라고/될거라고 예측하고 그냥 명령어 순서대로 실행하는 것(?)
    - 예측이 틀리면 다음 명령어 flush하고 branch target 명령어를 넣는다.
